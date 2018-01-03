#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#include "constants.h"

int num_docs;
long total_terms;
int num_topics = sizeof(topics_time) / sizeof(topics_time[0]);
long sum;
float min_score, max_score;

FILE * concat_fopen(char *s1, char *s2, char *mode) {
  char str[strlen (s1) + strlen (s2) + 1];
  strcpy (str, s1);
  strcat (str, s2);
  if (mode == "w+") {
    remove(str);
  }
  return fopen (str, mode);
}

void init_tf(char *data_path) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  long i = 0;
  long stats[4];
  fp = concat_fopen(data_path, "/stats.txt", "r");
  if (fp == NULL) {printf("Error!\n"); exit(-1);}
  // printf("-> Reading from stats.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
     stats[i] = atol(line);
     i ++;
  }
  fclose(fp);
  num_docs = (int)stats[0];
  total_terms = stats[2];
  int num_terms = (int)stats[3];

  long total_terms_unique_per_doc = stats[1];
  collection_tf = malloc(total_terms_unique_per_doc * sizeof(uint32_t));
  i = 0;
  fp = concat_fopen(data_path, "/all_terms_ordered.txt", "r");
  if (fp == NULL) {printf("Error!\n"); exit(-1);}
  // printf("-> Reading collection from all_terms_ordered.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    collection_tf[i ++] = atol(line);
    // if (i % 10000000 == 0 ) printf("  %ld terms...\n", i);
  }
  // printf("Total of %ld terms ordered read\n\n", i);
  fclose(fp);

  tf = malloc(total_terms_unique_per_doc * sizeof(uint8_t));
  i = 0;
  fp = concat_fopen(data_path, "/all_terms_tf.txt", "r");
  if (fp == NULL) {printf("Error!\n"); exit(-1);}
  // printf("-> Reading tf from all_terms_tf.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    tf[i ++] = atoi(line);
    // if (i % 10000000 == 0 ) printf("  %ld tfs...\n", i);
  }
  // printf("Total of %ld tfs read\n\n", i);
  fclose(fp);

  doclengths_ordered = malloc(num_docs * sizeof(uint8_t));
  doclengths_ordered_padding = malloc(num_docs * sizeof(uint8_t));
  i = 0;
  sum = 0;
  fp = concat_fopen(data_path, "/doc_length_ordered.txt", "r");
  if (fp == NULL) {printf("Error!\n"); exit(-1);}
  // printf("-> Reading doclengths from doc_length_ordered.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    doclengths_ordered[i] = atoi(line);
    if (atoi(line) % BLOCK_SIZE == 0) {
      doclengths_ordered_padding[i] = atoi(line);
    } else {
      doclengths_ordered_padding[i] = atoi(line) + (BLOCK_SIZE - atoi(line) % BLOCK_SIZE);
    }
    sum += doclengths_ordered_padding[i++];
    // if (i % 1000000 == 0 ) printf("  %d ordered lengths...\n", i);
  }
  // printf("Total of %d doclengths ordered read\n\n", i);
  fclose(fp);

  collection_tf_padding = malloc(sum * sizeof(uint32_t));
  tf_padding = malloc(sum * sizeof(uint8_t));
  doc_pos = malloc((sum / BLOCK_SIZE) * sizeof(uint8_t));
  long base = 0;
  int j = 0;
  long i_padding = 0;
  int i_pos = 0;
  int pos = 0;
  for (i = 0; i < num_docs; i ++) {
    for (j = 0; j < doclengths_ordered[i]; j ++) {
      collection_tf_padding[i_padding] = collection_tf[base + j];
      tf_padding[i_padding] = tf[base + j];
      // doc_pos[i_padding] = pos % DOCS_BLOCK_SIZE;
      i_padding++;
    }
    for (j = doclengths_ordered[i]; j < doclengths_ordered_padding[i]; j ++) {
      collection_tf_padding[i_padding] = 0;
      tf_padding[i_padding] = 0;
      // doc_pos[i_padding] = pos % DOCS_BLOCK_SIZE;
      i_padding++;
    }
    for (j = 0; j < doclengths_ordered_padding[i] / BLOCK_SIZE; j ++) {
      doc_pos[i_pos] = pos % DOCS_BLOCK_SIZE;
      i_pos ++;
    }
    pos ++;
    base += doclengths_ordered[i];
  }

  tweetids = malloc(num_docs * sizeof(uint64_t));
  i = 0;
  fp = concat_fopen(data_path, "/doc_id.txt", "r");
  if (fp == NULL) {printf("Error!\n"); exit(-1);}
  // printf("-> Reading tweetids from doc_id.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    tweetids[i ++] = atol(line);
    // if (i % 1000000 == 0 ) printf("  %d tweetids...\n", i);
  }
  // printf("Total of %d tweetids read\n\n", i);
  fclose(fp);

  doclengths = malloc(num_docs * sizeof(uint8_t));  
  i = 0;
  fp = concat_fopen(data_path, "/doc_length.txt", "r");
  if (fp == NULL) {printf("Error!\n"); exit(-1);}
  // printf("-> Reading doclengths from doc_length.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    doclengths[i ++] = atoi(line);
    // if (i % 1000000 == 0 ) printf("  %d lengths...\n", i);
  }
  // printf("Total of %d doclengths read\n\n", i);
  fclose(fp);

  cf = malloc((num_terms + 1) * sizeof(uint32_t));  
  i = 1;
  fp = concat_fopen(data_path, "/cf_table.txt", "r");
  if (fp == NULL) {printf("Error!\n"); exit(-1);}
  // printf("-> Reading cfs from cf_table.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    cf[i ++] = atoi(line);
    // if (i % 1000000 == 0 ) printf("  %d terms...\n", i);
  }
  // printf("Total of %d terms read\n\n", i);
  fclose(fp);

  if (line) {free(line);}
}

