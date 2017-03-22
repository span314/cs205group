ifeq (, $(shell which pgcc))
	CC = gcc
else
	CC = pgcc -acc -Minfo=accel
endif

unit_tests: unit_tests.o graph.o APSP.o
bench_apsp: bench_apsp.o graph.o APSP.o
bfs: BFS.o graph.o

clean:
	-rm -f *.o
