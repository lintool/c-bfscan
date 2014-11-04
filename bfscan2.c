#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "topics2011.h"

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
  int score;

  int n;
  int t;

  for (n=0; n<49; n++) {
    printf("topic id %d, %d terms\n", topics2011[n][0], topics2011[n][1]);

    int max_score = 0;
    int max_doc = -1;

    base = 0;

    if ( topics2011[n][1] == 2 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
           collection[base+j] == topics2011[n][2] && score++;
           collection[base+j] == topics2011[n][3] && score++;
        }

        if (score > max_score) {
          max_score = score;
          max_doc = i;
        }

        base += doclengths[i];
      }
    } else if ( topics2011[n][1] == 3 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
           collection[base+j] == topics2011[n][2] && score++;
           collection[base+j] == topics2011[n][3] && score++;
           collection[base+j] == topics2011[n][4] && score++;
        }

        if (score > max_score) {
          max_score = score;
          max_doc = i;
        }

        base += doclengths[i];
      }
    } else if ( topics2011[n][1] == 4 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
           collection[base+j] == topics2011[n][2] && score++;
           collection[base+j] == topics2011[n][3] && score++;
           collection[base+j] == topics2011[n][4] && score++;
           collection[base+j] == topics2011[n][5] && score++;
        }

        if (score > max_score) {
          max_score = score;
          max_doc = i;
        }

        base += doclengths[i];
      }
    } else if ( topics2011[n][1] == 5 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
           collection[base+j] == topics2011[n][2] && score++;
           collection[base+j] == topics2011[n][3] && score++;
           collection[base+j] == topics2011[n][4] && score++;
           collection[base+j] == topics2011[n][5] && score++;
           collection[base+j] == topics2011[n][6] && score++;
        }

        if (score > max_score) {
          max_score = score;
          max_doc = i;
        }

        base += doclengths[i];
      }
    } else if ( topics2011[n][1] == 6 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
           collection[base+j] == topics2011[n][2] && score++;
           collection[base+j] == topics2011[n][3] && score++;
           collection[base+j] == topics2011[n][4] && score++;
           collection[base+j] == topics2011[n][5] && score++;
           collection[base+j] == topics2011[n][6] && score++;
           collection[base+j] == topics2011[n][7] && score++;
        }

        if (score > max_score) {
          max_score = score;
          max_doc = i;
        }

        base += doclengths[i];
      }
    } else if ( topics2011[n][1] == 7 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
           collection[base+j] == topics2011[n][2] && score++;
           collection[base+j] == topics2011[n][3] && score++;
           collection[base+j] == topics2011[n][4] && score++;
           collection[base+j] == topics2011[n][5] && score++;
           collection[base+j] == topics2011[n][6] && score++;
           collection[base+j] == topics2011[n][7] && score++;
           collection[base+j] == topics2011[n][8] && score++;
        }

        if (score > max_score) {
          max_score = score;
          max_doc = i;
        }

        base += doclengths[i];
      }
    } else {
      for (i=0; i<NUM_DOCS; i++) {
        score = 0;
        for (j=0; j<doclengths[i]; j++) {
          for (t=2; t<2+topics2011[n][1]; t++) {
            if ( collection[base+j] == topics2011[n][t]) {
              score++;
            }
          }
        }

        if (score > max_score) {
          max_score = score;
          max_doc = i;
        }

        base += doclengths[i];
      }
    }

    printf("%d Q0 %d 1 %d bfscan1\n", topics2011[n][0], max_doc, max_score);
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total time = %f ms\n", time_spent * 1000);
  printf("Time per query = %f ms\n", (time_spent * 1000)/49);
}
