// credit to http://graphics.stanford.edu/~seander/bithacks.html#InterleaveBMN

#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdlib.h>

static const unsigned int B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF};
static const unsigned int S[] = {1, 2, 4, 8};
unsigned int quadex(unsigned int y, unsigned int x);
float* build_quadtree_from_matrix(float* M, unsigned int n);

#endif
