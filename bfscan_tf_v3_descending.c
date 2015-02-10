#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "heap.h"
#include "topics2011_descending.h"
#include "topics2011_time.h"
#include "constants.h"

extern void init_tf();

int main(int argc, const char* argv[]) {
  init_tf();
  int count = 1;
    // for (count = 1; count <= 10; count ++) {
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
    int len = 0;
    int count = 0;
    heap h;
    heap_create(&h,0,NULL);

    float* min_key;
    int* min_val;

    base = 0;
    if ( topics2011[n][1] == 2 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        for (j=doclengths_ordered[i]-1; j>=0; j--) {
          if (collection_tf[base+j] > topics2011[n][3]) {len += doclengths_ordered[i]-1-j;count++; break;}
          if (collection_tf[base+j] == topics2011[n][2]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][3]) {score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));len += doclengths_ordered[i]-j;count++;break;}
          // if (collection_tf[base+j] == topics2011[n][3]) continue;
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

    } else if ( topics2011[n][1] == 3 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        for (j=doclengths_ordered[i]-1; j>=0; j--) {
          if (collection_tf[base+j] > topics2011[n][4]) {len += doclengths_ordered[i]-1-j; count++;break;}
          if (collection_tf[base+j] == topics2011[n][2]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][3]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][4]) {score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));len += doclengths_ordered[i]-j;count++;break;}
          // if (collection_tf[base+j] == topics2011[n][4]) continue;
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
    } else if ( topics2011[n][1] == 4 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        for (j=doclengths_ordered[i]-1; j>=0; j--) {
          if (collection_tf[base+j] > topics2011[n][5]) {len += doclengths_ordered[i]-1-j; count++;break;}
          if (collection_tf[base+j] == topics2011[n][2]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][3]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][4]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][5]) {score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));len += doclengths_ordered[i]-j;count++;break;}
          // if (collection_tf[base+j] == topics2011[n][5]) continue;
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
    } else if ( topics2011[n][1] == 5 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        for (j=doclengths_ordered[i]-1; j>=0; j--) {
          if (collection_tf[base+j] > topics2011[n][6]) {len += doclengths_ordered[i]-1-j; count++;break;}
          if (collection_tf[base+j] == topics2011[n][2]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][3]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][4]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][5]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][6]) {score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));len += doclengths_ordered[i]-j;count++;break;}
          // if (collection_tf[base+j] == topics2011[n][6]) continue;
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
    } else if ( topics2011[n][1] == 6 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        for (j=doclengths_ordered[i]-1; j>=0; j--) {
          if (collection_tf[base+j] > topics2011[n][7]) {len += doclengths_ordered[i]-1-j; count++;break;}
          if (collection_tf[base+j] == topics2011[n][2]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][3]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][4]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][5]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][6]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][7]) {score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));len += doclengths_ordered[i]-j;count++;break;}
          // if (collection_tf[base+j] == topics2011[n][7]) continue;
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
    } else if ( topics2011[n][1] == 7 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        for (j=doclengths_ordered[i]-1; j>=0; j--) {
          if (collection_tf[base+j] > topics2011[n][8]) {len += doclengths_ordered[i]-1-j; count++;break;}
          if (collection_tf[base+j] == topics2011[n][2]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][3]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][4]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][5]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][6]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][7]) score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics2011[n][8]) {score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));len += doclengths_ordered[i]-j;count++;break;}
          // if (collection_tf[base+j] == topics2011[n][8]) continue;
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
    } else {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        // for (j=0; j<doclengths_ordered[i]; j++) {
        //   for (t=2; t<2+topics2011[n][1]; t++) {
        //     if ( collection_tf[base+j] == topics2011[n][t]) {
        //       score+=log(1 + tf[base+j]/(MU * (cf[topics2011[n][t]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        //     }
        //   }
        // }
        t=2;
        j=0;
        while (t<2+topics2011[n][1] && j<doclengths_ordered[i]) {
          if (collection_tf[base+j] < topics2011[n][t]) {
            j++;
          } else if (collection_tf[base+j] > topics2011[n][t]) {
            t++;
          } else {
            score += log(1 + tf[base+j]/(MU * (cf[topics2011[n][t]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            j++;
            t++;
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
    }

    int rank = TOP_K;
    while (heap_delmin(&h, (void**)&min_key, (void**)&min_val)) {
      printf("MB%02d Q0 %ld %d %f bfscan_tf_v3\n", (n+1), tweetids[*min_val], rank, *min_key);
      rank--;
    }

    heap_destroy(&h);
    printf("check length:%f\n", (float)(len) / count);
  }

  
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total time = %f ms\n", time_spent * 1000);
  printf("Time per query = %f ms\n", (time_spent * 1000)/NUM_TOPICS);
  printf("Throughput: %f qps\n", NUM_TOPICS/time_spent);
    // }
}
