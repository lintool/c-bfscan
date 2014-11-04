#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "heap.h"
#include "topics2011.h"
#include "constants.h"

extern void init();

int main(int argc, const char* argv[]) {
  init();

  int i=0, j=0;

  clock_t begin, end;
  double time_spent;
  begin = clock();

  int base = 0;
  float score;

  int n;
  int t;

  for (n=0; n<49; n++) {
    printf("Processing topic %d...\n", topics2011[n][0]);

    heap h;
    heap_create(&h,0,NULL);

    float* min_key;
    int* min_val;

    base = 0;
    if ( topics2011[n][1] == 2 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
	  if (collection[base+j] == topics2011[n][2]) score+=log10(NUM_DOCS / df[2]);
	  if (collection[base+j] == topics2011[n][3]) score+=log10(NUM_DOCS / df[3]);
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
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
	  if (collection[base+j] == topics2011[n][2]) score+=log10(NUM_DOCS / df[2]);
	  if (collection[base+j] == topics2011[n][3]) score+=log10(NUM_DOCS / df[3]);
	  if (collection[base+j] == topics2011[n][4]) score+=log10(NUM_DOCS / df[4]);
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
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
	  if (collection[base+j] == topics2011[n][2]) score+=log10(NUM_DOCS / df[2]);
	  if (collection[base+j] == topics2011[n][3]) score+=log10(NUM_DOCS / df[3]);
	  if (collection[base+j] == topics2011[n][4]) score+=log10(NUM_DOCS / df[4]);
	  if (collection[base+j] == topics2011[n][5]) score+=log10(NUM_DOCS / df[5]);
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
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
	  if (collection[base+j] == topics2011[n][2]) score+=log10(NUM_DOCS / df[2]);
	  if (collection[base+j] == topics2011[n][3]) score+=log10(NUM_DOCS / df[3]);
	  if (collection[base+j] == topics2011[n][4]) score+=log10(NUM_DOCS / df[4]);
	  if (collection[base+j] == topics2011[n][5]) score+=log10(NUM_DOCS / df[5]);
	  if (collection[base+j] == topics2011[n][6]) score+=log10(NUM_DOCS / df[6]);
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
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
	  if (collection[base+j] == topics2011[n][2]) score+=log10(NUM_DOCS / df[2]);
	  if (collection[base+j] == topics2011[n][3]) score+=log10(NUM_DOCS / df[3]);
	  if (collection[base+j] == topics2011[n][4]) score+=log10(NUM_DOCS / df[4]);
	  if (collection[base+j] == topics2011[n][5]) score+=log10(NUM_DOCS / df[5]);
	  if (collection[base+j] == topics2011[n][6]) score+=log10(NUM_DOCS / df[6]);
	  if (collection[base+j] == topics2011[n][7]) score+=log10(NUM_DOCS / df[7]);
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
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
	  if (collection[base+j] == topics2011[n][2]) score+=log10(NUM_DOCS / df[2]);
	  if (collection[base+j] == topics2011[n][3]) score+=log10(NUM_DOCS / df[3]);
	  if (collection[base+j] == topics2011[n][4]) score+=log10(NUM_DOCS / df[4]);
	  if (collection[base+j] == topics2011[n][5]) score+=log10(NUM_DOCS / df[5]);
	  if (collection[base+j] == topics2011[n][6]) score+=log10(NUM_DOCS / df[6]);
	  if (collection[base+j] == topics2011[n][7]) score+=log10(NUM_DOCS / df[7]);
	  if (collection[base+j] == topics2011[n][8]) score+=log10(NUM_DOCS / df[8]);
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
      for (i=0; i<NUM_DOCS; i++) {
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
          for (t=2; t<2+topics2011[n][1]; t++) {
            if ( collection[base+j] == topics2011[n][t]) {
              score+=log10(NUM_DOCS / df[t]);
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

        base += doclengths[i];
      }
    }

    int rank = TOP_K;
    while (heap_delmin(&h, (void**)&min_key, (void**)&min_val)) {
      printf("%d Q0 %ld %d %f bfscan2\n", (n+1), tweetids[*min_val], rank, *min_key);
      rank--;
    }

    heap_destroy(&h);
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total time = %f ms\n", time_spent * 1000);
  printf("Time per query = %f ms\n", (time_spent * 1000)/49);
  printf("Throughput: %f qps\n", 49/time_spent);
}
