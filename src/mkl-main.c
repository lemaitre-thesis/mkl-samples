#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"
#include "mkl-main.h"

float*  allocate_s(int n, int m) {
  return (float*) mkl_malloc(n*m*sizeof(float),  MEMORY_ALIGNMENT);
}
double* allocate_d(int n, int m) {
  return (double*)mkl_malloc(n*m*sizeof(double), MEMORY_ALIGNMENT);
}

void free_s(float*  p) {
  mkl_free((void*)p);
}
void free_d(double* p) {
  mkl_free((void*)p);
}

void zero_matrix_s(float*  M, int n, int m) {
  int i, nm = n*m;
  for (i = 0; i < nm; ++i) {
    M[i] = 0;
  }
}
void zero_matrix_d(double* M, int n, int m) {
  int i, nm = n*m;
  for (i = 0; i < nm; ++i) {
    M[i] = 0;
  }
}

void zero_vector_s(float*  V, int n) {
  zero_matrix_s(V, n, 1);
}
void zero_vector_d(double* V, int n) {
  zero_matrix_d(V, n, 1);
}

void show_matrix_s(float*  M, int n, int m) {
  int i, j;
  float* Mi;
  
  for (i = 0; i < n; ++i) {
    Mi = &M[i*m];
    printf("%.4f", Mi[0]);
    for (j = 1; j < m; ++j) {
      printf("\t%.4f", Mi[j]);
    }
    printf("\n");
  }
}
void show_matrix_d(double* M, int n, int m) {
  int i, j;
  double* Mi;
  
  for (i = 0; i < n; ++i) {
    Mi = &M[i*m];
    printf("%.4lf", Mi[0]);
    for (j = 1; j < m; ++j) {
      printf("\t%.4lf", Mi[j]);
    }
    printf("\n");
  }
}

void show_vector_s(float*  V, int n) {
  int i;
  printf("[ %.4f", V[0]);
  for (i = 1; i < n; ++i) {
    printf("\t%.4f", V[i]);
  }
  printf(" ]");
}
void show_vector_d(double* V, int n) {
  int i;
  printf("[ %.4lf", V[0]);
  for (i = 1; i < n; ++i) {
    printf("\t%.4lf", V[i]);
  }
  printf(" ]");
}
