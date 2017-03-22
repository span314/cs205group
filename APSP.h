#ifndef APSP_H
#define APSP_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define inf INFINITY

void floyd_apsp_early_return(float* A, int n);
void floyd_apsp_sequential(float* A, int n);
void floyd_apsp_parallel(float* A, int n);

void tropical_quadtree_gemm(float* A, float* B, float* C, unsigned int n);
void tropical_quadtree_apsp(float* A, unsigned int n);

void tropical_gemm(float* A, float* B, float* C, int n);
void tropical_apsp(float* A, int n);

void minplace(float* A, float* B, int n);

float* build_quadtree_from_matrix(float* M, unsigned int n);
unsigned int qx(unsigned int y, unsigned int x);

#endif
