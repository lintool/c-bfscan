#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#include "heap.h"
#include "topics2011.h"
#include "topics2011_time.h"
#include "constants.h"
#include "threadpool.h"

extern void init_tf();

int search(int n) {
  printf("# Thread working: %u\n", (int)pthread_self());
  int i=0, j=0;
  int base = 0;
  float score;
  int t;
  heap h;
  heap_create(&h,0,NULL);

  float* min_key;
  int* min_val;

  for (i=0; i<NUM_DOCS; i++) {
    if (tweetids[i] > topics2011_time[n]) {
      base += doclengths_ordered[i];
      continue;
    }
    score = 0;
    for (t=2; t<2+topics2011[n][1]; t++) {
      for (j=0; j<doclengths_ordered[i]; j++) {
        if (collection_tf[base+j] == topics2011[n][t]) {
            score += log(1 + tf[base+j]/(MU * (cf[topics2011[n][t]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }
      }
    }

    if (score > 0) {
      int size = heap_size(&h);

      if ( size < TOP_K ) {
        int *docid = malloc(sizeof(int)); *docid = i;
        float *scorez = malloc(sizeof(float)); *scorez = score;
        heap_insert(&h, scorez, docid);
      } else {
        heap_min(&h, (void**)&min_key, (void**)&min_val);

        if (score > *min_key) {
          heap_delmin(&h, (void**)&min_key, (void**)&min_val);

          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = score;
          heap_insert(&h, scorez, docid);
        }
      }
    }

    base += doclengths_ordered[i];
  }

  int rank = TOP_K;
  while (heap_delmin(&h, (void**)&min_key, (void**)&min_val)) {
    printf("MB%02d Q0 %ld %d %f bfscan_tf_v2_multithread_interquery\n", (n+1), tweetids[*min_val], rank, *min_key);
    rank--;
  }

  heap_destroy(&h);
  return 0;
}

int main(int argc, const char* argv[]) {
  int nthreads = atoi(argv[1]);
  printf("number of threads: %d\n", nthreads);
  init_tf();

  // clock_t begin, end;
  time_t begin, end;
  double time_spent;

  struct threadpool *pool;
  pool = threadpool_init(nthreads);
  
  // begin = clock();
  begin = time(NULL);
  int n;
  for (n=0; n<NUM_TOPICS; n++) {
    // printf("Processing topic %d...\n", topics2011[n][0]);
    threadpool_add_task(pool,search,(void*)n,0);
  }
  threadpool_free(pool,1);
  
  // end = clock();
  end = time(NULL);
  // time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  time_spent = (double)(end - begin);
  printf("Total time = %f ms\n", time_spent * 1000);
  printf("Time per query = %f ms\n", (time_spent * 1000)/NUM_TOPICS);
  printf("Throughput: %f qps\n", NUM_TOPICS/time_spent);
}
