#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Edge {
  int node;
  int weight;
  struct Edge* next;
} Edge;

typedef struct Graph {
  int node_count;
  struct Edge** edges;
} Graph;

Graph* create_graph(int node_count);
Graph* build_graph_from_file(char* fn);

void add_edge(Graph* g, int n1, int n2);
void add_dedge(Graph* g, int n1, int n2);
void add_wedge(Graph* g, int n1, int n2, int wt);

void free_graph(Graph* g);
void free_edge(Edge* e);

#endif
