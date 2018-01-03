#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>

#include "immintrin.h"
#include "include/constants.h"
#include "include/data.c"
#include "include/heap.c"
// #include "include/thpool.c"
#include "include/threadpool.c"

struct arg_struct {
    int topic;
    int startidx;
    int endidx;
    long base;
    heap* h;
};

extern void init_tf_prestore_score(char *data_path);
int num_topics;
int num_docs;
long total_terms;

int search(struct arg_struct *arg);

int main(int argc, const char* argv[]) {
  if (argc <= 2) {
    printf("PLEASE ENTER DATA PATH AND THREAD NUMBER!\n");
    return 0;
  }

  int nthreads = atoi(argv[2]);
  printf("Number of threads: %d\n", nthreads);

  init_tf_prestore_score(argv[1]);
  double total = 0;
  int count;
  int N = 3;
  int n, i;
  for (count = 0; count < N; count ++) {
    double time_spent;
    // threadpool thpool;
    for (n = 0; n < num_topics; n ++) {
      heap h_array[nthreads];
      memset(h_array, 0, sizeof(h_array));
      // thpool = thpool_init(nthreads);
      struct threadpool *pool;
      pool = threadpool_init(nthreads);
      struct arg_struct* args[nthreads];
      for (i = 0; i < nthreads; i ++) {
        args[i] = malloc(sizeof(struct arg_struct));
        args[i]->topic = n;
        args[i]->startidx = i * (int)(ceil((double)num_docs / nthreads));
        if ((i + 1) * (int)(ceil((double)num_docs / nthreads)) > num_docs) {
          args[i]->endidx = num_docs;
        } else {
          args[i]->endidx = (i + 1) * (int)(ceil((double)num_docs / nthreads));
        }
        args[i]->base = termindexes[nthreads - 1][i];
        heap h;
        h_array[i] = h;
        args[i]->h = &h_array[i];
      }

      struct timeval begin, end;
      gettimeofday(&begin, NULL);
      for (i = 0; i < nthreads; i ++) {
        // thpool_add_work(thpool, search, args[i]);
        threadpool_add_task(pool, search, args[i], 0);
      }
      // thpool_wait(thpool);
      threadpool_free(pool, 1);

      heap h_merge;
      heap_create(&h_merge, 0, NULL);
      float* min_key_merge;
      int* min_val_merge;
      for (i = 0; i < nthreads; i ++) {
        float* min_key;
        int* min_val;
        while (heap_delmin(&h_array[i], (void**)&min_key, (void**)&min_val)) {
          int size = heap_size(&h_merge);
          if (size < TOP_K) {
            heap_insert(&h_merge, min_key, min_val);
          } else {
            heap_min(&h_merge, (void**)&min_key_merge, (void**)&min_val_merge);
            if (*min_key_merge < *min_key) {
              heap_delmin(&h_merge, (void**)&min_key_merge, (void**)&min_val_merge);
              heap_insert(&h_merge, min_key, min_val);
            }
          }
        }
        heap_destroy(&h_array[i]);
      }

      int rank = TOP_K;
      while (heap_delmin(&h_merge, (void**)&min_key_merge, (void**)&min_val_merge)) {
        // printf("MB%02d Q0 %ld %d %f AVXScan2_optimize_multithread_intraquery\n", (n + 1), tweetids[*min_val_merge], rank, *min_key_merge);
        rank --;
      }
      heap_destroy(&h_merge);

      gettimeofday(&end, NULL);
      time_spent = (double)((end.tv_sec * 1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec));
      total = total + time_spent / 1000.0;
    }
    printf("Time = %f ms\n", total / num_topics);
  }
  // printf("Total time = %f ms\n", total / N);
  printf("Time per query = %f ms\n", (total / N) / num_topics);
}

