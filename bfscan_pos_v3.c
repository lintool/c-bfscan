#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "heap.h"
#include "topics2011_reordered.h"
#include "constants.h"

extern void init_pos();

int main(int argc, const char* argv[]) {
  init_pos();

  int i=0, j=0;

  clock_t begin, end;
  double time_spent;
  begin = clock();

  int base = 0;
  float score1, score2;

  int n;

  for (n=0; n<42; n+=2) {
    base = 0;

    heap h1;
    heap_create(&h1,0,NULL);
    heap h2;
    heap_create(&h2,0,NULL);

    float* min_key;
    int* min_val;

    int tf = 0;
    if ( topics2011[n][1] == 2 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score1 = 0;
        score2 = 0;

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        
        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][3]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][2]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][3]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        if (score1 > 0) {
          int size = heap_size(&h1);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h1, scorez, docid);
          } else {
            heap_min(&h1, (void**)&min_key, (void**)&min_val);

            if (score1 > *min_key) {
              heap_delmin(&h1, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score1;
              heap_insert(&h1, scorez, docid);
            }
          }
        }

        if (score2 > 0) {
          int size = heap_size(&h2);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h2, scorez, docid);
          } else {
            heap_min(&h2, (void**)&min_key, (void**)&min_val);

            if (score2 > *min_key) {
              heap_delmin(&h2, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score2;
              heap_insert(&h2, scorez, docid);
            }
          }
        }

        base += doclengths[i];
      }
    } else
    if ( topics2011[n][1] == 3 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score1 = 0;
        score2 = 0;

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        
        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][3]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][4]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][2]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][3]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][4]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        if (score1 > 0) {
          int size = heap_size(&h1);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h1, scorez, docid);
          } else {
            heap_min(&h1, (void**)&min_key, (void**)&min_val);

            if (score1 > *min_key) {
              heap_delmin(&h1, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score1;
              heap_insert(&h1, scorez, docid);
            }
        }
        }

        if (score2 > 0) {
          int size = heap_size(&h2);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h2, scorez, docid);
          } else {
            heap_min(&h2, (void**)&min_key, (void**)&min_val);

            if (score2 > *min_key) {
              heap_delmin(&h2, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score2;
              heap_insert(&h2, scorez, docid);
            }
        }
        }

        base += doclengths[i];
      }
    } else
    if ( topics2011[n][1] == 4 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score1 = 0;
        score2 = 0;

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        
        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][3]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][4]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][5]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][2]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][3]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][4]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][5]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][5]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));


        if (score1 > 0) {
          int size = heap_size(&h1);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h1, scorez, docid);
          } else {
            heap_min(&h1, (void**)&min_key, (void**)&min_val);

            if (score1 > *min_key) {
              heap_delmin(&h1, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score1;
              heap_insert(&h1, scorez, docid);
            }
        }
        }

        if (score2 > 0) {
          int size = heap_size(&h2);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h2, scorez, docid);
          } else {
            heap_min(&h2, (void**)&min_key, (void**)&min_val);

            if (score2 > *min_key) {
              heap_delmin(&h2, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score2;
              heap_insert(&h2, scorez, docid);
            }
        }
        }

        base += doclengths[i];
      }
    }else
    if ( topics2011[n][1] == 5 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score1 = 0;
        score2 = 0;

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        
        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][3]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][4]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][5]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][6]) tf ++;
        }
        if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][2]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][3]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][4]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][5]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][5]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        tf = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n+1][6]) tf ++;
        }
        if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][6]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        if (score1 > 0) {
          int size = heap_size(&h1);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h1, scorez, docid);
          } else {
            heap_min(&h1, (void**)&min_key, (void**)&min_val);

            if (score1 > *min_key) {
              heap_delmin(&h1, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score1;
              heap_insert(&h1, scorez, docid);
            }
        }
        }

        if (score2 > 0) {
          int size = heap_size(&h2);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h2, scorez, docid);
          } else {
            heap_min(&h2, (void**)&min_key, (void**)&min_val);

            if (score2 > *min_key) {
              heap_delmin(&h2, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score2;
              heap_insert(&h2, scorez, docid);
            }
        }
        }

        base += doclengths[i];
      }
    }

    int rank = TOP_K;
    while (heap_delmin(&h1, (void**)&min_key, (void**)&min_val)) {
      printf("%d Q0 %ld %d %f bfscan_pos_v3\n", topics2011[n][0], tweetids[*min_val], rank, *min_key);
      rank--;
    }
    heap_destroy(&h1);

    rank = TOP_K;
    while (heap_delmin(&h2, (void**)&min_key, (void**)&min_val)) {
      printf("%d Q0 %ld %d %f bfscan_pos_v3\n", topics2011[n+1][0], tweetids[*min_val], rank, *min_key);
      rank--;
    }
    heap_destroy(&h2);
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total time = %f ms\n", time_spent * 1000);
  printf("Time per query = %f ms\n", (time_spent * 1000)/42);
  printf("Throughput: %f qps\n", 42/time_spent);
}