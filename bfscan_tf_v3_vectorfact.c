#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "heap.h"
#include "topics2011.h"
#include "topics2011_time.h"
#include "constants.h"
// #include "emmintrin.h"
#include "immintrin.h"

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

    heap h;
    heap_create(&h,0,NULL);

    float* min_key;
    int* min_val;

    base = 0;
    if ( topics2011[n][1] == 2 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered_simd[i]; j+=8) {
          __m256i query_vec = _mm256_set1_epi32(topics2011[n][2]);
          __m256i collect_vec, mask;
          collect_vec = _mm256_load_si256((__m256i *)&collection_tf_simd[base+j]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          }
          query_vec = _mm256_set1_epi32(topics2011[n][3]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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

        base += doclengths_ordered_simd[i];
      }

    } else if ( topics2011[n][1] == 3 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered_simd[i]; j+=8) {
          __m256i query_vec = _mm256_set1_epi32(topics2011[n][2]);
          __m256i collect_vec, mask;
          collect_vec = _mm256_load_si256((__m256i *)&collection_tf_simd[base+j]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          }
          query_vec = _mm256_set1_epi32(topics2011[n][3]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][4]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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

        base += doclengths_ordered_simd[i];
      }
    } else if ( topics2011[n][1] == 4 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered_simd[i]; j+=8) {
          __m256i query_vec = _mm256_set1_epi32(topics2011[n][2]);
          __m256i collect_vec, mask;
          collect_vec = _mm256_load_si256((__m256i *)&collection_tf_simd[base+j]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          }
          query_vec = _mm256_set1_epi32(topics2011[n][3]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][4]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][5]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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

        base += doclengths_ordered_simd[i];
      }
    } else if ( topics2011[n][1] == 5 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered_simd[i]; j+=8) {
          __m256i query_vec = _mm256_set1_epi32(topics2011[n][2]);
          __m256i collect_vec, mask;
          collect_vec = _mm256_load_si256((__m256i *)&collection_tf_simd[base+j]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          }
          query_vec = _mm256_set1_epi32(topics2011[n][3]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][4]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][5]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][6]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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

        base += doclengths_ordered_simd[i];
      }
    } else if ( topics2011[n][1] == 6 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered_simd[i]; j+=8) {
          __m256i query_vec = _mm256_set1_epi32(topics2011[n][2]);
          __m256i collect_vec, mask;
          collect_vec = _mm256_load_si256((__m256i *)&collection_tf_simd[base+j]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          }
          query_vec = _mm256_set1_epi32(topics2011[n][3]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][4]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][5]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][6]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][7]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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

        base += doclengths_ordered_simd[i];
      }
    } else if ( topics2011[n][1] == 7 ) {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered_simd[i]; j+=8) {
          __m256i query_vec = _mm256_set1_epi32(topics2011[n][2]);
          __m256i collect_vec, mask;
          collect_vec = _mm256_load_si256((__m256i *)&collection_tf_simd[base+j]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][2]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          }
          query_vec = _mm256_set1_epi32(topics2011[n][3]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][3]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][4]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][4]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][5]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][5]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][6]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][6]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][7]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][7]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            }
          } 
          query_vec = _mm256_set1_epi32(topics2011[n][8]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec);
          if (_mm256_movemask_epi8(mask) != 0) {
            if (collection_tf_simd[base+j] == topics2011[n][8]) {
               score += log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+1] == topics2011[n][8]) {
               score += log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+2] == topics2011[n][8]) {
               score += log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+3] == topics2011[n][8]) {
               score += log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+4] == topics2011[n][8]) {
               score += log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+5] == topics2011[n][8]) {
               score += log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+6] == topics2011[n][8]) {
               score += log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            } else if (collection_tf_simd[base+j+7] == topics2011[n][8]) {
               score += log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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

        base += doclengths_ordered_simd[i];
      }
    } else {
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered_simd[i]; j++) {
          for (t=2; t<2+topics2011[n][1]; t++) {
            if ( collection_tf_simd[base+j] == topics2011[n][t]) {
              score+=log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][t]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
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

        base += doclengths_ordered_simd[i];
      }
    }

    int rank = TOP_K;
    while (heap_delmin(&h, (void**)&min_key, (void**)&min_val)) {
      printf("MB%02d Q0 %ld %d %f bfscan_tf_v3_vectorfact\n", (n+1), tweetids[*min_val], rank, *min_key);
      rank--;
    }

    heap_destroy(&h);
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total time = %f ms\n", time_spent * 1000);
  printf("Time per query = %f ms\n", (time_spent * 1000)/NUM_TOPICS);
  printf("Throughput: %f qps\n", NUM_TOPICS/time_spent);
    // }
}