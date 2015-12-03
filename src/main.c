#include <stdio.h>
#include "main.h"
#include "mkl-main.h"

int main() {
  double *A = allocate_d(16, 16);
  if (A == NULL) {
    fprintf(stderr, "Failed to allocate a 16x16 matrix of double.\n");
    return 1;
  }
  printf("Successful allocation of a 16x16 matrix of double using MKL.\n");
  free_d(A);
  return 0;
}
