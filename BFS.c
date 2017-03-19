#include <stdio.h>
#include <math.h>
#include <string.h>
#include "graph.h"

// Note: Has a memory bug I'm still tracking down -- segfaults in some cases!  :(
// Also, no parallelization yet... 
// Usage: ./BFS 5 RMATGraphs/rmat_3-2.txt

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
	Graph* G = create_graph(n_nodes);
	
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


int* make_1D_int_arr(int arraySize){
	// Make n-sized array of zeros 
	int* arr;
	arr = (int*) malloc(arraySize*sizeof(int));
	
	for (int i=1; i<arraySize; i++){
		arr[i]=0;
		}
	
    return arr;
}


int A_IJ(Graph* G,int i, int j){
	// Treats graph as a matrix
	// (slowly) look’s up if there’s an i,j edge
	// (Used for testing) 
 
	i += 1;
	j += 1; 
	
	Edge *head = G->edges[i];
	int temp;
	while (head) {
		temp = head->node;
		if (temp == j){return 1;}
		head = head->next;
		}		
	return 0; 
}

	
void print_path(int start,int goal,int* parent){
	// Prints path from start to goal
	
	char str[100];
	sprintf(str, "%i", goal);
	int p = parent[goal-1];
	
	char* str_copy;
	str_copy = malloc(sizeof(char) * strlen(str));
	strcpy(str_copy,str);
	
	while (p != start){
		strcpy(str_copy,str);
		sprintf(str_copy, "%d -> %s",p,str);
		p = parent[p-1];
		strcpy(str,str_copy);
	}
	
	printf("\n%d -> %s",start,str_copy);
}
				
void p_arr(int* arr, int N, char* str){
	printf("\n %s:",str);
	
	for (int i=0; i<N; i++){
		printf("%i,",arr[i]);
	}
	printf("\n");
	
}

int main(int argc, char *argv[]) {
	
	if (argc != 3) {
		printf("Usage: %s N_to_find filename\n",argv[0]);
		return 1;
	}
	
	char* fn = argv[2];
	Graph* G = build_graph_from_file(fn);
	
	int N = G -> node_count;

	int goal = atoi(argv[1]); 
	
	// Stores number of moves away from starting position 
	int* level = make_1D_int_arr(N);
	// Parent of node via most efficient path  
	int* parent = make_1D_int_arr(N);
	// Nodes at current level to follow 
	int* frontier = make_1D_int_arr(N);
	frontier[0] = 1; 
	
	int* x = make_1D_int_arr(N);
	x[0] = 1;
	
	int* y = make_1D_int_arr(N);
	
	
	int i,j;

	int dist = 0;
	int fron_limit = 1; 
	int fron_start = 0;
	int parent_id = 1;
	while (level[goal-1]==0 && dist <= N){
		dist += 1;
		printf("\n**Dist %i\n",dist);
		
		
		for (i=fron_start; i<fron_limit; i++){
			y[i]=0;
			
			//printf("\ni:%i,F_start:%i,F_limt:%i",i,fron_start,fron_limit);
			//p_arr(frontier,N,"Fron");
			
			parent_id = frontier[i];
			Edge *head = G->edges[parent_id];
			printf("at %i\n",parent_id);
			while (head) {
				printf("Finding new node\n");
				if(head){printf("Head defined\n");}
				j = head->node;
				printf("Sub 1\n");
				j -= 1; 
				printf("Looking at %i\n",j+1);
				if(j < 0 || j > N-1){
					// This should not be needed, but sometimes I'm following nodes into undefined space... 
					printf("**Break!**");
					break;
					}
		
				   if(j !=0 && level[j] == 0){
					//printf("found %i\n",j+1);
					frontier[fron_limit] = j+1; 
					fron_limit += 1;
					level[j] = level[parent_id-1] + 1;
					parent[j] = parent_id;

					
				} else{
					//printf("See %i again\n",j+1);
				}
				
				y[i] += 1 + x[j];
				printf("Done with %i\n",j+1);
				head = head->next;
				printf("Moving Head\n");
				}
				printf("Done with par %i\n",parent_id);
				frontier[i] = -1;
				fron_start +=1;
				//p_arr(parent,N,"parent");
				//p_arr(level,N,"level");	

		}
		
			
		for (i = 0; i < N; i++){
			if(i !=0 && level[i] == 0 &&  x[i] == 0 && y[i] == 1){
				//printf("**found %i\n",i+1);			
			}
			x[i] = y[i];
		
	
	}}
					
	//p_arr(x,N,"x"); 
	
	p_arr(parent,N,"parent");
	p_arr(level,N,"level");
	
	print_path(1,goal,parent);
	free_graph(G);

}