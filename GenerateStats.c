#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <zlib.h>

#include "include/jsmn.c"
#include "include/data.c"
#include "include/intHashMap.c"

#define LENGTH 0x1000

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

void lower_string(char *string) {
   while(*string) {
      if (*string >= 'A' && *string <= 'Z') {
         *string = *string + 32;
      }
      string++;
   }
}

int main(int argc, const char* argv[]) {
  clock_t begin, end;
  double time_spent;
  begin = clock();
  if (argc <= 2) {
    printf("PLEASE ENTER COLLECTION PATH AND OUTPUT PATH!\n");
    return 0;
  }

  char *output_path = argv[2];
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

  int i;
  int r;
  char *ch_text = NULL;
  int size = 30000;
  long term_cnt = 1;
  long doc_cnt = 0;
  hashMap term2idmap;
  hashMapNew(&term2idmap);
  int *cf = (int *) malloc(size * sizeof(int));
  long collection_unique_term_size = 0;
  long collection_all_term_size = 0;
  struct dirent **namelist;
  int n;
  n = scandir(argv[1], &namelist, 0, alphasort);
  if (n < 0) {
    perror("scandir");
  }
  else {
    printf("-> Start storing stats...\n");
    int filecnt = 0;
    while (filecnt < n) {
      char *filename = namelist[filecnt]->d_name;      
      if (strlen(filename) >= 4 && strcmp(filename + strlen(filename) - 3, ".gz") == 0) {       
        gzFile *file;
        char str[80];
        strcpy(str, argv[1]);
        strcat(str, "/");
        strcat(str, filename);
        file = gzopen(str, "r");

        while (!gzeof(file)) {
          char *line_text = NULL;
          unsigned char buffer[LENGTH];
          gzgets(file, buffer, LENGTH);
          jsmn_parser p;
          jsmntok_t t[128];
          jsmn_init(&p);
          r = jsmn_parse(&p, buffer, strlen(buffer), t, sizeof(t)/sizeof(t[0]));
          if (r < 0) {
            continue;
          }
          if (r < 1 || t[0].type != JSMN_OBJECT) {
            continue;
          }
          for (i = 1; i < r; i++) {
            if (jsoneq(buffer, &t[i], "text") == 0) {
              asprintf(&line_text, "%.*s\n", t[i + 1].end - t[i + 1].start, buffer + t[i + 1].start);
              i ++;
            } else if (jsoneq(buffer, &t[i], "id") == 0) {
              if (t[i + 1].end - t[i + 1].start >= 17) {
                fprintf(fp_id, "%.*s\n", t[i + 1].end - t[i + 1].start, buffer + t[i + 1].start);
                i ++;
                break;
              }
            }
          }

          lower_string(line_text);
          ch_text = strtok(line_text, " \n");
          int doc_length = 0;
          int doc_length_ordered = 0;
          intHashMap doctfmap;
          intHashMapNew(&doctfmap);
          while (ch_text != NULL) {
            struct entry *entryTerm2Id = malloc(sizeof(*entryTerm2Id));
            entryTerm2Id->line = strdup(ch_text);
            entryTerm2Id->value = term_cnt;
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
            time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;
            printf("%d processed, Time = %f ms\n", doc_cnt, time_spent * 1000);
          }
        }
        gzclose(file);
      }
      free(namelist[filecnt ++]);
    }
    free(namelist);
  }

  printf("Total %d processed, Time = %f ms\n", doc_cnt, time_spent * 1000);

  i = 0;
  for (i = 0; i < term_cnt - 1; i ++) {
    fprintf(fp_cf, "%d\n", cf[i]);
  }
  free(cf);

  fprintf(fp_stats, "%ld\n", doc_cnt);
  fprintf(fp_stats, "%ld\n", collection_unique_term_size);
  fprintf(fp_stats, "%ld\n", collection_all_term_size);
  fprintf(fp_stats, "%ld\n", term_cnt - 1);

  struct entry *entryTerm2Id;
  HASHMAP_FOR_EACH(hashMap, entryTerm2Id, term2idmap) {
    fprintf(fp_term2idmapping, "%s %d\n", entryTerm2Id->line, entryTerm2Id->value);
  } HASHMAP_FOR_EACH_END
  hashMapDestroy(&term2idmap);

  fclose(fp_id);
  fclose(fp_length);
  fclose(fp_term_ordered);
  fclose(fp_tf);
  fclose(fp_length_ordered);
  fclose(fp_cf);
  fclose(fp_stats);
  fclose(fp_term2idmapping);

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total time = %f ms\n", time_spent * 1000);
     
  printf("-> Start preprocessing for storing termindexes...\n");
  long *termindexes;
  long *termindexes_padding;
  termindexes = malloc((doc_cnt + 1) * sizeof(long));
  termindexes_padding = malloc((doc_cnt + 1) * sizeof(long));
  doc_cnt = 0;
  fp_length_ordered = concat_fopen(output_path, "/doc_length_ordered.txt", "r");
  ssize_t read_text;
  char *line_text;
  size_t len_text = 0;
  while ((read_text = getline(&line_text, &len_text, fp_length_ordered)) != -1) {
    int length = atoi(line_text);
    termindexes[doc_cnt + 1] = termindexes[doc_cnt] + length;
    termindexes_padding[doc_cnt + 1] = termindexes_padding[doc_cnt] + length + (length % BLOCK_SIZE == 0 ? 0 : (BLOCK_SIZE - length % BLOCK_SIZE));
    doc_cnt ++;
  }
  fclose(fp_length_ordered);
  printf("Total %d processed\n", doc_cnt);

  printf("-> Start storing termindexes......\n");
  fprintf(fp_termindexes, "long *termindexes[] = {\n");
  fprintf(fp_termindexes_padding, "long *termindexes[] = {\n");
  int thread;
  for (thread = 1; thread <= 128; thread ++) {
    fprintf(fp_termindexes, "(long []) {");
    fprintf(fp_termindexes_padding, "(long []) {");
    int part;
    for (part = 0; part < thread; part ++) {
      fprintf(fp_termindexes, "%ld, ", termindexes[(int)(ceil(doc_cnt * 1.0 / thread) * part)]);
      fprintf(fp_termindexes_padding, "%ld, ", termindexes_padding[(int)(ceil(doc_cnt * 1.0 / thread) * part)]);
    }
    fprintf(fp_termindexes, "},\n");
    fprintf(fp_termindexes_padding, "},\n");
  }
  fprintf(fp_termindexes, "};\n");
  fprintf(fp_termindexes_padding, "};\n");

  fclose(fp_termindexes);
  fclose(fp_termindexes_padding);
  printf("-> Done......\n");
}
