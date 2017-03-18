# Rmat graph generation 

Adopted from matlab kronecker graph generator algorithm here: 

https://github.com/graph500/graph500/tree/master/octave 

Generates undirected graphs of varies sizes. Output format is a list of edges, with 1 edge on each row:
> 2 3 1
(E.g., node 2 is connected to node 3, with weight 1) 
All edge weights are currently 1. 

To regenerate run with octave: 

octave make_graphs.m

Not sure this is possible easily load onto Odyssey – ended up doing it on my local machin with octave... 
-Nathaniel 
