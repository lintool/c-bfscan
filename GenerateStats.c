#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>

#include "include/data.c"
#include "include/intHashMap.c"

int main(int argc, const char* argv[]) {
  // if (argc <= 2) { //delete
  if (argc <= 3) { //delete
    printf("PLEASE ENTER TEXT PATH, DOCIDS PATH AND OUTPUT PATH!\n");
    return 0;
  }

  // char *output_path = argv[2]; //delete
  char *output_path = argv[3]; //delete
  struct stat st = {0};
  if (stat(output_path, &st) == -1) {
    mkdir(output_path, 0700);
  }
  
  FILE *fp_id = concat_fopen(output_path, "/doc_id.txt", "w+");
  FILE *fp_length = concat_fopen(output_path, "/doc_length.txt", "w+");
  FILE *fp_term_ordered = concat_fopen(output_path, "/all_terms_ordered.txt", "w+");
  FILE *fp_tf = concat_fopen(output_path, "/all_terms_tf.txt", "w+");
  FILE *fp_length_ordered = concat_fopen(output_path, "/doc_length_ordered.txt", "w+");
  FILE *fp_cf = concat_fopen(output_path, "/cf_table.txt", "w+");
  FILE *fp_stats = concat_fopen(output_path, "/stats.txt", "w+");
  FILE *fp_term2idmapping = concat_fopen(output_path, "/term2id_mapping.txt", "w+");
  FILE *fp_termindexes = concat_fopen(output_path, "/termindexes.txt", "w+");
  FILE *fp_termindexes_padding = concat_fopen(output_path, "/termindexes_padding.txt", "w+");

  FILE *fp_inputtext;
  fp_inputtext = fopen(argv[1], "r");
  if (fp_inputtext == NULL) { printf("Error!\n"); exit(-1); }
  // delete
  FILE *fp_inputdocs;
  fp_inputdocs = fopen(argv[2], "r");
  if (fp_inputdocs == NULL) { printf("Error!\n"); exit(-1); }
  // delete done
  printf("-> Start storing stats...\n");

  ssize_t read_text, read_docs;
  char *line_text = NULL, *line_docs = NULL;
  size_t len_text = 0, len_docs = 0;
  char *ch_text = NULL, *ch_docs = NULL;

  int doc_cnt = 0;
  int term_cnt = 1;
  int size = 30000;
  hashMap term2idmap;
  hashMapNew(&term2idmap);
  int *cf = (int *) malloc(size * sizeof(int));
  int collection_unique_term_size = 0;
  int collection_all_term_size = 0;
  
  while ((read_text = getline(&line_text, &len_text, fp_inputtext)) != -1) {
    // delete
    read_docs = getline(&line_docs, &len_docs, fp_inputdocs);
    ch_docs = strtok(line_docs, " \n");
    ch_docs = strtok(NULL, " \n");
    fprintf(fp_id, "%s\n", ch_docs);
    // delete done

    ch_text = strtok(line_text, " \n");
    // fprintf(fp_id, "%s\n", ch_text);   // delete
    ch_text = strtok(NULL, " \n");
    int doc_length = 0;
    int doc_length_ordered = 0;
    intHashMap doctfmap;
    intHashMapNew(&doctfmap);
    while (ch_text != NULL) {
      struct entry entryTerm2IdValue;
      struct entry *entryTerm2Id;
      entryTerm2IdValue.line = strdup(ch_text);
      entryTerm2IdValue.value = term_cnt;
      entryTerm2Id = &entryTerm2IdValue;
      if (hashMapFind(&term2idmap, &entryTerm2Id)) {
        cf[entryTerm2Id->value - 1] = cf[entryTerm2Id->value - 1] + 1;
      } else {
        hashMapPut(&term2idmap, &entryTerm2Id, HMDR_FIND);
        if (entryTerm2Id->value > size) {
          size = 2 * size;
          cf = (int *) realloc(cf, size * sizeof(int));
        }  
        cf[term_cnt - 1] = 1;
        term_cnt ++;
      }
      struct entry_int doctfEntryValue;
      struct entry_int *doctfEntry;
      doctfEntryValue.num = entryTerm2Id->value;
      doctfEntryValue.value = 1;
      doctfEntry = &doctfEntryValue;
      if (intHashMapFind(&doctfmap, &doctfEntry)) {
        doctfEntry->value ++;
      } else {
        intHashMapPut(&doctfmap, &doctfEntry, HMDR_FIND);
        doc_length_ordered ++;
      }
      ch_text = strtok(NULL, " \n");
      doc_length ++;
    }

    fprintf(fp_length, "%d\n", doc_length);
    collection_all_term_size += doc_length;
    fprintf(fp_length_ordered, "%d\n", doc_length_ordered);
    collection_unique_term_size += doc_length_ordered;
    struct entry_int *doctfEntry;
    HASHMAP_FOR_EACH(intHashMap, doctfEntry, doctfmap) {
      fprintf(fp_term_ordered, "%d\n", doctfEntry->num);
      fprintf(fp_tf, "%d\n", doctfEntry->value);
    } HASHMAP_FOR_EACH_END
    intHashMapDestroy(&doctfmap);

    doc_cnt ++;
    if (doc_cnt % 100000 == 0) {
      printf("%d processed\n", doc_cnt);
    }
  }
  printf("Total %d processed\n", doc_cnt);

  int i = 0;
  for (i = 0; i < term_cnt - 1; i ++) {
    fprintf(fp_cf, "%d\n", cf[i]);
  }
  free(cf);

  fprintf(fp_stats, "%d\n", doc_cnt);
  fprintf(fp_stats, "%d\n", collection_unique_term_size);
  fprintf(fp_stats, "%d\n", collection_all_term_size);
  fprintf(fp_stats, "%d\n", term_cnt - 1);

  struct entry *entryTerm2Id;
  HASHMAP_FOR_EACH(hashMap, entryTerm2Id, term2idmap) {
    fprintf(fp_term2idmapping, "%s %d\n", entryTerm2Id->line, entryTerm2Id->value);
  } HASHMAP_FOR_EACH_END
  hashMapDestroy(&term2idmap);

  fclose(fp_inputtext);
  fclose(fp_inputdocs); //delete
  fclose(fp_id);
  fclose(fp_length);
  fclose(fp_term_ordered);
  fclose(fp_tf);
  fclose(fp_length_ordered);
  fclose(fp_cf);
  fclose(fp_stats);
  fclose(fp_term2idmapping);

  printf("-> Start preprocessing for storing termindexes...\n");
  int *termindexes;
  int *termindexes_padding;
  termindexes = malloc((doc_cnt + 1) * sizeof(int));
  termindexes_padding = malloc((doc_cnt + 1) * sizeof(int));
  doc_cnt = 0;
  fp_length_ordered = concat_fopen(output_path, "/doc_length_ordered.txt", "r");
  while ((read_text = getline(&line_text, &len_text, fp_length_ordered)) != -1) {
    int length = atoi(line_text);
    termindexes[doc_cnt + 1] = termindexes[doc_cnt] + length;
    termindexes_padding[doc_cnt + 1] = termindexes_padding[doc_cnt] + length + (length % BLOCK_SIZE == 0 ? 0 : (BLOCK_SIZE - length % BLOCK_SIZE));
    doc_cnt ++;
  }
  fclose(fp_length_ordered);
  printf("Total %d processed\n", doc_cnt);

  printf("-> Start storing termindexes......\n");
  for (int thread = 1; thread <= 48; thread ++) {
    for (int part = 0; part < thread; part ++) {
      fprintf(fp_termindexes, "%d ", termindexes[(int)(ceil(doc_cnt * 1.0 / thread) * part)]);
      fprintf(fp_termindexes_padding, "%d ", termindexes_padding[(int)(ceil(doc_cnt * 1.0 / thread) * part)]);
    }
    fprintf(fp_termindexes, "\n");
    fprintf(fp_termindexes_padding, "\n");
  }

  fclose(fp_termindexes);
  fclose(fp_termindexes_padding);
  printf("-> Done......\n");
}