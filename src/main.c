#include <stdio.h>
#include "main.h"
#include "mkl-main.h"
#include "mkl-cholesky.h"

int main() {
  const int N = 4;

  double *A, *x, *L, *rhs;
  if (!allocate_generate_cholesky_system_d(&A, &L, &x, &rhs, N)) {
    fprintf(stderr, "Failed to allocate a %ix%i cholesky system", N, N);
    return 1;
  }

  printf("A:\n");
  show_matrix_d(A, N, N);

  printf("rhs:  ");
  show_vector_d(rhs, N);
  printf("\n");

  free_d(A);
  free_d(L);
  free_d(x);
  free_d(rhs);


  return 0;
}
