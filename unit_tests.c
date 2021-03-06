#include "c_utest.h"
#include "graph.h"
#include "APSP.h"
#include "BFS.h"

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

void bfs_algorithms_work() {
  Graph* G = create_graph(8);
  add_edge(G, 1, 0);
  add_edge(G, 6, 0);
  add_edge(G, 2, 1);
  add_edge(G, 3, 1);
  add_edge(G, 6, 1);
  add_edge(G, 7, 3);
  add_edge(G, 6, 5);
  EdgeList* edgelist = build_edgelist(G);
  int* edges = edgelist->edges;
  int* offsets = edgelist->edge_offset;
  int goal = 3;

  ASSERT_EQUAL_INTS(1, edgelist_BFS(edges, offsets, 0, 1, 8));
  ASSERT_EQUAL_INTS(2, edgelist_BFS(edges, offsets, 0, 2, 8));
  ASSERT_EQUAL_INTS(2, edgelist_BFS(edges, offsets, 0, 3, 8));
  ASSERT_EQUAL_INTS(-1, edgelist_BFS(edges, offsets, 0, 4, 8));
  ASSERT_EQUAL_INTS(2, edgelist_BFS(edges, offsets, 0, 5, 8));
  ASSERT_EQUAL_INTS(4, edgelist_BFS(edges, offsets, 5, 7, 8));
}

void quadtree_indexing_works() {
  ASSERT_EQUAL_INTS(qx(0, 0), 0);
  ASSERT_EQUAL_INTS(qx(5, 0), 34);
  ASSERT_EQUAL_INTS(qx(7, 7), 63);
}

void apsp_algorithms_work() {
  // Initialize two distance matrices --
  // One in row major form:
  float distances[16] = {
    0.0, inf, 3.0, inf,
    2.0, 0.0, inf, inf,
    inf, 7.0, 0.0, 1.0,
    6.0, inf, inf, 0.0
  };
  float distances1[16] = {
    0.0, inf, 3.0, inf,
    2.0, 0.0, inf, inf,
    inf, 7.0, 0.0, 1.0,
    6.0, inf, inf, 0.0
  };

  // ...and one in quadtree form:
  float distances2[16];
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      distances2[qx(i,j)] = distances[i*4+j];

  // Run both algorithms
  floyd_apsp_sequential(distances, 4);
  tropical_quadtree_apsp(distances2, 4);
  tropical_apsp(distances1, 4);

  // Assert equality
  float expected[16] = {
    0, 10, 3, 4,
    2, 0, 5, 6,
    7, 7, 0, 1,
    6, 16, 9, 0
  };

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ASSERT_EQUAL_INTS(expected[i*4+j], distances[i*4+j]);
      ASSERT_EQUAL_INTS(expected[i*4+j], distances1[i*4+j]);
      ASSERT_EQUAL_INTS(expected[i*4+j], distances2[qx(i,j)]);
    }
  }
}

int main() {
  TEST_THAT(graphs_work);
  TEST_THAT(quadtree_indexing_works);
  TEST_THAT(apsp_algorithms_work);
  TEST_THAT(bfs_algorithms_work);
  RUN_TESTS();
}
