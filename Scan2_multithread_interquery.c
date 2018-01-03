#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>

#include "include/constants.h"
#include "include/data.c"
#include "include/heap.c"
#include "include/threadpool.c"

extern void init_tf(char *data_path);
int num_topics;
int num_docs;
long total_terms;

int search(int n) {
  int i, j, t;
  long base;
  
  heap h;
  heap_create(&h, 0, NULL);
  float* min_key;
  int* min_val;

  float score;

  base = 0;
  if (topics[n][1] == 1) {
    for (i = 0; i < num_docs; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered[i]; j ++) {
        if (collection_tf[base + j] == topics[n][2]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
      }

      if (score > 0) {
        int size = heap_size(&h);
        if (size < TOP_K) {
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
  } else if (topics[n][1] == 2) {
    for (i = 0; i < num_docs; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered[i]; j ++) {
        if (collection_tf[base + j] == topics[n][2]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][3]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
      }

      if (score > 0) {
        int size = heap_size(&h);
        if (size < TOP_K) {
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
  } else if (topics[n][1] == 3) {
    for (i = 0; i < num_docs; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered[i]; j ++) {
        if (collection_tf[base + j] == topics[n][2]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][3]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][4]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
      }

      if (score > 0) {
        int size = heap_size(&h);
        if (size < TOP_K) {
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
  } else if (topics[n][1] == 4) {
    for (i = 0; i < num_docs; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered[i]; j ++) {
        if (collection_tf[base + j] == topics[n][2]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][3]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][4]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][5]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
      }

      if (score > 0) {
        int size = heap_size(&h);
        if (size < TOP_K) {
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
  } else if (topics[n][1] == 5) {
    for (i = 0; i < num_docs; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered[i]; j ++) {
        if (collection_tf[base + j] == topics[n][2]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][3]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][4]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][5]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][6]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
      }

      if (score > 0) {
        int size = heap_size(&h);
        if (size < TOP_K) {
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
  } else if (topics[n][1] == 6) {
    for (i = 0; i < num_docs; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered[i]; j ++) {
        if (collection_tf[base + j] == topics[n][2]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][3]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][4]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][5]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][6]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][7]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
      }

      if (score > 0) {
        int size = heap_size(&h);
        if (size < TOP_K) {
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
  } else if (topics[n][1] == 7) {
    for (i = 0; i < num_docs; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered[i]; j ++) {
        if (collection_tf[base + j] == topics[n][2]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][3]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][4]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][5]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][6]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][7]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][8]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
      }

      if (score > 0) {
        int size = heap_size(&h);
        if (size < TOP_K) {
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
  } else if (topics[n][1] == 8) {
    for (i = 0; i < num_docs; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered[i]; j ++) {
        if (collection_tf[base + j] == topics[n][2]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][3]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][4]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][5]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][6]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][7]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][8]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][9]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
      }

      if (score > 0) {
        int size = heap_size(&h);
        if (size < TOP_K) {
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
  } else if (topics[n][1] == 9) {
    for (i = 0; i < num_docs; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered[i]; j ++) {
        if (collection_tf[base + j] == topics[n][2]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][3]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][4]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][5]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][6]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][7]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][8]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][9]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][10]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
      }

      if (score > 0) {
        int size = heap_size(&h);
        if (size < TOP_K) {
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
  } else if (topics[n][1] == 10) {
    for (i = 0; i < num_docs; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered[i]; j ++) {
        if (collection_tf[base + j] == topics[n][2]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][3]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][4]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][5]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][6]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][7]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][8]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][9]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][10]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
        if (collection_tf[base + j] == topics[n][11]) score += log(1 + tf[base + j]/(MU * (cf[topics[n][11]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
      }

      if (score > 0) {
        int size = heap_size(&h);
        if (size < TOP_K) {
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
    for (i = 0; i < num_docs; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered[i]; j ++) {
        for (t = 2; t < 2 + topics[n][1]; t ++) {
          if (collection_tf[base + j] == topics[n][t]) {
            score += log(1 + tf[base + j]/(MU * (cf[topics[n][t]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          }
        }
      }

      if (score > 0) {
        int size = heap_size(&h);
        if (size < TOP_K) {
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
    // printf("MB%02d Q0 %ld %d %f Scan2_multithread_interquery\n", (n + 1), tweetids[*min_val], rank, *min_key);
    rank --;
  }

  heap_destroy(&h);
  return 0;
}

int main(int argc, const char* argv[]) {
  if (argc <= 2) {
    printf("PLEASE ENTER DATA PATH AND THREAD NUMBER!\n");
    return 0;
  }

  int nthreads = atoi(argv[2]);
  printf("Number of threads: %d\n", nthreads);

  init_tf(argv[1]);
  int count;
  int N = 3;
  int n;
  double total = 0;
  for (count = 0; count < N; count ++) {
    struct threadpool *pool;
    pool = threadpool_init(nthreads);

    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    for (n = 0; n < num_topics; n ++) {
      threadpool_add_task(pool, search, (void*)n, 0);
    }
    threadpool_free(pool, 1);
    
    gettimeofday(&end, NULL);
    double time_spent = (double)((end.tv_sec * 1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec));
    total = total + time_spent / 1000.0;
    printf("Time = %f ms\n", total / num_topics);
  }
  // printf("Total time = %f ms\n", total / N);
  printf("Throughput: %f qps\n", num_topics / (total / N) * 1000);
}
