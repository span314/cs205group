#include "graph.h"

Graph* create_graph(int node_count) {
  Graph* g = malloc(sizeof(Graph));
  g->edges = malloc(sizeof(Edge*) * node_count);
  for (int i = 0; i < node_count; i++)
    g->edges[i] = NULL;
  return g;
}

void add_edge(Graph* g, int node1, int node2) {
  add_dedge(g, node1, node2);
  add_dedge(g, node2, node1);
}

void add_dedge(Graph* g, int node1, int node2) {
  add_wedge(g, node1, node2, 1);
}

void add_wedge(Graph* g, int node1, int node2, int wt) {
  Edge* olde = g->edges[node1];
  Edge* newe = malloc(sizeof(Edge));
  newe->node = node2;
  newe->next = olde;
  newe->weight = wt;
  g->edges[node1] = newe;
}

void free_edge(Edge* e) {
  if (e != NULL) {
    free_edge(e->next);
    free(e);
  }
}

void free_graph(Graph* g) {
  for (int i = 0; i < g->node_count; i++)
    free_edge(g->edges[i]);
  free(g->edges);
  free(g);
}
