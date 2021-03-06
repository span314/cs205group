int edgelist_BFS(const int* edges, const int* offsets, int start, int goal, int N);
void edgelist_matrix_vector_multiply(const int* edges, const int* offsets, int* vector, int* result, int N);

int edgelist_BFS_parallel(const int* edges, const int* offsets, int start, int goal, int N);
void edgelist_matrix_vector_multiply_parallel(const int* edges, const int* offsets, int* vector, int* result, int N);
