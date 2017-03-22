#include "timer.h"
#include "graph.h"
#include "APSP.h"

int main() {
  //Graph* g = build_graph_from_file("RMATGraphs/rmat_2-2.txt");
  //int n = g->node_count;
  //float* D1 = build_matrix_from_graph(g);
  //float* D2 = build_quadtree_from_matrix(D1, g->node_count);
  //float* D3 = build_matrix_from_graph(g);
  int n = 64;
  float* D1 = (float*)malloc(n*n*sizeof(float));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i==j) {
        D1[i*n+j] = 0;
      } else if (i % 3 == 0) {
        D1[i*n+j] = 1;
      } else if (j % 2 == 0) {
        D1[i*n+j] = 2;
      } else {
        D1[i*n+j] = inf;
      }
    }
  }
  float* D2 = build_quadtree_from_matrix(D1, n);
  float* D3 = (float*)malloc(n*n*sizeof(float));
  memcpy(D3, D1, n*n*sizeof(float));

  double t1, t2, t3;

  set_timer();
  floyd_apsp_early_return(D1, n);
  t1 = get_timer();

  set_timer();
  tropical_quadtree_apsp(D2, (unsigned int)n);
  t2 = get_timer();

  set_timer();
  tropical_apsp(D3, n);
  t3 = get_timer();

  printf("the following should be equal\n");
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      printf("%f = %f = %f\n", D1[i*n + j], D2[qx(i,j)], D3[i*n + j]);
  printf("\n");

  printf("%f,%f,%f\n", t1, t2, t3);
}
