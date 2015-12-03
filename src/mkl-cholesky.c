#include <stdio.h>
#include <stdlib.h>
#include "mkl-main.h"
#include "mkl.h"


void generate_cholesky_L_s(float*  L, int n) {
  int i, j;
  float* Li;
  zero_matrix_s(L, n, n);
  for (i = 0; i < n; ++i) {
    Li = &L[i*n];
    for (j = 0; j <= i; ++j) {
      Li[j] = 1+((i+j)*(i+j)) % 5;
    }
  }
}
void generate_cholesky_L_d(double* L, int n) {
  int i, j;
  double* Li;
  zero_matrix_d(L, n, n);
  for (i = 0; i < n; ++i) {
    Li = &L[i*n];
    for (j = 0; j <= i; ++j) {
      Li[j] = 1+((i+j)*(i+j)) % 5;
    }
  }
}

void generate_cholesky_x_s(float*  rhs, int n) {
  int i;
  for (i = 0; i < n; ++i) {
    rhs[i] = 1+i;
  }
}
void generate_cholesky_x_d(double* rhs, int n) {
  int i;
  for (i = 0; i < n; ++i) {
    rhs[i] = 1+i;
  }
}

void generate_cholesky_A_s(float*  A, const float*  L, int n) {
  int nn = n*n;
  cblas_scopy(nn, L, 1, A, 1);
  cblas_strmm(CblasRowMajor, CblasRight, CblasLower, CblasTrans, CblasNonUnit, n, n, 1, L, n, A, n);
}
void generate_cholesky_A_d(double* A, const double* L, int n) {
  int nn = n*n;
  cblas_dcopy(nn, L, 1, A, 1);
  cblas_dtrmm(CblasRowMajor, CblasRight, CblasLower, CblasTrans, CblasNonUnit, n, n, 1, L, n, A, n);
}

void generate_cholesky_rhs_s(float*  rhs, const float*  A, const float*  x, int n) {
  cblas_ssymv(CblasRowMajor, CblasLower, n, 1, A, n, x, 1, 0, rhs, 1);
}
void generate_cholesky_rhs_d(double* rhs, const double* A, const double* x, int n) {
  cblas_dsymv(CblasRowMajor, CblasLower, n, 1, A, n, x, 1, 0, rhs, 1);
}

void generate_cholesky_system_s(float*  A, float*  L, float*  x, float*  rhs, int n) {
  generate_cholesky_L_s(L, n);
  generate_cholesky_x_s(x, n);
  generate_cholesky_A_s(A, L, n);
  generate_cholesky_rhs_s(rhs, A, x, n);
}
void generate_cholesky_system_d(double* A, double* L, double* x, double* rhs, int n) {
  generate_cholesky_L_d(L, n);
  generate_cholesky_x_d(x, n);
  generate_cholesky_A_d(A, L, n);
  generate_cholesky_rhs_d(rhs, A, x, n);
}

int allocate_generate_cholesky_system_s(float**  Aptr, float**  Lptr, float**  xptr, float**  rhsptr, int n) {
  float *A, *x, *L, *rhs;

  A   = allocate_s(n, n);
  x   = allocate_s(n, 1);
  L   = allocate_s(n, n);
  rhs = allocate_s(n, 1);

  if (A == NULL || x == NULL || L == NULL || rhs == NULL) {
    free_s(A);
    free_s(x);
    free_s(L);
    free_s(rhs);
    return 0;
  }
  generate_cholesky_system_s(A, L, x, rhs, n);

  *Aptr   = A;
  *rhsptr = rhs;
  if (Lptr != NULL) *Lptr = L;
  if (xptr != NULL) *xptr = x;

  return 1;
}
int allocate_generate_cholesky_system_d(double** Aptr, double** Lptr, double** xptr, double** rhsptr, int n) {
  double *A, *x, *L, *rhs;

  A   = allocate_d(n, n);
  x   = allocate_d(n, 1);
  L   = allocate_d(n, n);
  rhs = allocate_d(n, 1);

  if (A == NULL || x == NULL || L == NULL || rhs == NULL) {
    free_d(A);
    free_d(x);
    free_d(L);
    free_d(rhs);
    return 0;
  }
  generate_cholesky_system_d(A, L, x, rhs, n);

  *Aptr   = A;
  *rhsptr = rhs;
  if (Lptr != NULL) *Lptr = L;
  if (xptr != NULL) *xptr = x;

  return 1;
}







void factorize_cholesky_s(const float*  A, float*  L, int n) {
  LAPACKE_slacpy(LAPACK_ROW_MAJOR, 'L', n, n, A, n, L, n);
  LAPACKE_spotrf(LAPACK_ROW_MAJOR, 'L', n, L, n);
}
void factorize_cholesky_d(const double* A, double* L, int n) {
  LAPACKE_dlacpy(LAPACK_ROW_MAJOR, 'L', n, n, A, n, L, n);
  LAPACKE_dpotrf(LAPACK_ROW_MAJOR, 'L', n, L, n);
}

void forward_cholesky_s(const float*  L, const float*  rhs, float*  x, int n) {
  cblas_scopy(n, rhs, 1, x, 1);
  LAPACKE_spotrs(LAPACK_ROW_MAJOR, 'L', n, 1, L, n, x, 1);
}
void forward_cholesky_d(const double* L, const double* rhs, double* x, int n) {
  cblas_dcopy(n, rhs, 1, x, 1);
  LAPACKE_dpotrs(LAPACK_ROW_MAJOR, 'L', n, 1, L, n, x, 1);
}

int is_valid_cholesky_factorization_s(const float*  L, int n) {
  int i;
  for (i = 0; i < n; ++i) {
    if (L[i*n+i] == 0) {
      return 0;
    }
  }
  return 1;
}
int is_valid_cholesky_factorization_d(const double* L, int n) {
  int i;
  for (i = 0; i < n; ++i) {
    if (L[i*n+i] == 0) {
      return 0;
    }
  }
  return 1;
}

int solve_cholesky_system_s(const float*  A, float*  L, float*  x, const float*  rhs, int n) {
  float *Lowned = NULL;
  if (L == NULL) {
    L = allocate_s(n, n);
    Lowned = L;
  }
  if (L == NULL) {
    return 0;
  }

  factorize_cholesky_s(A, L, n);

  if (!is_valid_cholesky_factorization_s(L, n)) {
    free_s(Lowned);
    return 0;
  }

  forward_cholesky_s(L, rhs, x, n);

  free_s(Lowned);
  return 1;
}
int solve_cholesky_system_d(const double* A, double* L, double* x, const double* rhs, int n) {
  double *Lowned = NULL;
  if (L == NULL) {
    L = allocate_d(n, n);
    Lowned = L;
  }
  if (L == NULL) {
    return 0;
  }

  factorize_cholesky_d(A, L, n);

  if (!is_valid_cholesky_factorization_d(L, n)) {
    free_d(Lowned);
    return 0;
  }

  forward_cholesky_d(L, rhs, x, n);

  free_d(Lowned);
  return 1;
}
