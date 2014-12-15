#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "constants.h"

extern void init_pos();

int main(int argc, const char* argv[]) {
  init_pos();
  int i=0, j=0;

  clock_t begin, end;
  double time_spent;
  begin = clock();

  int base = 0;
  long sum = 0;
  for (i=0; i<NUM_DOCS; i++) {
    for (j=0; j<doclengths[i]; j++) {
      if (collection_pos[base+j] == 132948) {
      sum += collection_pos[base+j];
    }
    }
    base += doclengths[i];
  }

  printf("sum = %ld\n", sum);

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total time = %f ms\n", time_spent * 1000);
}
