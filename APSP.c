#include "APSP.h"

void floyd_apsp(float* distances, int n) {
  int changed;

  for (int k = 0; k < n; k++) {
    changed = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        float detour = distances[i*n + k] + distances[k*n + j];
        if (detour < distances[i*n + j]) {
          distances[i*n + j] = detour;
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

void minplace(float* A, float* B, unsigned int n) {
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      unsigned int q = quadex(i,j);
      A[q] = fmin(A[q], B[q]);
    }
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
