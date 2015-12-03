#include <stdio.h>
#include "main.h"
#include "mkl-main.h"
#include "mkl-cholesky.h"
#include "rdtsc.h"

int main() {
  const int N = 64;
  long long int t1, t2;

  double *A, *x, *L, *rhs;
  t1 = rdtsc();
  if (!allocate_generate_cholesky_system_d(&A, &L, &x, &rhs, N)) {
    fprintf(stderr, "Failed to allocate a %ix%i cholesky system", N, N);
    return 1;
  }
  t2 = rdtsc();
  printf("Cholesky system generated in %lli cycles\n", t2 - t1);

  if (N <= 16) {
    printf("\nA:\n");
    show_matrix_d(A, N, N);

    printf("\ntheoretical L:\n");
    show_matrix_d(L, N, N);

    printf("\ntheoretical x:\n");
    show_matrix_d(x, N, 1);

    printf("\nrhs:\n");
    show_matrix_d(rhs, N, 1);
  }

  zero_matrix_d(L, N, N);
  zero_vector_d(x, N);

  printf("\nFactorizing");

  t1 = rdtsc();
  factorize_cholesky_d(A, L, N);
  t2 = rdtsc();
  printf("\rFactorized in %lli cycles\n", t2 - t1);

  if (N <= 16) {
    if (is_valid_cholesky_factorization_d(L, N)) {
      printf("L:\n");
    } else {
      printf("L (invalid factorization):\n");
    }
    show_matrix_d(L, N, N);
  } else {
    if (!is_valid_cholesky_factorization_d(L, N)) {
      printf("Invalid factorization\n");
    }
  }

  printf("\nForwarding");

  t1 = rdtsc();
  forward_cholesky_d(L, rhs, x, N);
  t2 = rdtsc();
  printf("\rForwarded in %lli cycles\n", t2 - t1);

  if (N <= 128) {
    printf("x:\n");
    show_matrix_d(x, 1, N);
  }

  free_d(A);
  free_d(L);
  free_d(x);
  free_d(rhs);


  return 0;
}
