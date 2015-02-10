#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#include "heap.h"
#include "termindexes.h"
#include "topics2011.h"
#include "topics2011_time.h"
#include "constants.h"
#include "threadpool.h"

struct arg_struct {
    int topic;
    int startidx;
    int endidx;
    int base;
    heap* h;
};

extern void init_tf();

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
  __m256i collect_vec, mask;
  __m256 score_vec, t1, t2;
  __m128 t3, t4;

  float* min_key;
  int* min_val;
  float score_array[8];

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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1,t1);
          t3 = _mm256_extractf128_ps(t2,1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
          score += _mm_cvtss_f32(t4);
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
  return 0;
}

int main(int argc, const char* argv[]) {
  int nthreads = atoi(argv[1]);
  printf("number of threads: %d\n", nthreads);
  init_tf();
  int count = 1;
    for (count = 1; count <= 10; count ++) {

  // clock_t begin, end;
  struct timeval begin, end;
  double time_spent;
  
  // begin = clock();
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
          if (*min_key_merge > *min_key) {
            heap_delmin(&h_merge, (void**)&min_key_merge, (void**)&min_val_merge);
            heap_insert(&h_merge, min_key, min_val);
          }
        }
      }
      heap_destroy(&h_array[i]);
    }

    int rank = TOP_K;
    while (heap_delmin(&h_merge, (void**)&min_key_merge, (void**)&min_val_merge)) {
      printf("MB%02d Q0 %ld %d %f bfscan_tf_v3_multithread_intraquery\n", (n+1), tweetids[*min_val_merge], rank, *min_key_merge);
      rank--;
    }
    heap_destroy(&h_merge);
  }
  
  // end = clock();
  gettimeofday(&end, NULL);
  // time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  time_spent = (double)((end.tv_sec * 1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec));
  printf("Total time = %f ms\n", time_spent / 1000);
  printf("Time per query = %f ms\n", (time_spent / 1000)/NUM_TOPICS);
  printf("Throughput: %f qps\n", NUM_TOPICS/(time_spent / 1000000));
    }
}