int search(struct arg_struct *arg) {
  int n, i, j, t;
  long base;
  long cur;

  int jump = DOCS_BLOCK_SIZE;
  int indexsum; //, pos;

  __m256i collect_vec;
  int bits;
  int map[129];
  memset(map, 0, sizeof(map));
  map[128] = 7;
  map[64] = 6;
  map[32] = 5;
  map[16] = 4;
  map[8] = 3;
  map[4] = 2;
  map[2] = 1;
  // int score_pos;

  heap* h = arg->h;
  heap_create(h, 0, NULL);
  float* min_key;
  int* min_val;

  float scores[jump];

  n = arg->topic;
  int start = arg->startidx;
  int end = arg->endidx;
  base = arg->base;
  int off = DOCS_BLOCK_SIZE - start % DOCS_BLOCK_SIZE;
  if (topics[n][1] == 1) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);

    for (i = start; i + jump < end; i += jump) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
      memset(scores, 0, sizeof(scores));
      for (j = 0; j < indexsum; j += 8) {
        cur = base + j;
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
      }

      if (scores[0] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = scores[0];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[0] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[1] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 1;
          float *scorez = malloc(sizeof(float)); *scorez = scores[1];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[1] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[2] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 2;
          float *scorez = malloc(sizeof(float)); *scorez = scores[2];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[2] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[3] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 3;
          float *scorez = malloc(sizeof(float)); *scorez = scores[3];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[3] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[4] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 4;
          float *scorez = malloc(sizeof(float)); *scorez = scores[4];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[4] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[5] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 5;
          float *scorez = malloc(sizeof(float)); *scorez = scores[5];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[5] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[6] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 6;
          float *scorez = malloc(sizeof(float)); *scorez = scores[6];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[6] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[7] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 7;
          float *scorez = malloc(sizeof(float)); *scorez = scores[7];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[7] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[8] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 8;
          float *scorez = malloc(sizeof(float)); *scorez = scores[8];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[8] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[9] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 9;
          float *scorez = malloc(sizeof(float)); *scorez = scores[9];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[9] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(h, scorez, docid);
          }
        }
      }

      base += indexsum;
    }
  } else if (topics[n][1] == 2) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);

    for (i = start; i + jump < end; i += jump) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
      memset(scores, 0, sizeof(scores));
      for (j = 0; j < indexsum; j += 8) {
        cur = base + j;
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
      }

      if (scores[0] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = scores[0];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[0] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[1] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 1;
          float *scorez = malloc(sizeof(float)); *scorez = scores[1];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[1] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[2] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 2;
          float *scorez = malloc(sizeof(float)); *scorez = scores[2];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[2] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[3] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 3;
          float *scorez = malloc(sizeof(float)); *scorez = scores[3];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[3] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[4] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 4;
          float *scorez = malloc(sizeof(float)); *scorez = scores[4];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[4] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[5] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 5;
          float *scorez = malloc(sizeof(float)); *scorez = scores[5];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[5] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[6] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 6;
          float *scorez = malloc(sizeof(float)); *scorez = scores[6];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[6] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[7] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 7;
          float *scorez = malloc(sizeof(float)); *scorez = scores[7];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[7] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[8] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 8;
          float *scorez = malloc(sizeof(float)); *scorez = scores[8];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[8] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[9] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 9;
          float *scorez = malloc(sizeof(float)); *scorez = scores[9];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[9] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(h, scorez, docid);
          }
        }
      }

      base += indexsum;
    }
  } else if (topics[n][1] == 3) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);

    for (i = start; i + jump < end; i += jump) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
      memset(scores, 0, sizeof(scores));
      for (j = 0; j < indexsum; j += 8) {
        cur = base + j;
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        } 
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
      }

      if (scores[0] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = scores[0];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[0] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[1] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 1;
          float *scorez = malloc(sizeof(float)); *scorez = scores[1];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[1] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[2] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 2;
          float *scorez = malloc(sizeof(float)); *scorez = scores[2];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[2] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[3] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 3;
          float *scorez = malloc(sizeof(float)); *scorez = scores[3];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[3] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[4] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 4;
          float *scorez = malloc(sizeof(float)); *scorez = scores[4];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[4] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[5] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 5;
          float *scorez = malloc(sizeof(float)); *scorez = scores[5];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[5] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[6] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 6;
          float *scorez = malloc(sizeof(float)); *scorez = scores[6];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[6] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[7] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 7;
          float *scorez = malloc(sizeof(float)); *scorez = scores[7];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[7] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[8] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 8;
          float *scorez = malloc(sizeof(float)); *scorez = scores[8];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[8] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[9] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 9;
          float *scorez = malloc(sizeof(float)); *scorez = scores[9];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[9] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(h, scorez, docid);
          }
        }
      }

      base += indexsum;
    }
  } else if (topics[n][1] == 4) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);

    for (i = start; i + jump < end; i += jump) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
      memset(scores, 0, sizeof(scores));
      for (j = 0; j < indexsum; j += 8) {
        cur = base + j;
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        } 
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        } 
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
      }

      if (scores[0] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = scores[0];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[0] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[1] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 1;
          float *scorez = malloc(sizeof(float)); *scorez = scores[1];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[1] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[2] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 2;
          float *scorez = malloc(sizeof(float)); *scorez = scores[2];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[2] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[3] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 3;
          float *scorez = malloc(sizeof(float)); *scorez = scores[3];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[3] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[4] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 4;
          float *scorez = malloc(sizeof(float)); *scorez = scores[4];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[4] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[5] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 5;
          float *scorez = malloc(sizeof(float)); *scorez = scores[5];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[5] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[6] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 6;
          float *scorez = malloc(sizeof(float)); *scorez = scores[6];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[6] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[7] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 7;
          float *scorez = malloc(sizeof(float)); *scorez = scores[7];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[7] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[8] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 8;
          float *scorez = malloc(sizeof(float)); *scorez = scores[8];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[8] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[9] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 9;
          float *scorez = malloc(sizeof(float)); *scorez = scores[9];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[9] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(h, scorez, docid);
          }
        }
      }

      base += indexsum;
    }
  } else if (topics[n][1] == 5) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
    __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);

    for (i = start; i + jump < end; i += jump) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
      memset(scores, 0, sizeof(scores));
      for (j = 0; j < indexsum; j += 8) {
        cur = base + j;
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_5)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
      }

      if (scores[0] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = scores[0];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[0] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[1] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 1;
          float *scorez = malloc(sizeof(float)); *scorez = scores[1];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[1] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[2] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 2;
          float *scorez = malloc(sizeof(float)); *scorez = scores[2];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[2] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[3] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 3;
          float *scorez = malloc(sizeof(float)); *scorez = scores[3];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[3] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[4] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 4;
          float *scorez = malloc(sizeof(float)); *scorez = scores[4];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[4] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[5] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 5;
          float *scorez = malloc(sizeof(float)); *scorez = scores[5];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[5] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[6] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 6;
          float *scorez = malloc(sizeof(float)); *scorez = scores[6];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[6] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[7] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 7;
          float *scorez = malloc(sizeof(float)); *scorez = scores[7];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[7] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[8] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 8;
          float *scorez = malloc(sizeof(float)); *scorez = scores[8];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[8] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[9] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 9;
          float *scorez = malloc(sizeof(float)); *scorez = scores[9];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[9] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(h, scorez, docid);
          }
        }
      }

      base += indexsum;
    }
  } else if (topics[n][1] == 6) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
    __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
    __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);

    for (i = start; i + jump < end; i += jump) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
      memset(scores, 0, sizeof(scores));
      for (j = 0; j < indexsum; j += 8) {
        cur = base + j;
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_5)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_6)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
      }

      if (scores[0] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = scores[0];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[0] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[1] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 1;
          float *scorez = malloc(sizeof(float)); *scorez = scores[1];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[1] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[2] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 2;
          float *scorez = malloc(sizeof(float)); *scorez = scores[2];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[2] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[3] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 3;
          float *scorez = malloc(sizeof(float)); *scorez = scores[3];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[3] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[4] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 4;
          float *scorez = malloc(sizeof(float)); *scorez = scores[4];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[4] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[5] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 5;
          float *scorez = malloc(sizeof(float)); *scorez = scores[5];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[5] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[6] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 6;
          float *scorez = malloc(sizeof(float)); *scorez = scores[6];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[6] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[7] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 7;
          float *scorez = malloc(sizeof(float)); *scorez = scores[7];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[7] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[8] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 8;
          float *scorez = malloc(sizeof(float)); *scorez = scores[8];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[8] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[9] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 9;
          float *scorez = malloc(sizeof(float)); *scorez = scores[9];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[9] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(h, scorez, docid);
          }
        }
      }

      base += indexsum;
    }
  } else if (topics[n][1] == 7) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
    __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
    __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);
    __m256i query_vec_7 = _mm256_set1_epi32(topics[n][8]);

    for (i = start; i + jump < end; i += jump) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
      memset(scores, 0, sizeof(scores));
      for (j = 0; j < indexsum; j += 8) {
        cur = base + j;
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_5)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_6)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_7)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
      }

      if (scores[0] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = scores[0];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[0] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[1] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 1;
          float *scorez = malloc(sizeof(float)); *scorez = scores[1];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[1] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[2] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 2;
          float *scorez = malloc(sizeof(float)); *scorez = scores[2];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[2] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[3] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 3;
          float *scorez = malloc(sizeof(float)); *scorez = scores[3];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[3] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[4] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 4;
          float *scorez = malloc(sizeof(float)); *scorez = scores[4];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[4] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[5] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 5;
          float *scorez = malloc(sizeof(float)); *scorez = scores[5];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[5] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[6] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 6;
          float *scorez = malloc(sizeof(float)); *scorez = scores[6];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[6] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[7] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 7;
          float *scorez = malloc(sizeof(float)); *scorez = scores[7];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[7] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[8] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 8;
          float *scorez = malloc(sizeof(float)); *scorez = scores[8];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[8] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[9] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 9;
          float *scorez = malloc(sizeof(float)); *scorez = scores[9];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[9] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(h, scorez, docid);
          }
        }
      }

      base += indexsum;
    }
  } else if (topics[n][1] == 8) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
    __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
    __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);
    __m256i query_vec_7 = _mm256_set1_epi32(topics[n][8]);
    __m256i query_vec_8 = _mm256_set1_epi32(topics[n][9]);

    for (i = start; i + jump < end; i += jump) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
      memset(scores, 0, sizeof(scores));
      for (j = 0; j < indexsum; j += 8) {
        cur = base + j;
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_5)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_6)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_7)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_8)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
      }

      if (scores[0] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = scores[0];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[0] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[1] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 1;
          float *scorez = malloc(sizeof(float)); *scorez = scores[1];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[1] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[2] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 2;
          float *scorez = malloc(sizeof(float)); *scorez = scores[2];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[2] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[3] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 3;
          float *scorez = malloc(sizeof(float)); *scorez = scores[3];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[3] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[4] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 4;
          float *scorez = malloc(sizeof(float)); *scorez = scores[4];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[4] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[5] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 5;
          float *scorez = malloc(sizeof(float)); *scorez = scores[5];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[5] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[6] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 6;
          float *scorez = malloc(sizeof(float)); *scorez = scores[6];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[6] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[7] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 7;
          float *scorez = malloc(sizeof(float)); *scorez = scores[7];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[7] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[8] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 8;
          float *scorez = malloc(sizeof(float)); *scorez = scores[8];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[8] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[9] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 9;
          float *scorez = malloc(sizeof(float)); *scorez = scores[9];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[9] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(h, scorez, docid);
          }
        }
      }

      base += indexsum;
    }
  } else if (topics[n][1] == 9) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
    __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
    __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);
    __m256i query_vec_7 = _mm256_set1_epi32(topics[n][8]);
    __m256i query_vec_8 = _mm256_set1_epi32(topics[n][9]);
    __m256i query_vec_9 = _mm256_set1_epi32(topics[n][10]);

    for (i = start; i + jump < end; i += jump) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
      memset(scores, 0, sizeof(scores));
      for (j = 0; j < indexsum; j += 8) {
        cur = base + j;
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_5)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_6)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_7)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_8)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_9)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
      }

      if (scores[0] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = scores[0];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[0] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[1] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 1;
          float *scorez = malloc(sizeof(float)); *scorez = scores[1];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[1] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[2] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 2;
          float *scorez = malloc(sizeof(float)); *scorez = scores[2];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[2] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[3] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 3;
          float *scorez = malloc(sizeof(float)); *scorez = scores[3];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[3] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[4] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 4;
          float *scorez = malloc(sizeof(float)); *scorez = scores[4];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[4] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[5] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 5;
          float *scorez = malloc(sizeof(float)); *scorez = scores[5];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[5] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[6] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 6;
          float *scorez = malloc(sizeof(float)); *scorez = scores[6];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[6] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[7] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 7;
          float *scorez = malloc(sizeof(float)); *scorez = scores[7];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[7] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[8] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 8;
          float *scorez = malloc(sizeof(float)); *scorez = scores[8];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[8] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[9] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 9;
          float *scorez = malloc(sizeof(float)); *scorez = scores[9];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[9] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(h, scorez, docid);
          }
        }
      }
 
      base += indexsum;
    }
  } else if (topics[n][1] == 10) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
    __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
    __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);
    __m256i query_vec_7 = _mm256_set1_epi32(topics[n][8]);
    __m256i query_vec_8 = _mm256_set1_epi32(topics[n][9]);
    __m256i query_vec_9 = _mm256_set1_epi32(topics[n][10]);
    __m256i query_vec_10 = _mm256_set1_epi32(topics[n][11]);

    for (i = start; i + jump < end; i += jump) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
      memset(scores, 0, sizeof(scores));
      for (j = 0; j < indexsum; j += 8) {
        cur = base + j;
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_5)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_6)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_7)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_8)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_9)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
        bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_10)));
        if (bits != 0) {
          int pos = (doc_pos[cur >> 3] + off) % DOCS_BLOCK_SIZE;
          scores[pos] = scores[pos] + prestore_score_padding[cur + map[bits]];
        }
      }

      if (scores[0] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = scores[0];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[0] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[1] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 1;
          float *scorez = malloc(sizeof(float)); *scorez = scores[1];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[1] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[2] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 2;
          float *scorez = malloc(sizeof(float)); *scorez = scores[2];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[2] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[3] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 3;
          float *scorez = malloc(sizeof(float)); *scorez = scores[3];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[3] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[4] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 4;
          float *scorez = malloc(sizeof(float)); *scorez = scores[4];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[4] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[5] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 5;
          float *scorez = malloc(sizeof(float)); *scorez = scores[5];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[5] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[6] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 6;
          float *scorez = malloc(sizeof(float)); *scorez = scores[6];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[6] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[7] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 7;
          float *scorez = malloc(sizeof(float)); *scorez = scores[7];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[7] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[8] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 8;
          float *scorez = malloc(sizeof(float)); *scorez = scores[8];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[8] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(h, scorez, docid);
          }
        }
      }
      if (scores[9] > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i + 9;
          float *scorez = malloc(sizeof(float)); *scorez = scores[9];
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (scores[9] > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(h, scorez, docid);
          }
        }
      }

      base += indexsum;
    }
  } else {
    for (i = start; i < end; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      float score = 0;
      for (j = 0; j < doclengths_ordered_padding[i]; j ++) {
        for (t = 2; t < 2 + topics[n][1]; t ++) {
          if (collection_tf_padding[base + j] == topics[n][t]) {
            score += prestore_score_padding[base + j];
          }
        }
      }

      if (score > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = score;
          heap_insert(h, scorez, docid);
        } else {
          heap_min(h, (void**)&min_key, (void**)&min_val);
          if (score > *min_key) {
            heap_delmin(h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score;
            heap_insert(h, scorez, docid);
          }
        }
      }

      base += doclengths_ordered_padding[i];
    }
  }

  for (; i < end; i ++) {
    if (tweetids[i] > topics_time[n]) {
      base += doclengths_ordered_padding[i];
      continue;
    }

    float score = 0;
    for (j = 0; j < doclengths_ordered_padding[i]; j ++) {
      for (t = 2; t < 2 + topics[n][1]; t ++) {
        if (collection_tf_padding[base + j] == topics[n][t]) {
          score += prestore_score_padding[base + j];
        }
      }
    }

    if (score > 0) {
      int size = heap_size(h);
      if (size < TOP_K) {
        int *docid = malloc(sizeof(int)); *docid = i;
        float *scorez = malloc(sizeof(float)); *scorez = score;
        heap_insert(h, scorez, docid);
      } else {
        heap_min(h, (void**)&min_key, (void**)&min_val);
        if (score > *min_key) {
          heap_delmin(h, (void**)&min_key, (void**)&min_val);
          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = score;
          heap_insert(h, scorez, docid);
        }
      }
    }

    base += doclengths_ordered_padding[i];
  }

  return 0;
}