void init_tf_prestore_score(char *data_path) {
  init_tf(data_path);

  prestore_score_padding = malloc(sum * sizeof(float));
  memset(prestore_score_padding, 0, sizeof(prestore_score_padding));
  
  int i, j;
  long base = 0;
  for (i = 0; i < num_docs; i ++) {
    for (j = 0; j < doclengths_ordered[i]; j ++) {
      prestore_score_padding[base + j] = log(1 + tf_padding[base + j] / (MU * (cf[collection_tf_padding[base + j]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
    }
    base += doclengths_ordered_padding[i];
  }
  // printf("Prestore score processed done.\n\n");
}

void init_tf_impact_score_helper(char *data_path, int b) {
  init_tf(data_path);

  min_score = INT_MAX;
  max_score = INT_MIN;
  int i, j;
  long base = 0;
  for (i = 0; i < num_docs; i ++) {
    for (j = 0; j < doclengths_ordered[i]; j ++) {
      float score = log(1 + tf_padding[base + j] / (MU * (cf[collection_tf_padding[base + j]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
      if (score < min_score) {min_score = score;}
      if (score > min_score) {max_score = score;}
    }
    base += doclengths_ordered_padding[i];
  }
  // printf("Min and max score processed done. Min: %f, Max: %f\n\n", min_score, max_score);
}

void init_tf_impact_score_8bits(char *data_path, int b) {
  init_tf_impact_score_helper(data_path, b);

  impact_score_8bits_padding = malloc(sum * sizeof(uint8_t));
  memset(impact_score_8bits_padding, 0, sizeof(impact_score_8bits_padding));

  int i, j;
  long base = 0;
  double e = 0.0001;
  for (i = 0; i < num_docs; i ++) {
    for (j = 0; j < doclengths_ordered[i]; j ++) {
      float score = log(1 + tf_padding[base + j] / (MU * (cf[collection_tf_padding[base + j]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
      impact_score_8bits_padding[base + j] = (int)(floor(pow(2, b) * (score - min_score) / (max_score - min_score + e)));
    }
    base += doclengths_ordered_padding[i];
  }
  // printf("Impact score processed done.\n\n");
}

void init_tf_impact_score_32bits(char *data_path, int b) {
  init_tf_impact_score_helper(data_path, b);

  impact_score_32bits_padding = malloc(sum * sizeof(uint32_t));
  memset(impact_score_32bits_padding, 0, sizeof(impact_score_32bits_padding));

  int i, j;
  long base = 0;
  double e = 0.0001;
  for (i = 0; i < num_docs; i ++) {
    for (j = 0; j < doclengths_ordered[i]; j ++) {
      float score = log(1 + tf_padding[base + j] / (MU * (cf[collection_tf_padding[base + j]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
      impact_score_32bits_padding[base + j] = (int)(floor(pow(2, b) * (score - min_score) / (max_score - min_score + e)));
    }
    base += doclengths_ordered_padding[i];
  }
  // printf("Impact score processed done.\n\n");
}
