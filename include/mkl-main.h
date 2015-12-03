#ifndef MKL_MAIN_H
#define MKL_MAIN_H

#define MEMORY_ALIGNMENT 64

float*  allocate_s(int n, int m);
double* allocate_d(int n, int m);

void free_s(float*  p);
void free_d(double* p);

void show_matrix_s(float*  M, int n, int m);
void show_matrix_d(double* M, int n, int m);

void show_vector_s(float*  V, int n);
void show_vector_d(double* V, int n);

void zero_matrix_s(float*  M, int n, int m);
void zero_matrix_d(double* M, int n, int m);

void zero_vector_s(float*  V, int n);
void zero_vector_d(double* V, int n);

#endif //MKL_MAIN_H
