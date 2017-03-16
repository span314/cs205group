#include "c_utest.h"
#include "graph.h"

void graphs_work() {
  int n = 10;
  Graph* g = create_graph(n); 

  for (int i = 0; i < n; i++)
    ASSERT_EQUAL_PTRS(g->edges[i], NULL);

  add_edge(g, 1, 2);

  ASSERT_DIFFN_PTRS(g->edges[1], NULL);
  ASSERT_DIFFN_PTRS(g->edges[2], NULL);
  ASSERT_EQUAL_PTRS(g->edges[1]->next, NULL);
  ASSERT_EQUAL_PTRS(g->edges[2]->next, NULL);
  ASSERT_EQUAL_INTS(g->edges[1]->node, 2);
  ASSERT_EQUAL_INTS(g->edges[2]->node, 1);

  add_edge(g, 1, 3);

  ASSERT_DIFFN_PTRS(g->edges[1]->next, NULL);
  ASSERT_EQUAL_PTRS(g->edges[1]->next->next, NULL);
  ASSERT_EQUAL_INTS(g->edges[1]->node, 3);
  ASSERT_EQUAL_INTS(g->edges[1]->next->node, 2);

  free_graph(g);
}

int main() {
  TEST_THAT(graphs_work);
  RUN_TESTS();
}
