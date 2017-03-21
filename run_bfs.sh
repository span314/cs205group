#!/bin/bash
echo 'run on host'
export ACC_DEVICE_TYPE=host

./BFS.o 4 RMATGraphs/rmat_2-2.txt
# Distance to goal 4 is 1
# 1 -> 4

./BFS.o 4 RMATGraphs/rmat_3-3.txt
# Distance to goal 4 is 2
# 1 -> 7 -> 4

./BFS.o 57 RMATGraphs/rmat_6-2.txt
# Distance to goal 57 is 2
# 1 -> 12 -> 57

./BFS.o 61 RMATGraphs/rmat_6-2.txt
# Unable to find path to 61 after 65 steps

./BFS.o 756 RMATGraphs/rmat_10-4.txt
# Distance to goal 756 is 3
# 1 -> 2 -> 892 -> 756

./BFS.o 1021 RMATGraphs/rmat_10-16.txt
# Distance to goal 1021 is 2
# 1 -> 704 -> 1021

./BFS.o 1021 RMATGraphs/rmat_12-16.txt
# Distance to goal 1021 is 4
# 1 -> 2895 -> 3803 -> 2944 -> 1021

./BFS.o 6932 RMATGraphs/rmat_14-16.txt
# Distance to goal 6932 is 3
# 1 -> 7605 -> 14933 -> 6932

time ./BFS.o 2001 RMATGraphs/rmat_12-16.txt 
#No solution -- this takes the longest
# Unable to find path to 2001 after 4097 steps

echo 'run on GPU'
export ACC_DEVICE_TYPE=nvidia
time ./BFS.o 2001 RMATGraphs/rmat_12-16.txt
