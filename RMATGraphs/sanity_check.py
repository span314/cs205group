# Sanity check to ensure that we don’t have any self-connected nodes 

fnames = ["rmat_2-2.txt","rmat_3-2.txt","rmat_6-2.txt","rmat_10-4.txt","rmat_10-16.txt","rmat_12-16.txt","rmat_14-16.txt"]

for fn in fnames:
	with open(fn) as f:
		for line in f:
			v1, v2, w = line.split()
			assert(v1 != v2)