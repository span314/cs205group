#include "timer.h"
#include "graph.h"
#include "APSP.h"

int main() {
  Graph* g = build_graph_from_file("RMATGraphs/rmat_10-16.txt");
  float* D1 = build_matrix_from_graph(g);
  float* D2 = build_quadtree_from_matrix(D1, g->node_count);
  double t1, t2;

  set_timer();
  floyd_apsp(D1, g->node_count);
  t1 = get_timer();

  //set_timer();
  //tropical_apsp(D2, (unsigned int)g->node_count);
  //t2 = get_timer();
  t2 = inf;

  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      printf("%f should eq %f\n", D1[i*g->node_count + j], D2[quadex(i,j)]);

  printf("%f,%f\n", t1, t2);
}
