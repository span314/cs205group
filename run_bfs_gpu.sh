#!/bin/bash
#pgcc -tp sandybridge-64 -acc -ta=nvidia -Minfo=accel BFS.c graph.c

./a.out 4 RMATGraphs/rmat_2-2.txt
echo 'Expected distance  to goal 4 is 1'
# 1 -> 4

./a.out 4 RMATGraphs/rmat_3-3.txt
echo 'Expected distance  to goal 4 is 2'
# 1 -> 7 -> 4

./a.out 57 RMATGraphs/rmat_6-2.txt
echo 'Expected distance  to goal 57 is 2'
# 1 -> 12 -> 57

./a.out 61 RMATGraphs/rmat_6-2.txt
echo 'Expected unable to find path to 61 after 65 steps'

./a.out 756 RMATGraphs/rmat_10-4.txt
echo 'Expected distance  to goal 756 is 3'
# 1 -> 2 -> 892 -> 756

./a.out 1021 RMATGraphs/rmat_10-16.txt
echo 'Expected distance  to goal 1021 is 2'
# 1 -> 704 -> 1021

./a.out 1021 RMATGraphs/rmat_12-16.txt
echo 'Expected distance  to goal 1021 is 4'
# 1 -> 2895 -> 3803 -> 2944 -> 1021

./a.out 6932 RMATGraphs/rmat_14-16.txt
echo 'Expected distance  to goal 6932 is 3'
# 1 -> 7605 -> 14933 -> 6932

time ./a.out 2001 RMATGraphs/rmat_12-16.txt 
#No solution -- this takes the longest
echo 'Expected unable to find path to 2001 after 4097 steps'

