#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>

#include "include/constants.h"
#include "include/data.c"
#include "include/heap.c"
#include "include/threadpool.c"

struct arg_struct {
    int topic;
    int startidx;
    int endidx;
    long base;
    heap* h;
};

extern void init_tf_intra(char * data_path, char *query_path, bool padding);
int search(struct arg_struct *arg) {
  int n = arg->topic;
  int start = arg->startidx;
  int end = arg->endidx;
  heap* h = arg->h;
  heap_create(h,0,NULL);

  int i=0, j=0;
  long base = arg->base;
  float score;
  int t;
  float* min_key;
  int* min_val;

  for (i=start; i<end; i++) {
    // if (tweetids[i] > topics_time[n]) {
    //   base += doclengths_ordered[i];
    //   continue;
    // }
    score = 0;
    for (j=0; j<doclengths_ordered[i]; j++) {
      for (t=2; t<2+topics[n][1]; t++) {
        if (collection_tf[base+j] == topics[n][t]) {
            score += log(1 + tf[base+j]/(MU * (cf[topics[n][t]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        }
      }
    }

    if (score > 0) {
      int size = heap_size(h);

      if ( size < TOP_K ) {
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

    base += doclengths_ordered[i];
  }
  return 0;
}

int main(int argc, const char* argv[]) {
  if (argc <= 3) {
    printf("PLEASE ENTER STATS PATH, QUERY PATH AND THREAD NUMBER!\n");
    return 0;
  }
  int nthreads=atoi(argv[3]);
  printf("Number of threads: %d\n", nthreads);
  init_tf_intra(argv[1], argv[2], false);
  double total = 0;
  int N = 1;
  int count;
  for (count = 1; count <= N; count ++) {
    struct timeval begin, end;
    double time_spent;
    
    gettimeofday(&begin, NULL);
    int n;
    for (n=0; n<num_topics; n++) {
      heap h_array[nthreads];
      memset(h_array,0,sizeof(h_array));
      struct threadpool *pool;
      pool = threadpool_init(nthreads);
      int i = 0;
      for (i=0; i<nthreads; i++) {
        struct arg_struct *args = malloc(sizeof *args);
        args->topic = n;
        args->startidx = (int)(ceil(num_docs * 1.0 / nthreads) * i);
        if ((int)(ceil(num_docs * 1.0 / nthreads) * (i + 1)) > num_docs) {
          args->endidx = num_docs;
        } else {
          args->endidx = (int)(ceil(num_docs * 1.0 / nthreads) * (i + 1));
        }
        args->base = termindexes[nthreads-1][i];
        heap h;
        h_array[i] = h;
        args->h = &h_array[i];
        threadpool_add_task(pool,search,args,0);
      }
      threadpool_free(pool,1);

      heap h_merge;
      heap_create(&h_merge,0,NULL);
      float* min_key_merge;
      int* min_val_merge;
      for (i=0; i<nthreads; i++) {
        float* min_key;
        int* min_val;
        while(heap_delmin(&h_array[i], (void**)&min_key, (void**)&min_val)) {
          int size = heap_size(&h_merge);
          if ( size < TOP_K ) {
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
        printf("%d %ld %d %f Scan1_multithread_intraquery\n", (n+1), tweetids[*min_val_merge], rank, *min_key_merge);
        rank--;
      }
      heap_destroy(&h_merge);
    }
    
    gettimeofday(&end, NULL);
    time_spent = (double)((end.tv_sec * 1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec));
    total = total + time_spent / 1000.0;
  }
  printf("Total time = %f ms\n", total/N);
  printf("Time per query = %f ms\n", (total/N)/num_topics);
}
