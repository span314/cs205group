% First parameter is scale, second is “edgefactor”% Generates graphs via kronecker methods with 2^scale nodes, % and (roughly) edgefactor * (2^scale) vertices % Returned graphs should be symmetric, with no-self connected nodes. % All edge weights are 1.  gen_graph(2, 2);gen_graph(3, 2);gen_graph(6, 2);gen_graph(10,4);gen_graph(10,16);gen_graph(12,16);% If we need to go bigger... % gen_graph(14,16);% gen_graph(16,16);