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
  float score, score1, score2, score3, score4, score5, score6, score7;
  int indexsum1, indexsum2, indexsum3, indexsum4, indexsum5, indexsum6, indexsum7, indexsum8;
  __m256i collect_vec, mask;
  __m256 score_vec, t1, t2;
  __m128 t3, t4;

  int n;
  int t;
  int jump = 8;

  for (n=0; n<NUM_TOPICS; n++) {
    // printf("Processing topic %d...\n", topics2011[n][0]);

    heap h;
    heap_create(&h,0,NULL);

    float* min_key;
    int* min_val;
    float score_array[8];

    base = 0;
    if ( topics2011[n][1] == 2 ) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics2011[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics2011[n][3]);

      for (i=0; i<NUM_DOCS_PADDING; i+=jump) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        score1 = 0;
        score2 = 0;
        score3 = 0;
        score4 = 0;
        score5 = 0;
        score6 = 0;
        score7 = 0;
        indexsum1 = doclengths_ordered_simd[i];
        indexsum2 = indexsum1 + doclengths_ordered_simd[i+1];
        indexsum3 = indexsum2 + doclengths_ordered_simd[i+2];
        indexsum4 = indexsum3 + doclengths_ordered_simd[i+3];
        indexsum5 = indexsum4 + doclengths_ordered_simd[i+4];
        indexsum6 = indexsum5 + doclengths_ordered_simd[i+5];
        indexsum7 = indexsum6 + doclengths_ordered_simd[i+6];
        indexsum8 = indexsum7 + doclengths_ordered_simd[i+7];
        for (j=0; j<indexsum8; j+=8) {
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
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          }
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
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
        if (score1 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+1;
          float *scorez = malloc(sizeof(float)); *scorez = score1;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score1 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+1;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score2 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+2;
          float *scorez = malloc(sizeof(float)); *scorez = score2;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score2 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+2;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score3 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+3;
          float *scorez = malloc(sizeof(float)); *scorez = score3;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score3 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+3;
            float *scorez = malloc(sizeof(float)); *scorez = score3;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score4 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+4;
          float *scorez = malloc(sizeof(float)); *scorez = score4;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score4 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+4;
            float *scorez = malloc(sizeof(float)); *scorez = score4;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score5 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+5;
          float *scorez = malloc(sizeof(float)); *scorez = score5;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score5 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+5;
            float *scorez = malloc(sizeof(float)); *scorez = score5;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score6 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+6;
          float *scorez = malloc(sizeof(float)); *scorez = score6;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score6 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+6;
            float *scorez = malloc(sizeof(float)); *scorez = score6;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score7 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+7;
          float *scorez = malloc(sizeof(float)); *scorez = score7;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score7 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+7;
            float *scorez = malloc(sizeof(float)); *scorez = score7;
            heap_insert(&h, scorez, docid);
          }
        }
      }

        base += indexsum8;
      }

    } else if ( topics2011[n][1] == 3 ) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics2011[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics2011[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics2011[n][4]);
      for (i=0; i<NUM_DOCS_PADDING; i+=jump) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        score1 = 0;
        score2 = 0;
        score3 = 0;
        score4 = 0;
        score5 = 0;
        score6 = 0;
        score7 = 0;
        indexsum1 = doclengths_ordered_simd[i];
        indexsum2 = indexsum1 + doclengths_ordered_simd[i+1];
        indexsum3 = indexsum2 + doclengths_ordered_simd[i+2];
        indexsum4 = indexsum3 + doclengths_ordered_simd[i+3];
        indexsum5 = indexsum4 + doclengths_ordered_simd[i+4];
        indexsum6 = indexsum5 + doclengths_ordered_simd[i+5];
        indexsum7 = indexsum6 + doclengths_ordered_simd[i+6];
        indexsum8 = indexsum7 + doclengths_ordered_simd[i+7];
        for (j=0; j<indexsum8; j+=8) {
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
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          }
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
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
        if (score1 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+1;
          float *scorez = malloc(sizeof(float)); *scorez = score1;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score1 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+1;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score2 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+2;
          float *scorez = malloc(sizeof(float)); *scorez = score2;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score2 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+2;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score3 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+3;
          float *scorez = malloc(sizeof(float)); *scorez = score3;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score3 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+3;
            float *scorez = malloc(sizeof(float)); *scorez = score3;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score4 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+4;
          float *scorez = malloc(sizeof(float)); *scorez = score4;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score4 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+4;
            float *scorez = malloc(sizeof(float)); *scorez = score4;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score5 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+5;
          float *scorez = malloc(sizeof(float)); *scorez = score5;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score5 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+5;
            float *scorez = malloc(sizeof(float)); *scorez = score5;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score6 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+6;
          float *scorez = malloc(sizeof(float)); *scorez = score6;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score6 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+6;
            float *scorez = malloc(sizeof(float)); *scorez = score6;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score7 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+7;
          float *scorez = malloc(sizeof(float)); *scorez = score7;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score7 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+7;
            float *scorez = malloc(sizeof(float)); *scorez = score7;
            heap_insert(&h, scorez, docid);
          }
        }
      }

        base += indexsum8;
      }
    } else if ( topics2011[n][1] == 4 ) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics2011[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics2011[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics2011[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics2011[n][5]);
      for (i=0; i<NUM_DOCS_PADDING; i+=jump) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        score1 = 0;
        score2 = 0;
        score3 = 0;
        score4 = 0;
        score5 = 0;
        score6 = 0;
        score7 = 0;
        indexsum1 = doclengths_ordered_simd[i];
        indexsum2 = indexsum1 + doclengths_ordered_simd[i+1];
        indexsum3 = indexsum2 + doclengths_ordered_simd[i+2];
        indexsum4 = indexsum3 + doclengths_ordered_simd[i+3];
        indexsum5 = indexsum4 + doclengths_ordered_simd[i+4];
        indexsum6 = indexsum5 + doclengths_ordered_simd[i+5];
        indexsum7 = indexsum6 + doclengths_ordered_simd[i+6];
        indexsum8 = indexsum7 + doclengths_ordered_simd[i+7];
        for (j=0; j<indexsum8; j+=8) {
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
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          }
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
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
        if (score1 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+1;
          float *scorez = malloc(sizeof(float)); *scorez = score1;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score1 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+1;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score2 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+2;
          float *scorez = malloc(sizeof(float)); *scorez = score2;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score2 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+2;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score3 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+3;
          float *scorez = malloc(sizeof(float)); *scorez = score3;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score3 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+3;
            float *scorez = malloc(sizeof(float)); *scorez = score3;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score4 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+4;
          float *scorez = malloc(sizeof(float)); *scorez = score4;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score4 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+4;
            float *scorez = malloc(sizeof(float)); *scorez = score4;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score5 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+5;
          float *scorez = malloc(sizeof(float)); *scorez = score5;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score5 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+5;
            float *scorez = malloc(sizeof(float)); *scorez = score5;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score6 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+6;
          float *scorez = malloc(sizeof(float)); *scorez = score6;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score6 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+6;
            float *scorez = malloc(sizeof(float)); *scorez = score6;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score7 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+7;
          float *scorez = malloc(sizeof(float)); *scorez = score7;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score7 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+7;
            float *scorez = malloc(sizeof(float)); *scorez = score7;
            heap_insert(&h, scorez, docid);
          }
        }
      }

        base += indexsum8;
      }
    } else if ( topics2011[n][1] == 5 ) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics2011[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics2011[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics2011[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics2011[n][5]);
      __m256i query_vec_5 = _mm256_set1_epi32(topics2011[n][6]);
      for (i=0; i<NUM_DOCS_PADDING; i+=jump) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        score1 = 0;
        score2 = 0;
        score3 = 0;
        score4 = 0;
        score5 = 0;
        score6 = 0;
        score7 = 0;
        indexsum1 = doclengths_ordered_simd[i];
        indexsum2 = indexsum1 + doclengths_ordered_simd[i+1];
        indexsum3 = indexsum2 + doclengths_ordered_simd[i+2];
        indexsum4 = indexsum3 + doclengths_ordered_simd[i+3];
        indexsum5 = indexsum4 + doclengths_ordered_simd[i+4];
        indexsum6 = indexsum5 + doclengths_ordered_simd[i+5];
        indexsum7 = indexsum6 + doclengths_ordered_simd[i+6];
        indexsum8 = indexsum7 + doclengths_ordered_simd[i+7];
        for (j=0; j<indexsum8; j+=8) {
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
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          }
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_5);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
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
        if (score1 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+1;
          float *scorez = malloc(sizeof(float)); *scorez = score1;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score1 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+1;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score2 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+2;
          float *scorez = malloc(sizeof(float)); *scorez = score2;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score2 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+2;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score3 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+3;
          float *scorez = malloc(sizeof(float)); *scorez = score3;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score3 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+3;
            float *scorez = malloc(sizeof(float)); *scorez = score3;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score4 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+4;
          float *scorez = malloc(sizeof(float)); *scorez = score4;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score4 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+4;
            float *scorez = malloc(sizeof(float)); *scorez = score4;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score5 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+5;
          float *scorez = malloc(sizeof(float)); *scorez = score5;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score5 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+5;
            float *scorez = malloc(sizeof(float)); *scorez = score5;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score6 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+6;
          float *scorez = malloc(sizeof(float)); *scorez = score6;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score6 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+6;
            float *scorez = malloc(sizeof(float)); *scorez = score6;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score7 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+7;
          float *scorez = malloc(sizeof(float)); *scorez = score7;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score7 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+7;
            float *scorez = malloc(sizeof(float)); *scorez = score7;
            heap_insert(&h, scorez, docid);
          }
        }
      }

        base += indexsum8;
      }
    } else if ( topics2011[n][1] == 6 ) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics2011[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics2011[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics2011[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics2011[n][5]);
      __m256i query_vec_5 = _mm256_set1_epi32(topics2011[n][6]);
      __m256i query_vec_6 = _mm256_set1_epi32(topics2011[n][7]);
      for (i=0; i<NUM_DOCS_PADDING; i+=jump) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        score1 = 0;
        score2 = 0;
        score3 = 0;
        score4 = 0;
        score5 = 0;
        score6 = 0;
        score7 = 0;
        indexsum1 = doclengths_ordered_simd[i];
        indexsum2 = indexsum1 + doclengths_ordered_simd[i+1];
        indexsum3 = indexsum2 + doclengths_ordered_simd[i+2];
        indexsum4 = indexsum3 + doclengths_ordered_simd[i+3];
        indexsum5 = indexsum4 + doclengths_ordered_simd[i+4];
        indexsum6 = indexsum5 + doclengths_ordered_simd[i+5];
        indexsum7 = indexsum6 + doclengths_ordered_simd[i+6];
        indexsum8 = indexsum7 + doclengths_ordered_simd[i+7];
        for (j=0; j<indexsum8; j+=8) {
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
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          }
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
          if (_mm256_movemask_epi8(mask) != 0) {

            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_5);
          if (_mm256_movemask_epi8(mask) != 0) {

            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_6);
          if (_mm256_movemask_epi8(mask) != 0) {         
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
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
        if (score1 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+1;
          float *scorez = malloc(sizeof(float)); *scorez = score1;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score1 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+1;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score2 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+2;
          float *scorez = malloc(sizeof(float)); *scorez = score2;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score2 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+2;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score3 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+3;
          float *scorez = malloc(sizeof(float)); *scorez = score3;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score3 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+3;
            float *scorez = malloc(sizeof(float)); *scorez = score3;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score4 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+4;
          float *scorez = malloc(sizeof(float)); *scorez = score4;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score4 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+4;
            float *scorez = malloc(sizeof(float)); *scorez = score4;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score5 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+5;
          float *scorez = malloc(sizeof(float)); *scorez = score5;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score5 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+5;
            float *scorez = malloc(sizeof(float)); *scorez = score5;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score6 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+6;
          float *scorez = malloc(sizeof(float)); *scorez = score6;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score6 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+6;
            float *scorez = malloc(sizeof(float)); *scorez = score6;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score7 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+7;
          float *scorez = malloc(sizeof(float)); *scorez = score7;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score7 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+7;
            float *scorez = malloc(sizeof(float)); *scorez = score7;
            heap_insert(&h, scorez, docid);
          }
        }
      }

        base += indexsum8;
      }
    } else if ( topics2011[n][1] == 7 ) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics2011[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics2011[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics2011[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics2011[n][5]);
      __m256i query_vec_5 = _mm256_set1_epi32(topics2011[n][6]);
      __m256i query_vec_6 = _mm256_set1_epi32(topics2011[n][7]);
      __m256i query_vec_7 = _mm256_set1_epi32(topics2011[n][8]);
      for (i=0; i<NUM_DOCS_PADDING; i+=jump) {
        if (tweetids[i] > topics2011_time[n]) {
          base += doclengths_ordered_simd[i];
          continue;
        }
        score = 0;
        score1 = 0;
        score2 = 0;
        score3 = 0;
        score4 = 0;
        score5 = 0;
        score6 = 0;
        score7 = 0;
        indexsum1 = doclengths_ordered_simd[i];
        indexsum2 = indexsum1 + doclengths_ordered_simd[i+1];
        indexsum3 = indexsum2 + doclengths_ordered_simd[i+2];
        indexsum4 = indexsum3 + doclengths_ordered_simd[i+3];
        indexsum5 = indexsum4 + doclengths_ordered_simd[i+4];
        indexsum6 = indexsum5 + doclengths_ordered_simd[i+5];
        indexsum7 = indexsum6 + doclengths_ordered_simd[i+6];
        indexsum8 = indexsum7 + doclengths_ordered_simd[i+7];
        for (j=0; j<indexsum8; j+=8) {
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
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          }
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
          if (_mm256_movemask_epi8(mask) != 0) {

            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_5);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_6);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][7]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
            }
          } 
          mask = _mm256_cmpeq_epi32(collect_vec, query_vec_7);
          if (_mm256_movemask_epi8(mask) != 0) {
            memset(score_array, 0.0, sizeof(score_array));
            score_array[0] = log(1 + tf_simd[base+j]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[1] = log(1 + tf_simd[base+j+1]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[2] = log(1 + tf_simd[base+j+2]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[3] = log(1 + tf_simd[base+j+3]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[4] = log(1 + tf_simd[base+j+4]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[5] = log(1 + tf_simd[base+j+5]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[6] = log(1 + tf_simd[base+j+6]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_array[7] = log(1 + tf_simd[base+j+7]/(MU * (cf[topics2011[n][8]] + 1) / (TOTAL_TERMS + 1))) + log(MU / (doclengths[i] + MU));
            score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
            score_vec = _mm256_and_ps(score_vec, mask);
            t1 = _mm256_hadd_ps(score_vec,score_vec);
            t2 = _mm256_hadd_ps(t1,t1);
            t3 = _mm256_extractf128_ps(t2,1);
            t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
            if(j >= indexsum7) {
              score7 = score7 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum6) {
              score6 = score6 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum5) {
              score5 = score5 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum4) {
              score4 = score4 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum3) {
              score3 = score3 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum2) {
              score2 = score2 + _mm_cvtss_f32(t4);
            } else if(j >= indexsum1) {
              score1 = score1 + _mm_cvtss_f32(t4);
            } else {
              score = score + _mm_cvtss_f32(t4);
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
        if (score1 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+1;
          float *scorez = malloc(sizeof(float)); *scorez = score1;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score1 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+1;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score2 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+2;
          float *scorez = malloc(sizeof(float)); *scorez = score2;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score2 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+2;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score3 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+3;
          float *scorez = malloc(sizeof(float)); *scorez = score3;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score3 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+3;
            float *scorez = malloc(sizeof(float)); *scorez = score3;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score4 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+4;
          float *scorez = malloc(sizeof(float)); *scorez = score4;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score4 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+4;
            float *scorez = malloc(sizeof(float)); *scorez = score4;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score5 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+5;
          float *scorez = malloc(sizeof(float)); *scorez = score5;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score5 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+5;
            float *scorez = malloc(sizeof(float)); *scorez = score5;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score6 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+6;
          float *scorez = malloc(sizeof(float)); *scorez = score6;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score6 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+6;
            float *scorez = malloc(sizeof(float)); *scorez = score6;
            heap_insert(&h, scorez, docid);
          }
        }
      }
      if (score7 > 0) {
        int size = heap_size(&h);

        if ( size < TOP_K ) {
          int *docid = malloc(sizeof(int)); *docid = i+7;
          float *scorez = malloc(sizeof(float)); *scorez = score7;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);

          if (score7 > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);

            int *docid = malloc(sizeof(int)); *docid = i+7;
            float *scorez = malloc(sizeof(float)); *scorez = score7;
            heap_insert(&h, scorez, docid);
          }
        }
      }

        base += indexsum8;
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
      printf("MB%02d Q0 %ld %d %f bfscan_tf_v3_vectorfact_nonbranch\n", (n+1), tweetids[*min_val], rank, *min_key);
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