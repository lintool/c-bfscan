#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "heap.h"
#include "topics2011.h"
#include "topics2011_time.h"
// #include "topics_1000.h"
// #include "topics_1000_time.h"
#include "constants.h"

extern void init_pos();

int main(int argc, const char* argv[]) {
  init_pos();

  int i=0, j=0;

  clock_t begin, end;
  double time_spent;
  begin = clock();

  int base = 0;
  float score;

  int n;
  int t;

  for (n=0; n<NUM_TOPICS; n++) {
    // printf("Processing topic %d...\n", topics2011[n][0]);

    heap h;
    heap_create(&h,0,NULL);

    float* min_key;
    int* min_val;

    base = 0;
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
      printf("MB%02d Q0 %ld %d %f Scan1_pos\n", (n+1), tweetids[*min_val], rank, *min_key);
      rank--;
    }

    heap_destroy(&h);
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total time = %f ms\n", time_spent * 1000);
  printf("Time per query = %f ms\n", (time_spent * 1000)/NUM_TOPICS);
  printf("Throughput: %f qps\n", NUM_TOPICS/time_spent);
}
