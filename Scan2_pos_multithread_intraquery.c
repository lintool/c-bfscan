#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>

#include "heap.h"
#include "termindexes.h"
#include "topics2011.h"
#include "topics2011_time.h"
// #include "topics_1000.h"
// #include "topics_1000_time.h"
#include "constants.h"
#include "threadpool.h"

struct arg_struct {
    int topic;
    int startidx;
    int endidx;
    int base;
    heap* h;
};

extern void init_pos();

int search(struct arg_struct *arg) {
  // printf("# Thread working: %u\n", (int)pthread_self());
  int n = arg->topic;
  int start = arg->startidx;
  int end = arg->endidx;
  heap* h = arg->h;
  heap_create(h,0,NULL);

  int i=0, j=0;
  int base = arg->base;
  float score;
  int t;
  float* min_key;
  int* min_val;

  if ( topics2011[n][1] == 1 ) {
    for (i=start; i<end; i++) {
      if (tweetids[i] > topics2011_time[n]) {
        base += doclengths[i];
        continue;
      }
      score = 0;
      int tf1 = 0;
      for (j=0; j<doclengths[i]; j++) {
        if (collection_pos[base+j] == topics2011[n][2]) tf1++;
      }
      if (tf1 > 0) {
        score+=log(1 + tf1/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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

      base += doclengths[i];
    }
  } else if ( topics2011[n][1] == 2 ) {
    for (i=start; i<end; i++) {
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

      base += doclengths[i];
    }

  } else if ( topics2011[n][1] == 3 ) {
    for (i=start; i<end; i++) {
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

      base += doclengths[i];
    }
  } else if ( topics2011[n][1] == 4 ) {
    for (i=start; i<end; i++) {
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

      base += doclengths[i];
    }
  } else if ( topics2011[n][1] == 5 ) {
    for (i=start; i<end; i++) {
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

      base += doclengths[i];
    }
  } else if ( topics2011[n][1] == 6 ) {
    for (i=start; i<end; i++) {
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

      base += doclengths[i];
    }
  } else if ( topics2011[n][1] == 7 ) {
    for (i=start; i<end; i++) {
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

      base += doclengths[i];
    }
  } else if ( topics2011[n][1] == 8 ) {
    for (i=start; i<end; i++) {
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
      int tf8 = 0;
      for (j=0; j<doclengths[i]; j++) {
        if (collection_pos[base+j] == topics2011[n][2]) tf1++;
        if (collection_pos[base+j] == topics2011[n][3]) tf2++;
        if (collection_pos[base+j] == topics2011[n][4]) tf3++;
        if (collection_pos[base+j] == topics2011[n][5]) tf4++;
        if (collection_pos[base+j] == topics2011[n][6]) tf5++;
        if (collection_pos[base+j] == topics2011[n][7]) tf6++;
        if (collection_pos[base+j] == topics2011[n][8]) tf7++;
        if (collection_pos[base+j] == topics2011[n][9]) tf8++;
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

      if (tf8 > 0) {
        score+=log(1 + tf8/(MU * (cf[topics2011[n][9]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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

      base += doclengths[i];
    }
  } else if ( topics2011[n][1] == 9 ) {
    for (i=start; i<end; i++) {
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
      int tf8 = 0;
      int tf9 = 0;
      for (j=0; j<doclengths[i]; j++) {
        if (collection_pos[base+j] == topics2011[n][2]) tf1++;
        if (collection_pos[base+j] == topics2011[n][3]) tf2++;
        if (collection_pos[base+j] == topics2011[n][4]) tf3++;
        if (collection_pos[base+j] == topics2011[n][5]) tf4++;
        if (collection_pos[base+j] == topics2011[n][6]) tf5++;
        if (collection_pos[base+j] == topics2011[n][7]) tf6++;
        if (collection_pos[base+j] == topics2011[n][8]) tf7++;
        if (collection_pos[base+j] == topics2011[n][9]) tf8++;
        if (collection_pos[base+j] == topics2011[n][10]) tf9++;
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

      if (tf8 > 0) {
        score+=log(1 + tf8/(MU * (cf[topics2011[n][9]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
      }

      if (tf9 > 0) {
        score+=log(1 + tf9/(MU * (cf[topics2011[n][10]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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

      base += doclengths[i];
    }
  } else if ( topics2011[n][1] == 10 ) {
    for (i=start; i<end; i++) {
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
      int tf8 = 0;
      int tf9 = 0;
      int tf10 = 0;
      for (j=0; j<doclengths[i]; j++) {
        if (collection_pos[base+j] == topics2011[n][2]) tf1++;
        if (collection_pos[base+j] == topics2011[n][3]) tf2++;
        if (collection_pos[base+j] == topics2011[n][4]) tf3++;
        if (collection_pos[base+j] == topics2011[n][5]) tf4++;
        if (collection_pos[base+j] == topics2011[n][6]) tf5++;
        if (collection_pos[base+j] == topics2011[n][7]) tf6++;
        if (collection_pos[base+j] == topics2011[n][8]) tf7++;
        if (collection_pos[base+j] == topics2011[n][9]) tf8++;
        if (collection_pos[base+j] == topics2011[n][10]) tf9++;
        if (collection_pos[base+j] == topics2011[n][11]) tf10++;
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

      if (tf8 > 0) {
        score+=log(1 + tf8/(MU * (cf[topics2011[n][9]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
      }

      if (tf9 > 0) {
        score+=log(1 + tf9/(MU * (cf[topics2011[n][10]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
      }

      if (tf10 > 0) {
        score+=log(1 + tf10/(MU * (cf[topics2011[n][11]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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

      base += doclengths[i];
    }
  } else {
    int tf = 0;
    for (i=start; i<end; i++) {
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

      base += doclengths[i];
    }
  }
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
    
    gettimeofday(&begin, NULL);
    int n;
    for (n=0; n<NUM_TOPICS; n++) {
      // printf("Processing topic %d...\n", topics2011[n][0]);
      heap h_array[nthreads];
      memset(h_array,0,sizeof(h_array));
      struct threadpool *pool;
      pool = threadpool_init(nthreads);
      int i = 0;
      for (i=0; i<nthreads; i++) {
        struct arg_struct *args = malloc(sizeof *args);
        args->topic = n;
        args->startidx = i*(int)(ceil((double)NUM_DOCS / nthreads));
        if ((i+1)*(int)(ceil((double)NUM_DOCS / nthreads)) > NUM_DOCS) {
          args->endidx = NUM_DOCS;
        } else {
          args->endidx = (i+1)*(int)(ceil((double)NUM_DOCS / nthreads));
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
        printf("MB%02d Q0 %ld %d %f Scan2_pos_multithread_intraquery\n", (n+1), tweetids[*min_val_merge], rank, *min_key_merge);
        rank--;
      }
      heap_destroy(&h_merge);
    }
    
    gettimeofday(&end, NULL);
    time_spent = (double)((end.tv_sec * 1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec));
    total = total + time_spent / 1000.0;
  }
  printf("Total time = %f ms\n", total/N);
  printf("Time per query = %f ms\n", (total/N)/NUM_TOPICS);
}
