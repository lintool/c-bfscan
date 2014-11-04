#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "heap.h"
#include "topics2011.h"

#define COLLECTION_SIZE 191160334
#define NUM_DOCS 15175674
#define NUM_TERMS 14327804

#define MU 2500
#define TOP_K 1000

static int collection[COLLECTION_SIZE];
static long tweetids[NUM_DOCS];
static short doclengths[NUM_DOCS];
static short df[NUM_TERMS];

int main(int argc, const char* argv[]) {
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int i=0, j=0;;

  fp = fopen("/Users/jimmylin/Dropbox/data/bfscan-statistics/all_terms.txt", "r");
  if (fp == NULL) exit(-1);

  printf("-> Reading collection from all_terms.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    collection[i++] = atoi(line);
    if (i % 10000000 == 0 ) printf("  %d terms...\n", i);
  }
  printf("Total of %d terms read\n\n", i);

  fclose(fp);


  fp = fopen("/Users/jimmylin/Dropbox/data/bfscan-statistics/doc_length.txt", "r");
  if (fp == NULL) exit(-1);

  i=0;
  printf("-> Reading doclengths from doc_length.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    doclengths[i++] = atoi(line);
    if (i % 1000000 == 0 ) printf("  %d lengths...\n", i);
  }
  printf("Total of %d doclengths read\n\n", i);

  fclose(fp);


  fp = fopen("/Users/jimmylin/Dropbox/data/bfscan-statistics/doc_id.txt", "r");
  if (fp == NULL) {
    exit(-1);
  }

  i=0;
  printf("-> Reading tweetids from doc_id.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    tweetids[i++] = atol(line);
    if (i % 1000000 == 0 ) printf("  %d tweetids...\n", i);
  }
  printf("Total of %d tweetids read\n\n", i);

  fclose(fp);

  if (line) {
    free(line);
  }

  fp = fopen("/Users/jimmylin/Dropbox/data/bfscan-statistics/df_table.txt", "r");
  if (fp == NULL) {
    exit(-1);
  }

  i=0;
  printf("-> Reading dfs from df_table.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    df[i++] = atoi(line);
    if (i % 1000000 == 0 ) printf("  %d terms...\n", i);
  }
  printf("Total of %d terms read\n\n", i);

  fclose(fp);


  clock_t begin, end;
  double time_spent;
  begin = clock();

  int sum = 0;
  int base = 0;
  double score;

  int n;
  int t;

  for (n=0; n<49; n++) {
    printf("Processing topic %d...\n", topics2011[n][0]);

    heap h;
    heap_create(&h,0,NULL);

    float* min_key;
    int* min_val;

    base = 0;
    for (i=0; i<NUM_DOCS; i++) {
      score = 0;
      for (j=0; j<doclengths[i]; j++) {
        for (t=2; t<2+topics2011[n][1]; t++) {
          if (collection[base+j] == topics2011[n][t]) {
              score += log10(NUM_DOCS / df[t]);
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

      base += doclengths[i];
    }

    int rank = TOP_K;
    while (heap_delmin(&h, (void**)&min_key, (void**)&min_val)) {
      printf("%d Q0 %ld %d %f bfscan1\n", (n+1), tweetids[*min_val], rank, *min_key);
      rank--;
    }

    heap_destroy(&h);
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total time = %f ms\n", time_spent * 1000);
}
