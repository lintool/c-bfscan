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
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int i=0;
  int stats[4];
  char str1[strlen(data_path) + strlen("/stats.txt")];
  strcpy(str1, data_path);
  strcat(str1, "/stats.txt");
  fp = fopen(str1, "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading from stats.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
     stats[i] = atoi(line);
     i ++;
  }
  fclose(fp);
  num_docs = stats[0];
  int total_terms_unique_per_doc = stats[1];
  total_terms = stats[2];
  int num_terms = stats[3];

  collection_tf = malloc(total_terms_unique_per_doc * sizeof(uint32_t));
  i=0;
  char str2[strlen(data_path) + strlen("/all_terms_ordered.txt")];
  strcpy(str2, data_path);
  strcat(str2, "/all_terms_ordered.txt");
  fp = fopen(str2, "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading collection from all_terms_ordered.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    collection_tf[i++] = atoi(line);
    if (i % 10000000 == 0 ) printf("  %d terms...\n", i);
  }
  printf("Total of %d terms ordered read\n\n", i);
  fclose(fp);

  tf = malloc(total_terms_unique_per_doc * sizeof(uint8_t));
  i=0;
  char str3[strlen(data_path) + strlen("/all_terms_tf.txt")];
  strcpy(str3, data_path);
  strcat(str3, "/all_terms_tf.txt");
  fp = fopen(str3, "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }  
  printf("-> Reading tf from all_terms_tf.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    tf[i++] = atoi(line);
    if (i % 10000000 == 0 ) printf("  %d tfs...\n", i);
  }
  printf("Total of %d tfs read\n\n", i);
  fclose(fp);

  doclengths_ordered = malloc(num_docs * sizeof(uint8_t));
  doclengths_ordered_padding = malloc(num_docs * sizeof(uint8_t));
  base = malloc(num_docs * sizeof(uint32_t));
  base_padding = malloc(num_docs * sizeof(uint32_t));
  i=0;
  int sum = 0;
  base[0] = 0;
  base_padding[0] = 0;
  char str4[strlen(data_path) + strlen("/doc_length_ordered.txt")];
  strcpy(str4, data_path);
  strcat(str4, "/doc_length_ordered.txt");
  fp = fopen(str4, "r");
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

  tweetids = malloc(num_docs * sizeof(uint64_t));
  i=0;
  char str5[strlen(data_path) + strlen("/doc_id.txt")];
  strcpy(str5, data_path);
  strcat(str5, "/doc_id.txt");
  fp = fopen(str5, "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading tweetids from doc_id.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    tweetids[i++] = atol(line);
    if (i % 1000000 == 0 ) printf("  %d tweetids...\n", i);
  }
  printf("Total of %d tweetids read\n\n", i);
  fclose(fp);

  doclengths = malloc(num_docs * sizeof(uint32_t));  
  i=0;
  char str6[strlen(data_path) + strlen("/doc_length.txt")];
  strcpy(str6, data_path);
  strcat(str6, "/doc_length.txt");
  fp = fopen(str6, "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading doclengths from doc_length.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    doclengths[i++] = atoi(line);
    if (i % 1000000 == 0 ) printf("  %d lengths...\n", i);
  }
  printf("Total of %d doclengths read\n\n", i);
  fclose(fp);

  cf = malloc(num_terms * sizeof(uint32_t));  
  i=0;
  char str7[strlen(data_path) + strlen("/cf_table.txt")];
  strcpy(str7, data_path);
  strcat(str7, "/cf_table.txt");
  fp = fopen(str7, "r");
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