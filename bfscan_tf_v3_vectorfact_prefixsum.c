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
  int i=0, j=0;

  clock_t begin, end;
  double time_spent;
  begin = clock();

  int base = 0;
  float score;
  __m256i collect_vec, mask, score_vec_i;
  __m256 score_vec, t1, t2;
  __m128 t3, t4;

  int n;
  int t;

  for (n=0; n<NUM_TOPICS; n++) {
    // printf("Processing topic %d...\n", topics2011[n][0]);

    heap h;
    heap_create(&h,0,NULL);

    float* min_key;
    int* min_val;
    float score_array[8];
    float score_vec_res[8];

    base = 0;
    if ( topics2011[n][1] == 2 ) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics2011[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics2011[n][3]);

      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered_simd[i]; j+=8) {
          collect_vec = _mm256_load_si256((__m256i *)&collection_tf_simd[base+j]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          }
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
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
      __m256i query_vec_1 = _mm256_set1_epi32(topics2011[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics2011[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics2011[n][4]);
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered_simd[i]; j+=8) {
          collect_vec = _mm256_load_si256((__m256i *)&collection_tf_simd[base+j]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          }
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
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
      __m256i query_vec_1 = _mm256_set1_epi32(topics2011[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics2011[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics2011[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics2011[n][5]);
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered_simd[i]; j+=8) {
          collect_vec = _mm256_load_si256((__m256i *)&collection_tf_simd[base+j]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          }
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
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
      __m256i query_vec_1 = _mm256_set1_epi32(topics2011[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics2011[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics2011[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics2011[n][5]);
      __m256i query_vec_5 = _mm256_set1_epi32(topics2011[n][6]);
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered_simd[i]; j+=8) {
          collect_vec = _mm256_load_si256((__m256i *)&collection_tf_simd[base+j]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          }
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_5);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
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
      __m256i query_vec_1 = _mm256_set1_epi32(topics2011[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics2011[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics2011[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics2011[n][5]);
      __m256i query_vec_5 = _mm256_set1_epi32(topics2011[n][6]);
      __m256i query_vec_6 = _mm256_set1_epi32(topics2011[n][7]);
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered_simd[i]; j+=8) {
          collect_vec = _mm256_load_si256((__m256i *)&collection_tf_simd[base+j]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          }
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
          if (_mm256_movemask_epi8(mask) != 0) {

            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_5);
          if (_mm256_movemask_epi8(mask) != 0) {

            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_6);
          if (_mm256_movemask_epi8(mask) != 0) {         
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
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
      __m256i query_vec_1 = _mm256_set1_epi32(topics2011[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics2011[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics2011[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics2011[n][5]);
      __m256i query_vec_5 = _mm256_set1_epi32(topics2011[n][6]);
      __m256i query_vec_6 = _mm256_set1_epi32(topics2011[n][7]);
      __m256i query_vec_7 = _mm256_set1_epi32(topics2011[n][8]);
      for (i=0; i<NUM_DOCS; i++) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        for (j=0; j<doclengths_ordered_simd[i]; j+=8) {
          collect_vec = _mm256_load_si256((__m256i *)&collection_tf_simd[base+j]);
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          }
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
          if (_mm256_movemask_epi8(mask) != 0) {

            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_5);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_6);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_7);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            score_vec_i = _mm256_castps_si256(score_vec);
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 32));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 64));
            score_vec_i = _mm256_add_epi32(score_vec_i, _mm256_srli_epi32(score_vec_i, 128));
            _mm256_store_ps(score_vec_res, _mm256_castsi256_ps(score_vec_i));
            score += score_vec_res[7];
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