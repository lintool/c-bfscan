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
    if ( topics2011[n][1] == 2 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths[i];
          continue;
        }
        score = 0;
        int tf1 = 0;
        int tf2 = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf1++;
          if (collection_pos[base+j] == topics2011[n][3]) tf2++;
        }
        if (tf1 > 0) {
          score+=log(1 + tf1/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf2 > 0) {
          score+=log(1 + tf2/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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

    } else if ( topics2011[n][1] == 3 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths[i];
          continue;
        }
        score = 0;
        int tf1 = 0;
        int tf2 = 0;
        int tf3 = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf1++;
          if (collection_pos[base+j] == topics2011[n][3]) tf2++;
          if (collection_pos[base+j] == topics2011[n][4]) tf3++;
        }
        if (tf1 > 0) {
          score+=log(1 + tf1/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf2 > 0) {
          score+=log(1 + tf2/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf3 > 0) {
          score+=log(1 + tf3/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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
    } else if ( topics2011[n][1] == 4 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths[i];
          continue;
        }
        score = 0;
        int tf1 = 0;
        int tf2 = 0;
        int tf3 = 0;
        int tf4 = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf1++;
          if (collection_pos[base+j] == topics2011[n][3]) tf2++;
          if (collection_pos[base+j] == topics2011[n][4]) tf3++;
          if (collection_pos[base+j] == topics2011[n][5]) tf4++;
        }
        if (tf1 > 0) {
          score+=log(1 + tf1/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf2 > 0) {
          score+=log(1 + tf2/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf3 > 0) {
          score+=log(1 + tf3/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf4 > 0) {
          score+=log(1 + tf4/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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
    } else if ( topics2011[n][1] == 5 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths[i];
          continue;
        }
        score = 0;
        int tf1 = 0;
        int tf2 = 0;
        int tf3 = 0;
        int tf4 = 0;
        int tf5 = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf1++;
          if (collection_pos[base+j] == topics2011[n][3]) tf2++;
          if (collection_pos[base+j] == topics2011[n][4]) tf3++;
          if (collection_pos[base+j] == topics2011[n][5]) tf4++;
          if (collection_pos[base+j] == topics2011[n][6]) tf5++;
        }
        if (tf1 > 0) {
          score+=log(1 + tf1/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf2 > 0) {
          score+=log(1 + tf2/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf3 > 0) {
          score+=log(1 + tf3/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf4 > 0) {
          score+=log(1 + tf4/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf5 > 0) {
          score+=log(1 + tf5/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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
    } else if ( topics2011[n][1] == 6 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths[i];
          continue;
        }
        score = 0;
        int tf1 = 0;
        int tf2 = 0;
        int tf3 = 0;
        int tf4 = 0;
        int tf5 = 0;
        int tf6 = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf1++;
          if (collection_pos[base+j] == topics2011[n][3]) tf2++;
          if (collection_pos[base+j] == topics2011[n][4]) tf3++;
          if (collection_pos[base+j] == topics2011[n][5]) tf4++;
          if (collection_pos[base+j] == topics2011[n][6]) tf5++;
          if (collection_pos[base+j] == topics2011[n][7]) tf6++;
        }
        if (tf1 > 0) {
          score+=log(1 + tf1/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf2 > 0) {
          score+=log(1 + tf2/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf3 > 0) {
          score+=log(1 + tf3/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf4 > 0) {
          score+=log(1 + tf4/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf5 > 0) {
          score+=log(1 + tf5/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf6 > 0) {
          score+=log(1 + tf6/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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
    } else if ( topics2011[n][1] == 7 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths[i];
          continue;
        }
        score = 0;
        int tf1 = 0;
        int tf2 = 0;
        int tf3 = 0;
        int tf4 = 0;
        int tf5 = 0;
        int tf6 = 0;
        int tf7 = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf1++;
          if (collection_pos[base+j] == topics2011[n][3]) tf2++;
          if (collection_pos[base+j] == topics2011[n][4]) tf3++;
          if (collection_pos[base+j] == topics2011[n][5]) tf4++;
          if (collection_pos[base+j] == topics2011[n][6]) tf5++;
          if (collection_pos[base+j] == topics2011[n][7]) tf6++;
          if (collection_pos[base+j] == topics2011[n][8]) tf7++;
        }
        if (tf1 > 0) {
          score+=log(1 + tf1/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf2 > 0) {
          score+=log(1 + tf2/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf3 > 0) {
          score+=log(1 + tf3/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf4 > 0) {
          score+=log(1 + tf4/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf5 > 0) {
          score+=log(1 + tf5/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf6 > 0) {
          score+=log(1 + tf6/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
        }

        if (tf7 > 0) {
          score+=log(1 + tf7/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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
    } else {
      int tf = 0;
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths[i];
          continue;
        }
        score = 0;
        for (t=2; t<2+topics2011[n][1]; t++) {
          tf = 0;
          for (j=0; j<doclengths[i]; j++) {
            if (collection_pos[base+j] == topics2011[n][t]) {
              tf ++;
            }
          }
          if (tf > 0) {
            score += log(1 + tf/(MU * (cf[topics2011[n][t]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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
    }

    int rank = TOP_K;
    while (heap_delmin(&h, (void**)&min_key, (void**)&min_val)) {
      printf("MB%02d Q0 %ld %d %f Scan2_pos\n", (n+1), tweetids[*min_val], rank, *min_key);
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
