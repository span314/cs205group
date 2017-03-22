#include <stdio.h>
#include <math.h>
#include <string.h>
#include "graph.h"

// Usage: ./BFS 5 RMATGraphs/rmat_3-2.txt
// Other examples: 
// 756 RMATGraphs/rmat_10-4.txt
// 1021 RMATGraphs/rmat_12-16.txt

int* make_1D_int_arr(int arraySize){
	// Make n-sized array of zeros 
	int* arr = (int*) malloc(arraySize*sizeof(int));
	memset(arr, 0, arraySize*sizeof(int));
    return arr;
}


int A_IJ(Graph* G,int i, int j){
	// Treats graph as a matrix
	// (slowly) look’s up if there’s an i,j edge
	// (I used for testing, but this not used in functions below) 
 
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
	// Pretty-prints path from start to goal
	// 1 -> 6 -> 5
	
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
	printf("\n%s:",str);
	
	for (int i=0; i<N; i++){
		printf("%i,",arr[i]);
	}
	printf("\n");
	
}

void traditional_BFS(Graph* G, int goal, int N){
	// Traditional implementation of BFS that tracks distance and path
	// From node 1 to goal node (if path exits) 

	// Stores number of moves away from starting position 
	int* level = make_1D_int_arr(N);
	// Parent of node via most efficient path  
	int* parent = make_1D_int_arr(N);
	// Nodes at current level to follow 
	int* frontier = make_1D_int_arr(N);
	frontier[0] = 1; 
		
	int i,j;

	int dist = 0;
	int fron_limit = 1; 
	int fron_start = 0;
	int parent_id = 1;

	while (level[goal-1]==0 && dist <= N){
		dist += 1;
		//printf("\n**Dist %i\n",dist);
		
		for (i=fron_start; i<fron_limit; i++){

			parent_id = frontier[i];
			Edge *head = G->edges[parent_id-1];
			//printf("at %i\n",parent_id);
			while (head) {
				j = head->node; 
				if(j !=0 && level[j] == 0){
					//printf("found %i\n",j+1);
					frontier[fron_limit] = j+1; 
					fron_limit += 1;
					level[j] = level[parent_id-1] + 1;
					parent[j] = parent_id;	
				}
				head = head->next;
			}
			frontier[i] = -1;
			fron_start +=1;
		}
		

	}
					
	//p_arr(parent,N,"parent");
	//p_arr(level,N,"level");
	printf("\n**Traditional BFS**");
	if(level[goal-1] > 0){
		printf("\nDistance to goal %i is %i",goal,level[goal-1]);
		print_path(1,goal,parent);
	} else{
		printf("\nUnable to find path to %i after %i steps",goal,dist);
	}
}


void p_BFS(Graph* G, int goal, int N){
	// Distance-only BFS using matrix-vector multiplication method (as I understand it)
	// Starts at node 0, and looks for path to goal node
	//
	// Note: I had a version that (almost) tracks the path as well, and it *mostly* works, 
	// but there are bugs that I can’t figure out and we’re running out of time….

	// Stores number of moves away from starting position 
	int* level = make_1D_int_arr(N);
	
	int* x = make_1D_int_arr(N);
	x[0] = 1;
	
	int* y = make_1D_int_arr(N);
	
	
	int i,j;
	int dist = 0;

        //Construct edgelist arrays because OpenAcc does not like linked list pointers
        EdgeList* edgelist = build_edgelist(G);
        int* const edges = edgelist->edges;
        int* const edge_offset = edgelist->edge_offset; 

	while (x[goal-1] == 0 && dist <= N){
		dist += 1;
		#pragma acc data copyin(y[:N],x[:N],edges[:edgelist->edge_count],edge_offset[:(N+1)]) copy(y[:N],x[:N])
		{
                #pragma acc parallel loop private(i,j)
		for (i=0; i<N; i++){
			y[i]=0;
                        for (j=edge_offset[i]; j<edge_offset[i+1]; j++) {
                                y[i] += 1 * x[edges[j]];
                        } 
		} 
		//p_arr(x,N,"x"); 
		#pragma acc parallel loop private(i,j)
		for (i = 0; i < N; i++){
			if((x[i] == 0) && (y[i] >= 1)){
			// First time we've found path to goal, 
			// update level array with current distance
				level[i] = dist;
			}
			x[i] += y[i];
		}
                }
       }


		if(x[goal-1] > 0){
			printf("\nDistance to goal %i is %i\n",goal,level[goal-1]);

		} else{
			printf("\nUnable to find path to %i after %i steps\n",goal,dist);
		}		
	}



int main(int argc, char *argv[]) {
	
	if (argc != 3) {
		printf("Usage: %s N_to_find filename\n",argv[0]);
		return 1;
	}
	
	char* fn = argv[2];

	Graph* G = build_graph_from_file(fn);
	
	// Correct for over-counting above 
	int N = G -> node_count;

	int goal = atoi(argv[1]);

	// Look for path with normal BFS
	// traditional_BFS(G,goal,N);
	// (Useful for testing -- prints out path)
	
	// And with m-v implementation
	p_BFS(G,goal,N);

	
	free_graph(G);
}
