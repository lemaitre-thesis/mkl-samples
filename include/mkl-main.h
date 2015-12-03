#ifndef MKL_MAIN_H
#define MKL_MAIN_H

#define MEMORY_ALIGNMENT 64

float*  allocate_s(int n, int m);
double* allocate_d(int n, int m);

void free_s(float*);
void free_d(double*);

#endif //MKL_MAIN_H
