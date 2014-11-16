#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "constants.h"

extern void init_24bit();

int main(int argc, const char* argv[]) {
  init_24bit();
  int i=0, j=0;

  clock_t begin, end;
  double time_spent;
  begin = clock();

  int base = 0;
  int num = 0;
  long sum = 0;
  for (i=0; i<NUM_DOCS; i++) {
    int step = 3*doclengths[i];
    for (j=0; j<step; j+=3) {
      num = 0;
      num += (collection_24bit[base+j]<<16) + (collection_24bit[base+j+1]<<8) + (collection_24bit[base+j+2]);
      sum += num;
    }
    base += step;
  }

  printf("sum = %ld\n", sum);

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total time = %f ms\n", time_spent * 1000);
}
