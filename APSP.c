#include "APSP.h"

void floyd_apsp(float* D, int n) {
  int changed;
  for (int k = 0; k < n; k++) {
    changed = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        float detour = D[i*n + k] + D[k*n + j];
        if (detour < D[i*n + j]) {
          D[i*n + j] = detour;
          changed += 1;
        }
      }
    }
    if (changed == 0) break;
  }
}

void tropical_gemm(float* A, float* B, float* C, unsigned int n) {
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      float c = inf;
      for (unsigned int k = 0; k < n; k++)
        c = fmin(c, A[quadex(i,k)] + B[quadex(k,j)]);
      C[quadex(i,j)] = c;
    }
  }
}

void minplace(float* A, float* B, int n) {
  for (int i = 0; i < n*n; i++) {
    A[i] = fmin(A[i], B[i]);
  }
}

void tropical_apsp(float* A, unsigned int n) {
  if (n > 1) {
    int l = n/2;
    size_t size = l*l*sizeof(float);
    float* temp = (float*)malloc(size);
    float* A11 = A;
    float* A12 = A + n*n/4;
    float* A21 = A + n*n/2;
    float* A22 = A + 3*n*n/4;

    tropical_apsp(A11, l);
    tropical_gemm(A11, A12, temp, l); memcpy(A12, temp, size);
    tropical_gemm(A21, A11, temp, l); memcpy(A21, temp, size);
    tropical_gemm(A21, A12, temp, l); minplace(A22, temp, l);

    tropical_apsp(A22, l);
    tropical_gemm(A22, A21, temp, l); memcpy(A21, temp, size);
    tropical_gemm(A12, A22, temp, l); memcpy(A12, temp, size);
    tropical_gemm(A12, A21, temp, l); minplace(A11, temp, l);

    free(temp);
  }
}

void tropical_gemm2(float* A, float* B, float* C, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      float c = inf;
      for (int k = 0; k < n; k++)
        c = fmin(c, A[i*n+k] + B[k*n+j]);
      C[i*n+j] = c;
    }
  }
}

void tropical_apsp2(float* A, int n) {
  if (n > 1) {
    int l = n/2;
    size_t size = l*l*sizeof(float);
    float* A11 = (float*)malloc(size);
    float* A12 = (float*)malloc(size);
    float* A21 = (float*)malloc(size);
    float* A22 = (float*)malloc(size);
    float* temp = (float*)malloc(size);
    float* quads[4] = { A11, A12, A21, A22 };
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        quads[2*(i>=l)+(j>=l)][(i%l)*l+(j%l)] = A[i*n + j];

    tropical_apsp2(A11, l);
    tropical_gemm2(A11, A12, temp, l); memcpy(A12, temp, size);
    tropical_gemm2(A21, A11, temp, l); memcpy(A21, temp, size);
    tropical_gemm2(A21, A12, temp, l); minplace(A22, temp, l);

    tropical_apsp2(A22, l);
    tropical_gemm2(A22, A21, temp, l); memcpy(A21, temp, size);
    tropical_gemm2(A12, A22, temp, l); memcpy(A12, temp, size);
    tropical_gemm2(A12, A21, temp, l); minplace(A11, temp, l);

    for (int i = 0; i < l; i++) {
      for (int j = 0; j < l; j++) {
        A[( i )*n+( j )] = A11[i*l+j];
        A[( i )*n+(j+l)] = A12[i*l+j];
        A[(i+l)*n+( j )] = A21[i*l+j];
        A[(i+l)*n+(j+l)] = A22[i*l+j];
      }
    }

    free(A11);
    free(A12);
    free(A21);
    free(A22);
    free(temp);
  }
}
