#ifndef MKL_CHOLESKY_H
#define MKL_CHOLESKY_H

void generate_cholesky_L_s(float*  L, int n);
void generate_cholesky_L_d(double* L, int n);

void generate_cholesky_x_s(float*  rhs, int n);
void generate_cholesky_x_d(double* rhs, int n);

void generate_cholesky_A_s(float*  A, const float*  L, int n);
void generate_cholesky_A_d(double* A, const double* L, int n);

void generate_cholesky_rhs_s(float*  rhs, const float*  A, const float*  x, int n);
void generate_cholesky_rhs_d(double* rhs, const double* A, const double* x, int n);

void generate_cholesky_system_s(float*  A, float*  L, float*  x, float*  rhs, int n);
void generate_cholesky_system_d(double* A, double* L, double* x, double* rhs, int n);

int allocate_generate_cholesky_system_s(float**  Aptr, float**  Lptr, float**  xptr, float**  rhsptr, int n);
int allocate_generate_cholesky_system_d(double** Aptr, double** Lptr, double** xptr, double** rhsptr, int n);

#endif //MKL_CHOLESKY_H
