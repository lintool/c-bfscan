#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "constants.h"

int num_docs;
int total_terms;
int num_topics;
void init_tf(char *data_path) {
  num_topics = sizeof(topics)/sizeof(topics[0]);
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int i=0;
  int * stats[3];
  fp = fopen(*data_path "stats.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading from stats.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    stats[i++] = atoi(line);
  }
  fclose(fp);
  num_docs = stats[0];
  total_terms = stats[2];

  collection_tf = malloc(stats[1] * sizeof(uint32_t));
  int i=0;
  fp = fopen(*data_path "all_terms_ordered.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading collection from all_terms_ordered.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    collection_tf[i++] = atoi(line);
    if (i % 10000000 == 0 ) printf("  %d terms...\n", i);
  }
  printf("Total of %d terms ordered read\n\n", i);
  fclose(fp);

  tf = malloc(stats[1] * sizeof(uint8_t));
  i=0;
  fp = fopen(*data_path "all_terms_tf.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }  
  printf("-> Reading tf from all_terms_tf.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    tf[i++] = atoi(line);
    if (i % 10000000 == 0 ) printf("  %d tfs...\n", i);
  }
  printf("Total of %d tfs read\n\n", i);
  fclose(fp);

  doclengths_ordered = malloc(stats[0] * sizeof(uint8_t));
  doclengths_ordered_padding = malloc(stats[0] * sizeof(uint8_t));
  base = malloc(stats[0] * sizeof(uint32_t));
  base_padding = malloc(stats[0] * sizeof(uint32_t));
  i=0;
  int sum = 0;
  base[0] = 0;
  base_padding[0] = 0;
  fp = fopen(*data_path "doc_length_ordered.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading doclengths from doc_length_ordered.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    doclengths_ordered[i] = atoi(line);
    if (atoi(line) % BLOCK_SIZE == 0) {
      doclengths_ordered_padding[i] = atoi(line);
    } else {
      doclengths_ordered_padding[i] = atoi(line) + (BLOCK_SIZE - atoi(line) % BLOCK_SIZE);
    }
    if (i > 0) {
      base[i] = base[i - 1] + doclengths_ordered[i - 1];
      base_padding[i] = base_padding[i - 1] + doclengths_ordered_padding[i - 1];
    }
    sum += doclengths_ordered_padding[i++];
    if (i % 1000000 == 0 ) printf("  %d ordered lengths...\n", i);
  }
  printf("Total of %d doclengths ordered read\n\n", i);
  fclose(fp);

  collection_tf_padding = malloc(sum * sizeof(uint32_t));
  tf_padding = malloc(sum * sizeof(uint32_t));
  doc_pos = malloc(sum * sizeof(uint8_t));
  int base = 0;
  int i_padding = 0;
  int ii=0;
  int jj=0;
  int pos=0;
  for (ii = 0; ii < num_docs; ii ++) {
    for (jj = 0; jj < doclengths_ordered[ii]; jj ++) {
      collection_tf_padding[i_padding] = collection_tf[base + jj];
      tf_padding[i_padding] = tf[base + jj];
      doc_pos[i_padding] = pos % DOCS_BLOCK_SIZE;
      i_padding++;
    }
    for (jj = doclengths_ordered[ii]; jj < doclengths_ordered_padding[ii]; jj ++) {
      collection_tf_padding[i_padding] = 0;
      tf_padding[i_padding] = 0;
      doc_pos[i_padding] = pos % DOCS_BLOCK_SIZE;
      i_padding++;
    }
    pos ++;
    base += doclengths_ordered[ii];
  }

  tweetids = malloc(stats[0] * sizeof(uint64_t));
  int i=0;
  fp = fopen(*data_path "doc_id.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading tweetids from doc_id.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    tweetids[i++] = atol(line);
    if (i % 1000000 == 0 ) printf("  %d tweetids...\n", i);
  }
  printf("Total of %d tweetids read\n\n", i);
  fclose(fp);

  doclengths = malloc(stats[0] * sizeof(uint32_t));  
  i=0;
  fp = fopen(*data_path "doc_length.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading doclengths from doc_length.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    doclengths[i++] = atoi(line);
    if (i % 1000000 == 0 ) printf("  %d lengths...\n", i);
  }
  printf("Total of %d doclengths read\n\n", i);
  fclose(fp);

  cf = malloc(stats[3] * sizeof(uint32_t));  
  i=0;
  fp = fopen(*data_path "cf_table.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading cfs from cf_table.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    cf[i++] = atoi(line);
    if (i % 1000000 == 0 ) printf("  %d terms...\n", i);
  }
  printf("Total of %d terms read\n\n", i);
  fclose(fp);

  if (line) {
    free(line);
  }
}