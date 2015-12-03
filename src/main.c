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

  printf("\ntheoretical L:\n");
  show_matrix_d(L, N, N);

  printf("\ntheoretical x:\n");
  show_matrix_d(x, N, 1);

  printf("\nrhs:\n");
  show_matrix_d(rhs, N, 1);

  zero_matrix_d(L, N, N);
  zero_vector_d(x, N);

  printf("\nFactorize\n");

  factorize_cholesky_d(A, L, N);

  if (is_valid_cholesky_factorization_d(L, N)) {
    printf("L:\n");
  } else {
    printf("L (invalid factorization):\n");
  }
  show_matrix_d(L, N, N);

  forward_cholesky_d(L, rhs, x, N);

  printf("\nx:\n");
  show_matrix_d(x, N, 1);

  free_d(A);
  free_d(L);
  free_d(x);
  free_d(rhs);


  return 0;
}
