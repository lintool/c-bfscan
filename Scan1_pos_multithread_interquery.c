#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>

#include "heap.h"
#include "topics2011.h"
#include "topics2011_time.h"
// #include "topics_1000.h"
// #include "topics_1000_time.h"
#include "constants.h"
#include "threadpool.h"

extern void init_pos();

int search(int n) {
  // printf("# Thread working: %u\n", (int)pthread_self());
  int i=0, j=0;
  int base=0;
  float score;
  int t;
  heap h;
  heap_create(&h,0,NULL);

  float* min_key;
  int* min_val;

  for (i=0; i<NUM_DOCS; i++) {
    if (tweetids[i] > topics2011_time[n]) {
      base += doclengths[i];
      continue;
    }
    score = 0;
    int tf[topics2011[n][1]];
    memset(tf,0,sizeof(tf));
    for (j=0; j<doclengths[i]; j++) {
      for (t=2; t<2+topics2011[n][1]; t++) {
        if (collection_pos[base+j] == topics2011[n][t]) {
          tf[t - 2] ++;
        }
      }
    }
    for (t = 0; t < topics2011[n][1]; t++) {
      if (tf[t] > 0) {
        score += log(1 + tf[t]/(MU * (cf[topics2011[n][t+2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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

    base += doclengths[i];
  }

  int rank = TOP_K;
  while (heap_delmin(&h, (void**)&min_key, (void**)&min_val)) {
    printf("MB%02d Q0 %ld %d %f Scan1_pos_multithread_interquery\n", (n+1), tweetids[*min_val], rank, *min_key);
    rank--;
  }

  heap_destroy(&h);
  return 0;
}

int main(int argc, const char* argv[]) {
  if (argc <= 1) {
    printf("PLEASE ENTER THREAD NUMBER!\n");
    return 0;
  }
  int nthreads=atoi(argv[1]);
  printf("Number of threads: %d\n", nthreads);
  init_pos();
  double total = 0;
  int N = 3;
  int count;
  for (count = 1; count <= N; count ++) {
    struct timeval begin, end;
    double time_spent;
    
    struct threadpool *pool;
    pool = threadpool_init(nthreads);
    gettimeofday(&begin, NULL);
    int n;
    for (n=0; n<NUM_TOPICS; n++) {
      // printf("Processing topic %d...\n", topics2011[n][0]);
      threadpool_add_task(pool,search,(void*)n,0);
    }
    threadpool_free(pool,1);
    
    gettimeofday(&end, NULL);
    time_spent = (double)((end.tv_sec * 1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec));
    total = total + time_spent / 1000.0;
  }
  printf("Total time = %f ms\n", total/N);
  printf("Throughput: %f qps\n", NUM_TOPICS/(total/N) * 1000);
}
