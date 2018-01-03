#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>

#include "immintrin.h"
#include "include/constants.h"
#include "include/data.c"
#include "include/heap.c"
#include "include/threadpool.c"

struct arg_struct {
    int topic;
    int startidx;
    int endidx;
    long base;
    heap* h;
};

extern void init_tf(char *data_path);
int num_topics;
int num_docs;
long total_terms;

int search(struct arg_struct *arg) {
  int n, i, j, t;
  long base;

  __m256i collect_vec, mask;
  __m256 score_vec, t1, t2;
  __m128 t3, t4;

  heap* h = arg->h;
  heap_create(h, 0, NULL);
  float* min_key;
  int* min_val;

  float score_array[8];
  float score;

  n = arg->topic;
  int start = arg->startidx;
  int end = arg->endidx;
  base = arg->base;
  if (topics[n][1] == 1) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);

    for (i = start; i < end; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered_padding[i]; j += 8) {
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[base + j]);
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
      }

      if (score > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
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

      base += doclengths_ordered_padding[i];
    }
  } else if (topics[n][1] == 2) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);

    for (i = start; i < end; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered_padding[i]; j += 8) {
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[base + j]);
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
      }

      if (score > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
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

      base += doclengths_ordered_padding[i];
    }
  } else if (topics[n][1] == 3) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);

    for (i = start; i < end; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered_padding[i]; j += 8) {
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[base + j]);
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
      }

      if (score > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
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

      base += doclengths_ordered_padding[i];
    }
  } else if (topics[n][1] == 4) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);

    for (i = start; i < end; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered_padding[i]; j += 8) {
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[base + j]);
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
      }

      if (score > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
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

      base += doclengths_ordered_padding[i];
    }
  } else if (topics[n][1] == 5) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
    __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);

    for (i = start; i < end; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered_padding[i]; j += 8) {
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[base + j]);
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_5);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
      }

      if (score > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
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

      base += doclengths_ordered_padding[i];
    }
  } else if (topics[n][1] == 6) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
    __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
    __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);

    for (i = start; i < end; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered_padding[i]; j += 8) {
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[base + j]);
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_5);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_6);
        if (_mm256_movemask_epi8(mask) != 0) {         
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
      }

      if (score > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
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

      base += doclengths_ordered_padding[i];
    }
  } else if (topics[n][1] == 7) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
    __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
    __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);
    __m256i query_vec_7 = _mm256_set1_epi32(topics[n][8]);

    for (i = start; i < end; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered_padding[i]; j += 8) {
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[base + j]);
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_5);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_6);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_7);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }  
      }

      if (score > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
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

      base += doclengths_ordered_padding[i];
    }
  } else if (topics[n][1] == 8) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
    __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
    __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);
    __m256i query_vec_7 = _mm256_set1_epi32(topics[n][8]);
    __m256i query_vec_8 = _mm256_set1_epi32(topics[n][9]);

    for (i = start; i < end; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered_padding[i]; j += 8) {
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[base + j]);
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_5);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_6);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_7);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }  
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_8);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
      }

      if (score > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
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

      base += doclengths_ordered_padding[i];
    }
  } else if (topics[n][1] == 9) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
    __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
    __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);
    __m256i query_vec_7 = _mm256_set1_epi32(topics[n][8]);
    __m256i query_vec_8 = _mm256_set1_epi32(topics[n][9]);
    __m256i query_vec_9 = _mm256_set1_epi32(topics[n][10]);

    for (i = start; i < end; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered_padding[i]; j += 8) {
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[base + j]);
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_5);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_6);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_7);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }  
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_8);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_9);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
      }

      if (score > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
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

      base += doclengths_ordered_padding[i];
    }
  } else if (topics[n][1] == 10) {
    __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
    __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
    __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
    __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
    __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
    __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);
    __m256i query_vec_7 = _mm256_set1_epi32(topics[n][8]);
    __m256i query_vec_8 = _mm256_set1_epi32(topics[n][9]);
    __m256i query_vec_9 = _mm256_set1_epi32(topics[n][10]);
    __m256i query_vec_10 = _mm256_set1_epi32(topics[n][11]);

    for (i = start; i < end; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered_padding[i]; j += 8) {
        collect_vec = _mm256_loadu_si256(&collection_tf_padding[base + j]);
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_1);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_2);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_3);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_4);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_5);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_6);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_7);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }  
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_8);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_9);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
        mask = _mm256_cmpeq_epi32(collect_vec, query_vec_10);
        if (_mm256_movemask_epi8(mask) != 0) {
          memset(score_array, 0.0, sizeof(score_array));
          score_array[0] = log(1 + tf_padding[base + j]/(MU * (cf[topics[n][11]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[1] = log(1 + tf_padding[base + j + 1]/(MU * (cf[topics[n][11]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[2] = log(1 + tf_padding[base + j + 2]/(MU * (cf[topics[n][11]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[3] = log(1 + tf_padding[base + j + 3]/(MU * (cf[topics[n][11]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[4] = log(1 + tf_padding[base + j + 4]/(MU * (cf[topics[n][11]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[5] = log(1 + tf_padding[base + j + 5]/(MU * (cf[topics[n][11]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[6] = log(1 + tf_padding[base + j + 6]/(MU * (cf[topics[n][11]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_array[7] = log(1 + tf_padding[base + j + 7]/(MU * (cf[topics[n][11]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          score_vec = _mm256_load_ps((__m256 *)&score_array[0]);
          score_vec = _mm256_and_ps(score_vec, (__m256)mask);
          t1 = _mm256_hadd_ps(score_vec,score_vec);
          t2 = _mm256_hadd_ps(t1, t1);
          t3 = _mm256_extractf128_ps(t2, 1);
          t4 = _mm_add_ss(_mm256_castps256_ps128(t2), t3);
          score += _mm_cvtss_f32(t4);
        }
      }

      if (score > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
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

      base += doclengths_ordered_padding[i];
    }
  } else {
    for (i = start; i < end; i ++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered_padding[i]; j ++) {
        for (t = 2; t < 2 + topics[n][1]; t ++) {
          if (collection_tf_padding[base + j] == topics[n][t]) {
            score += log(1 + tf_padding[base + j]/(MU * (cf[topics[n][t]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          }
        }
      }

      if (score > 0) {
        int size = heap_size(h);
        if (size < TOP_K) {
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

      base += doclengths_ordered_padding[i];
    }
  }
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
  double total = 0;
  int count;
  int N = 3;
  int n, i;
  for (count = 0; count < N; count ++) {
    double time_spent;
    for (n = 0; n < num_topics; n ++) {
      heap h_array[nthreads];
      memset(h_array, 0, sizeof(h_array));
      struct threadpool *pool;
      pool = threadpool_init(nthreads);
      struct arg_struct* args[nthreads];
      for (i = 0; i < nthreads; i ++) {
        args[i] = malloc(sizeof(struct arg_struct));
        args[i]->topic = n;
        args[i]->startidx = i * (int)(ceil((double)num_docs / nthreads));
        if ((i + 1) * (int)(ceil((double)num_docs / nthreads)) > num_docs) {
          args[i]->endidx = num_docs;
        } else {
          args[i]->endidx = (i + 1) * (int)(ceil((double)num_docs / nthreads));
        }
        args[i]->base = termindexes[nthreads - 1][i];
        heap h;
        h_array[i] = h;
        args[i]->h = &h_array[i];
      }

      struct timeval begin, end;
      gettimeofday(&begin, NULL);
      for (i = 0; i < nthreads; i ++) {
        threadpool_add_task(pool, search, args[i], 0);
      }
      threadpool_free(pool, 1);

      heap h_merge;
      heap_create(&h_merge, 0, NULL);
      float* min_key_merge;
      int* min_val_merge;
      for (i = 0; i < nthreads; i ++) {
        float* min_key;
        int* min_val;
        while (heap_delmin(&h_array[i], (void**)&min_key, (void**)&min_val)) {
          int size = heap_size(&h_merge);
          if (size < TOP_K) {
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
        // printf("MB%02d Q0 %ld %d %f AVXScan1_multithread_intraquery\n", (n + 1), tweetids[*min_val_merge], rank, *min_key_merge);
        rank --;
      }
      heap_destroy(&h_merge);

      gettimeofday(&end, NULL);
      time_spent = (double)((end.tv_sec * 1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec));
      total = total + time_spent / 1000.0;
    }
    printf("Time = %f ms\n", total / num_topics);
  }
  // printf("Total time = %f ms\n", total / N);
  printf("Time per query = %f ms\n", (total / N) / num_topics);
}
