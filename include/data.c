#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "constants.h"
#include "hashmap.c"

// int num_docs;
// int total_terms;
// int num_topics;

FILE * concat_fopen (char *s1, char *s2, char *mode) {
  char str[strlen (s1) + strlen (s2) + 1];
  strcpy (str, s1);
  strcat (str, s2);
  if (mode == "w+") {
    remove(str);
  }
  return fopen (str, mode);
}

void init_tf(char *data_path, char *query_path) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  long i=0;
  long stats[4];
  fp = concat_fopen(data_path, "/stats.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading from stats.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
     stats[i] = atol(line);
     i ++;
  }
  fclose(fp);
  num_docs = stats[0];
  long total_terms_unique_per_doc = stats[1];
  total_terms = stats[2];
  long num_terms = stats[3];

  collection_tf = malloc(total_terms_unique_per_doc * sizeof(uint32_t));
  i=0;
  fp = concat_fopen(data_path, "/all_terms_ordered.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading collection from all_terms_ordered.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    collection_tf[i++] = atoi(line);
    if (i % 10000000 == 0 ) printf("  %ld terms...\n", i);
  }
  printf("Total of %ld terms ordered read\n\n", i);
  fclose(fp);

  tf = malloc(total_terms_unique_per_doc * sizeof(uint8_t));
  i=0;
  fp = concat_fopen(data_path, "/all_terms_tf.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }  
  printf("-> Reading tf from all_terms_tf.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    tf[i++] = atoi(line);
    if (i % 10000000 == 0 ) printf("  %ld tfs...\n", i);
  }
  printf("Total of %ld tfs read\n\n", i);
  fclose(fp);

  doclengths_ordered = malloc(num_docs * sizeof(uint8_t));
  doclengths_ordered_padding = malloc(num_docs * sizeof(uint8_t));
  base = malloc(num_docs * sizeof(uint32_t));
  base_padding = malloc(num_docs * sizeof(uint32_t));
  i=0;
  long sum = 0;
  base[0] = 0;
  base_padding[0] = 0;
  fp = concat_fopen(data_path, "/doc_length_ordered.txt", "r");
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
  tf_padding = malloc(sum * sizeof(uint8_t));
  doc_pos = malloc(sum * sizeof(uint8_t));
  long base = 0;
  long i_padding = 0;
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
  fp = concat_fopen(data_path, "/doc_id.txt", "r");
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
  fp = concat_fopen(data_path, "/doc_length.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading doclengths from doc_length.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    doclengths[i++] = atoi(line);
    if (i % 1000000 == 0 ) printf("  %d lengths...\n", i);
  }
  printf("Total of %d doclengths read\n\n", i);
  fclose(fp);

  cf = malloc((num_terms + 1) * sizeof(uint32_t));  
  i=1;
  fp = concat_fopen(data_path, "/cf_table.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading cfs from cf_table.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    cf[i++] = atoi(line);
    if (i % 1000000 == 0 ) printf("  %d terms...\n", i);
  }
  printf("Total of %d terms read\n\n", i);
  fclose(fp);

  fp = concat_fopen(data_path, "/term2id_mapping.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading term2idmap from term2id_mapping.txt\n");
  hashMap term2idmap;
  hashMapNew(&term2idmap);
  char *ch = NULL;
  i = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    struct entry entryTerm2IdValue;
    struct entry *entryTerm2Id;
    ch = strtok(line, " \n");
    entryTerm2IdValue.line = strdup(ch);
    ch = strtok(NULL, " \n");
    entryTerm2IdValue.value = atoi(strdup(ch));
    entryTerm2Id = &entryTerm2IdValue;
    hashMapPut(&term2idmap, &entryTerm2Id, HMDR_FIND);
    i ++;
    if (i % 1000000 == 0 ) printf("  %d terms...\n", i);
  }
  fclose(fp);
  printf("Finished reading stats.\n\n");

  printf("-> Process query\n");
  fp = fopen(query_path, "r");
  if (fp == NULL) { printf("Reading query file error!\n"); exit(-1); }
  int c = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    c ++;
  }
  num_topics = c;
  topics = malloc(c * sizeof(int *));
  fclose(fp);

  fp = fopen(query_path, "r");
  c = 1;
  while ((read = getline(&line, &len, fp)) != -1) {
    int size = 0;
    char *tempLine = strdup(line);
    ch = strtok(tempLine, " \n");
    ch = strtok(NULL, " \n");
    while (ch != NULL) {
      size ++;
      ch = strtok(NULL, " \n");
    }
    topics[c - 1] = malloc((size + 2) * sizeof(int));
    topics[c - 1][0] = c;
    topics[c - 1][1] = size;

    ch = strtok(line, " \n");
    ch = strtok(NULL, " \n");
    int pos = 2;
    while (ch != NULL) {
      struct entry entryTerm2IdValue;
      struct entry *entryTerm2Id;
      entryTerm2IdValue.line = strdup(ch);
      entryTerm2IdValue.value = 1;
      entryTerm2Id = &entryTerm2IdValue;
      int id = -1;
      if (hashMapFind(&term2idmap, &entryTerm2Id)) {
        id = entryTerm2Id->value;
      }
      topics[c - 1][pos] = id;
      ch = strtok(NULL, " \n");
      pos ++;
    }
    c ++;
  }
  printf("Total of %d queries processed.\n\n", num_topics);
  fclose(fp);

  if (line) {
    free(line);
  }
}

void init_tf_intra(char *data_path, char *query_path, bool padding) {
  init_tf(data_path, query_path);

  FILE *fp;
  char *line = NULL;
  char *ch = NULL;
  size_t len = 0;
  ssize_t read;

  if (!padding) {
    fp = concat_fopen(data_path, "/termindexes.txt", "r");
    if (fp == NULL) { printf("Reading termindexes file error!\n"); exit(-1); }
  } else {
    fp = concat_fopen(data_path, "/termindexes_padding.txt", "r");
    if (fp == NULL) { printf("Reading termindexes_padding file error!\n"); exit(-1); }
  }
  int c = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    c ++;
  }
  termindexes = malloc(c * sizeof(int *));
  fclose(fp);

  if (!padding) {
    fp = concat_fopen(data_path, "/termindexes.txt", "r");
    if (fp == NULL) { printf("Reading termindexes file error!\n"); exit(-1); }
  } else {
    fp = concat_fopen(data_path, "/termindexes_padding.txt", "r");
    if (fp == NULL) { printf("Reading termindexes_padding file error!\n"); exit(-1); }
  }
  c = 1;
  while ((read = getline(&line, &len, fp)) != -1) {
    int size = 0;
    char *tempLine = strdup(line);
    ch = strtok(tempLine, " \n");
    while (ch != NULL) {
      size ++;
      ch = strtok(NULL, " \n");
    }
    termindexes[c - 1] = malloc(size * sizeof(int));

    ch = strtok(line, " \n");
    int pos = 0;
    while (ch != NULL) {
      termindexes[c - 1][pos] = atoi(strdup(ch));
      ch = strtok(NULL, " \n");
      pos ++;
    }
    c ++;
  }
  fclose(fp);

  if (line) {
    free(line);
  }
}

// void init_tf_intra(char *data_path, char *query_path, bool padding) {
//   init_tf(data_path, query_path);
//   char *termindex_file = "/termindexes.txt";
//   if (padding) {
//     termindex_file = "/termindexes_padding.txt";
//   }
//   char str[strlen(data_path) + strlen(termindex_file)];
//   strcpy(str, data_path);
//   strcat(str, termindex_file);
//   printf("%s\n", str);
//   partition(str, termindexes);
// }
