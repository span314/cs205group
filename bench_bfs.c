#include "timer.h"
#include "graph.h"
#include "BFS.h"

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: %s start goal filename\n", argv[0]);
    return 1;
  }

  int start = atoi(argv[1]);
  int goal = atoi(argv[2]);
  char* filename = argv[3];
  Graph* g = build_graph_from_file(filename);
  int n = g->node_count;
  EdgeList* edgelist = build_edgelist(g);
  int* const edges = edgelist->edges;
  int* const offsets = edgelist->edge_offset;
  int d1, d2;
  double t1, t2;

  set_timer();
  d1 = edgelist_BFS(edges, offsets, start, goal, n);
  t1 = get_timer();

  set_timer();
  d2 = edgelist_BFS_parallel(edges, offsets, start, goal, n);
  t2 = get_timer();

  if (d1 == d2) {
    printf("%d,%f,%f\n", n, t1, t2);
    return 0;
  } else {
    printf("unequal distances! seq got %d, par got %d\n", d1, d2);
    return 1;
  }

  free_graph(g);
}
