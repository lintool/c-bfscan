#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "heap.h"
#include "constants.h"

extern void init_tf(char * data_path);
int num_docs;
int total_terms;
int num_topics;
int main(int argc, const char* argv[]) {
  init_tf(argv[1]);
  
  int i=0, j=0;
  
  clock_t begin, end;
  double time_spent;
  begin = clock();

  int base = 0;
  float score;

  int n;
  int t;

  for (n=0; n<num_topics; n++) {
    heap h;
    heap_create(&h,0,NULL);

    float* min_key;
    int* min_val;

    base = 0;
    if ( topics[n][1] == 2 ) {
      for (i=0; i<num_docs; i++) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered[i]; j++) {
          if (collection_tf[base+j] == topics[n][2]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][3]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
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

    } else if ( topics[n][1] == 3 ) {
      for (i=0; i<num_docs; i++) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered[i]; j++) {
          if (collection_tf[base+j] == topics[n][2]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][3]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][4]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
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
    } else if ( topics[n][1] == 4 ) {
      for (i=0; i<num_docs; i++) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered[i]; j++) {
          if (collection_tf[base+j] == topics[n][2]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][3]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][4]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][5]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
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
    } else if ( topics[n][1] == 5 ) {
      for (i=0; i<num_docs; i++) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered[i]; j++) {
          if (collection_tf[base+j] == topics[n][2]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][3]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][4]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][5]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][6]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
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
    } else if ( topics[n][1] == 6 ) {
      for (i=0; i<num_docs; i++) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered[i]; j++) {
          if (collection_tf[base+j] == topics[n][2]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][3]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][4]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][5]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][6]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][7]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
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
    } else if ( topics[n][1] == 7 ) {
      for (i=0; i<num_docs; i++) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered[i]; j++) {
          if (collection_tf[base+j] == topics[n][2]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][3]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][4]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][5]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][6]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][7]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          if (collection_tf[base+j] == topics[n][8]) score+=log(1 + tf[base+j]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
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
      for (i=0; i<num_docs; i++) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered[i]; j++) {
          for (t=2; t<2+topics[n][1]; t++) {
            if ( collection_tf[base+j] == topics[n][t]) {
              score+=log(1 + tf[base+j]/(MU * (cf[topics[n][t]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
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
    }

    int rank = TOP_K;
    while (heap_delmin(&h, (void**)&min_key, (void**)&min_val)) {
      printf("MB%02d Q0 %ld %d %f Scan2\n", (n+1), tweetids[*min_val], rank, *min_key);
      rank--;
    }

    heap_destroy(&h);
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total time = %f ms\n", time_spent * 1000);
  printf("Time per query = %f ms\n", (time_spent * 1000)/num_topics);
  printf("Throughput: %f qps\n", num_topics/time_spent);
}