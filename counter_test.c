#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "counter.h"


int main(int argc, char **argv) {
  counter *c;
  int *max;
  const int n = 3;
  int N;
  int i;
  
  max = malloc(n * sizeof(int));
  assert(max);

  for (i = 0; i < n; i++) {
    max[i] = i+2;
  }

  printf("max:\n");
  N = 1;
  for (i = 0; i < n; i++) {
    printf("%d ", max[i]);
    N *= max[i];
  }
  printf("\nN: %d\n\n", N);

  c = counter_create(n, max);

  counter_reset(c);
  for (i = 0; i < N; i++) {
    counter_printf(c);
    printf("\n");
    if (i != N - 1) {
      counter_tick(c);
    }
  }

  N = 1;
  for (i = 0; i < n-1; i++) {
    N *= max[i];
  }
  
  counter_reset(c);
  printf("\n");
  for (i = 0; i < N; i++) {
    counter_printf(c);
    printf("\n");
    if (i != N - 1) {
      counter_tick_digit(c, c->n-2);
    }
  }
  
  counter_destroy(&c);
  
  return 0;
}
