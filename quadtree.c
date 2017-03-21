#include "quadtree.h"

unsigned int quadex(unsigned int y, unsigned int x) {
  x = (x | (x << S[3])) & B[3];
  x = (x | (x << S[2])) & B[2];
  x = (x | (x << S[1])) & B[1];
  x = (x | (x << S[0])) & B[0];
  y = (y | (y << S[3])) & B[3];
  y = (y | (y << S[2])) & B[2];
  y = (y | (y << S[1])) & B[1];
  y = (y | (y << S[0])) & B[0];
  return x | (y << 1);
}

float* build_quadtree_from_matrix(float* M, unsigned int n) {
  float* Q = (float*)malloc(n * n * sizeof(float));
  for (unsigned int i = 0; i < n; i++)
    for (unsigned int j = 0; j < n; j++)
      Q[quadex(i, j)] = M[i*n + j];
  return Q;
}
