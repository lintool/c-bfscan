#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "heap.h"
#include "topics2011.h"
#include "topics2011_time.h"
#include "constants.h"

extern void init_tf();

int main(int argc, const char* argv[]) {
  init_tf();

  int i=0;

  clock_t begin, end;
  double time_spent;
  begin = clock();

  int base = 0;
  float score;

  int n;

  for (n=0; n<NUM_TOPICS; n++) {
    // printf("Processing topic %d...\n", topics2011[n][0]);

    heap h;
    heap_create(&h,0,NULL);

    float* min_key;
    int* min_val;

    base = 0;
    if ( topics2011[n][1] == 1 ) {
      double prob1;
      prob1 = MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1);
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        double plus = log(MU / (doclengths[i] + MU));

        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][2], prob1, plus);
        
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
    } else if ( topics2011[n][1] == 2 ) {
      double prob1, prob2;
      prob1 = MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1);
      prob2 = MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1);
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        double plus = log(MU / (doclengths[i] + MU));

        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][2], prob1, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][3], prob2, plus);
        
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
      double prob1, prob2, prob3;
      prob1 = MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1);
      prob2 = MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1);
      prob3 = MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1);
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        double plus = log(MU / (doclengths[i] + MU));

        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][2], prob1, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][3], prob2, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][4], prob3, plus);

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
      double prob1, prob2, prob3, prob4;
      prob1 = MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1);
      prob2 = MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1);
      prob3 = MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1);
      prob4 = MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1);
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        double plus = log(MU / (doclengths[i] + MU));

        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][2], prob1, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][3], prob2, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][4], prob3, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][5], prob4, plus);

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
      double prob1, prob2, prob3, prob4, prob5;
      prob1 = MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1);
      prob2 = MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1);
      prob3 = MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1);
      prob4 = MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1);
      prob5 = MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1);

      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        double plus = log(MU / (doclengths[i] + MU));

        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][2], prob1, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][3], prob2, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][4], prob3, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][5], prob4, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][6], prob5, plus);

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
      double prob1, prob2, prob3, prob4, prob5, prob6;
      prob1 = MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1);
      prob2 = MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1);
      prob3 = MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1);
      prob4 = MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1);
      prob5 = MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1);
      prob6 = MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1);

      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        double plus = log(MU / (doclengths[i] + MU));

        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][2], prob1, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][3], prob2, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][4], prob3, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][5], prob4, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][6], prob5, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][7], prob6, plus);

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
      double prob1, prob2, prob3, prob4, prob5, prob6, prob7;
      prob1 = MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1);
      prob2 = MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1);
      prob3 = MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1);
      prob4 = MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1);
      prob5 = MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1);
      prob6 = MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1);
      prob7 = MU * (cf[topics2011[n][8]] +  1) / (TOTAL_TERMS + 1);

      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered[i];
          continue;
        }
        score = 0;
        double plus = log(MU / (doclengths[i] + MU));

        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][2], prob1, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][3], prob2, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][4], prob3, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][5], prob4, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][6], prob5, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][7], prob6, plus);
        score += (*array_fun[doclengths_ordered[i]])(collection_tf, tf, base, topics2011[n][8], prob7, plus);

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
      printf("MB%02d Q0 %ld %d %f bfscan_tf_v4\n", (n+1), tweetids[*min_val], rank, *min_key);
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