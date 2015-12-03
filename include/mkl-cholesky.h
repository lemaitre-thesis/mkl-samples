#ifndef MKL_CHOLESKY_H
#define MKL_CHOLESKY_H


// System generation
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


// System solving
void factorize_cholesky_s(const float*  A, float*  L, int n);
void factorize_cholesky_d(const double* A, double* L, int n);

void forward_cholesky_s(const float*  A, const float*  rhs, float*  x, int n);
void forward_cholesky_d(const double* A, const double* rhs, double* x, int n);

int is_valid_cholesky_factorization_s(const float*  L, int n);
int is_valid_cholesky_factorization_d(const double* L, int n);

int solve_cholesky_system_s(const float*  A, float*  L, float*  x, const float*  rhs, int n);
int solve_cholesky_system_d(const double* A, double* L, double* x, const double* rhs, int n);

#endif //MKL_CHOLESKY_H
