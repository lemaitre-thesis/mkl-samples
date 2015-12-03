#include <stdio.h>
#include "main.h"
#include "mkl-main.h"
#include "mkl-cholesky.h"
#include "rdtsc.h"

#define MIN(a,b) ((a) < (b) ? (a) : (b))

int getArgNum(int argc, char* argv[], int i, int defaultNum) {
  if (i >= argc) {
    return defaultNum;
  }
  char* p;
  char* arg = argv[i];
  double res;
  if (sscanf(arg, "%lf", &res)) {
    return (int) res;
  } else {
    return defaultNum;
  }
}


int main(int argc, char* argv[]) {
  int i, success, N = 64, Ntry = 10;
  unsigned long long int t, t1, t2;

  float *A, *x, *L, *rhs;
  
  N = getArgNum(argc, argv, 1, N);
  Ntry = getArgNum(argc, argv, 2, Ntry);


  printf("Cholesky system generation");fflush(stdout);
  t = -1;
  for (i = 0; i < Ntry; ++i) {
    t1 = rdtsc();
    success = allocate_generate_cholesky_system_s(&A, &L, &x, &rhs, N);
    t2 = rdtsc();
    t = MIN(t, t2 - t1);
    if (!success) break;
  }
  if (!success) {
    fprintf(stderr, "\nFailed to allocate a %ix%i cholesky system\n", N, N);
    return 1;
  }
  printf("\rCholesky system generated in %lli cycles\n", t);

  if (N <= 16) {
    printf("\nA:\n");
    show_matrix_s(A, N, N);

    printf("\ntheoretical L:\n");
    show_matrix_s(L, N, N);

    printf("\ntheoretical x:\n");
    show_matrix_s(x, 1, N);

    printf("\nrhs:\n");
    show_matrix_s(rhs, 1, N);
  }

  printf("\nFactorizing");fflush(stdout);

  t = -1;
  for (i = 0; i < Ntry; ++i) {
    zero_matrix_s(L, N, N);
    t1 = rdtsc();
    factorize_cholesky_s(A, L, N);
    t2 = rdtsc();
    t = MIN(t, t2 - t1);
  }
  printf("\rFactorized in %lli cycles\n", t);

  if (N <= 16) {
    if (is_valid_cholesky_factorization_s(L, N)) {
      printf("L:\n");
    } else {
      printf("L (invalid factorization):\n");
    }
    show_matrix_s(L, N, N);
  } else {
    if (!is_valid_cholesky_factorization_s(L, N)) {
      printf("Invalid factorization\n");
    }
  }

  printf("\nForwarding");fflush(stdout);

  t = -1;
  for (i = 0; i < Ntry; ++i) {
    zero_vector_s(x, N);
    t1 = rdtsc();
    forward_cholesky_s(L, rhs, x, N);
    t2 = rdtsc();
    t = MIN(t, t2 - t1);
  }
  printf("\rForwarded in %lli cycles\n", t);

  if (N <= 128) {
    printf("x:\n");
    show_matrix_s(x, 1, N);
  }

  free_s(A);
  free_s(L);
  free_s(x);
  free_s(rhs);


  return 0;
}
