#include "graph.h"

Graph* create_graph(int node_count) {
  Graph* g = malloc(sizeof(Graph));
  g-> node_count = node_count;
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

Graph* build_graph_from_file(char* fn) {
	// Determines the max number of nodes from file name
	// Scale is in pows of 2 -- i.e., 4 = 2^4 = 16
	int scale, edgefactor;
	int sscanf_ret = sscanf(fn, "RMATGraphs/rmat_%d-%d.txt", &scale,&edgefactor);

	if(sscanf_ret != 2){
		printf("Warning: Unable to determine expected graph size from filename (%s)\n",fn);
	}

	// Create graph object
	int u, v, w;
	int n_nodes = pow(2,scale);
	//int n_nodes= 100000;
	Graph* G = create_graph(n_nodes*2); // Doubling node number because otherwise I run into memory issues

	FILE *ptr_file;
	ptr_file = fopen(fn,"r");

	if (!ptr_file){
		printf("Warning: File %s not found\n",fn);}

	// Read in file and add edges
	while (fscanf(ptr_file, "%i %i %i", &u,&v,&w)!=EOF){
		//printf("%i->%i\n",u,v);
		add_dedge(G, u, v);
	}
	fclose(ptr_file);
	return G;
}
