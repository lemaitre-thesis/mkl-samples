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
