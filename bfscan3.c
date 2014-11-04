#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "topics2011_reordered.h"

#define COLLECTION_SIZE 191160334
#define NUM_DOCS 15175674

static int collection[COLLECTION_SIZE];
static short doclengths[NUM_DOCS];

int main(int argc, const char* argv[]) {
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int i=0, j=0;;

  fp = fopen("/Users/jimmylin/Dropbox/data/bfscan-statistics/all_terms.txt", "r");
  if (fp == NULL) {
    exit(-1);
  }

  while ((read = getline(&line, &len, fp)) != -1) {
    //printf("Retrieved line of length %zu :\n", read);
    int termid = atoi(line);
    if (i % 10000000 == 0 ) printf("Read %d terms...\n", i);
    collection[i++] = termid;
  }
  printf("Total of %d terms read\n", i);

  fclose(fp);


  fp = fopen("/Users/jimmylin/Dropbox/data/bfscan-statistics/doc_length.txt", "r");
  if (fp == NULL) {
    exit(-1);
  }

  i=0;
  while ((read = getline(&line, &len, fp)) != -1) {
    //printf("Retrieved line of length %zu :\n", read);
    int doclength = atoi(line);
    if (i % 1000000 == 0 ) printf("Read %d terms...\n", i);
    doclengths[i++] = doclength;
  }
  printf("Total of %d doclengths read\n", i);

  fclose(fp);

  if (line) {
    free(line);
  }

  clock_t begin, end;
  double time_spent;
  begin = clock();

  int sum = 0;
  int base = 0;
  int score1, score2;

  int n;
  int t;

  for (n=0; n<42; n+=2) {
    int max_score1 = 0, max_score2 = 0;
    int max_doc1 = -1, max_doc2 = -1;

    base = 0;

    if ( topics2011[n][1] == 2 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score1 = 0;
        score2 = 0;

        for (j=0; j<doclengths[i]; j++) {
           collection[base+j] == topics2011[n][2] && score1++;
           collection[base+j] == topics2011[n][3] && score1++;

           collection[base+j] == topics2011[n+1][2] && score2++;
           collection[base+j] == topics2011[n+1][3] && score2++;
        }

        if (score1 > max_score1) {
          max_score1 = score1;
          max_doc1 = i;
        }

        if (score2 > max_score2) {
          max_score2 = score2;
          max_doc2 = i;
        }

        base += doclengths[i];
      }
    } else
    if ( topics2011[n][1] == 3 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score1 = 0;
        score2 = 0;

        for (j=0; j<doclengths[i]; j++) {
           collection[base+j] == topics2011[n][2] && score1++;
           collection[base+j] == topics2011[n][3] && score1++;
           collection[base+j] == topics2011[n][4] && score1++;

           collection[base+j] == topics2011[n+1][2] && score2++;
           collection[base+j] == topics2011[n+1][3] && score2++;
           collection[base+j] == topics2011[n+1][4] && score2++;
        }

        if (score1 > max_score1) {
          max_score1 = score1;
          max_doc1 = i;
        }

        if (score2 > max_score2) {
          max_score2 = score2;
          max_doc2 = i;
        }

        base += doclengths[i];
      }
    } else
    if ( topics2011[n][1] == 4 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score1 = 0;
        score2 = 0;

        for (j=0; j<doclengths[i]; j++) {
           collection[base+j] == topics2011[n][2] && score1++;
           collection[base+j] == topics2011[n][3] && score1++;
           collection[base+j] == topics2011[n][4] && score1++;
           collection[base+j] == topics2011[n][5] && score1++;

           collection[base+j] == topics2011[n+1][2] && score2++;
           collection[base+j] == topics2011[n+1][3] && score2++;
           collection[base+j] == topics2011[n+1][4] && score2++;
           collection[base+j] == topics2011[n+1][5] && score2++;
        }

        if (score1 > max_score1) {
          max_score1 = score1;
          max_doc1 = i;
        }

        if (score2 > max_score2) {
          max_score2 = score2;
          max_doc2 = i;
        }

        base += doclengths[i];
      }
    }else
    if ( topics2011[n][1] == 5 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score1 = 0;
        score2 = 0;

        for (j=0; j<doclengths[i]; j++) {
           collection[base+j] == topics2011[n][2] && score1++;
           collection[base+j] == topics2011[n][3] && score1++;
           collection[base+j] == topics2011[n][4] && score1++;
           collection[base+j] == topics2011[n][5] && score1++;
           collection[base+j] == topics2011[n][6] && score1++;

           collection[base+j] == topics2011[n+1][2] && score2++;
           collection[base+j] == topics2011[n+1][3] && score2++;
           collection[base+j] == topics2011[n+1][4] && score2++;
           collection[base+j] == topics2011[n+1][5] && score2++;
           collection[base+j] == topics2011[n+1][6] && score2++;
        }

        if (score1 > max_score1) {
          max_score1 = score1;
          max_doc1 = i;
        }

        if (score2 > max_score2) {
          max_score2 = score2;
          max_doc2 = i;
        }

        base += doclengths[i];
      }
    }

    printf("%d Q0 %d 1 %d bfscan1\n", topics2011[n][0], max_doc1, max_score1);
    printf("%d Q0 %d 1 %d bfscan1\n", topics2011[n+1][0], max_doc2, max_score2);
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total time = %f ms\n", time_spent * 1000);
  printf("Time per query = %f ms\n", (time_spent * 1000)/42);
}
