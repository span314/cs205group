#include <stdio.h>
#include <math.h>
#include "graph.h"

// Note: Does not do anything yet besides read graph file from disk and create 
// Graph structure 
// Usage: ./BFS 4 RMATGraphs/rmat_3-2.txt 3
// Where 4 is the node to find

Graph* build_graph_from_file(char* fn) {
	
	// Determins the max number of nodes from file name
	// Scale is in pows of 2 -- i.e., 4 = 2^4 = 16 
	
	int scale, edgefactor; 
	int sscanf_ret = sscanf(fn, "RMATGraphs/rmat_%d-%d.txt", &scale,&edgefactor);
	
	if(sscanf_ret != 2){
		printf("Warning: Unable to determine expected graph size from filename (%s)\n",fn);
	}
	
	// Create graph object 
	int u, v, w;
	int n_nodes = pow(2,scale);
	Graph* G = create_graph(n_nodes);
	
	FILE *ptr_file;
	ptr_file = fopen(fn,"r");
	
	if (!ptr_file){
		printf("Warning: File %s not found\n",fn);}
	
	// Read in file and add edges 
	while (fscanf(ptr_file, "%i %i %i", &u,&v,&w)!=EOF){
		//printf("%i->%i\n",u,v);
		add_edge(G, u, v);
	}
	fclose(ptr_file);
	return G;
}

int main(int argc, char *argv[]) {
	
	if (argc != 3) {
		printf("Usage: %s N filename\n",argv[0]);
		return 1;
	}
	
	char* fn = argv[2];
	Graph* G = build_graph_from_file(fn);
	free_graph(G);

}