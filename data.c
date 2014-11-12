#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "constants.h"

void init() {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i=0;

  fp = fopen("data/all_terms_ordered.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }

  printf("-> Reading collection from all_terms_ordered.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    collection[i++] = atoi(line);
    if (i % 10000000 == 0 ) printf("  %d terms...\n", i);
  }
  printf("Total of %d terms read\n\n", i);

  fclose(fp);

  fp = fopen("data/all_terms_tf.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }

  i=0;
  printf("-> Reading tf from all_terms_tf.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    tf[i++] = atoi(line);
    if (i % 10000000 == 0 ) printf("  %d tfs...\n", i);
  }
  printf("Total of %d tfs read\n\n", i);

  fclose(fp);


  fp = fopen("data/doc_length_ordered.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }

  i=0;
  printf("-> Reading doclengths from doc_length_ordered.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    doclengths[i++] = atoi(line);
    if (i % 1000000 == 0 ) printf("  %d lengths...\n", i);
  }
  printf("Total of %d doclengths read\n\n", i);

  fclose(fp);


  fp = fopen("data/doc_id.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }

  i=0;
  printf("-> Reading tweetids from doc_id.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    tweetids[i++] = atol(line);
    if (i % 1000000 == 0 ) printf("  %d tweetids...\n", i);
  }
  printf("Total of %d tweetids read\n\n", i);

  fclose(fp);

  fp = fopen("data/df_table.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }

  i=0;
  printf("-> Reading dfs from df_table.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    df[i++] = atoi(line);
    if (i % 1000000 == 0 ) printf("  %d terms...\n", i);
  }
  printf("Total of %d terms read\n\n", i);

  fclose(fp);

  fp = fopen("data/cf_table.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }

  i=0;
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
