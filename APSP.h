#ifndef APSP_H
#define APSP_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "quadtree.h"
#define inf INFINITY

void floyd_apsp(float* A, int n);
void tropical_apsp(float* A, unsigned int n);
void tropical_apsp2(float* A, int n);
void tropical_gemm(float* A, float* B, float* C, unsigned int n);
void minplace(float* A, float* B, int n);

#endif
