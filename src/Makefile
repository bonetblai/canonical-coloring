CCFLAGS=-O3 -DNDEBUG

all:	graphs_DIMACS test

graphs_DIMACS:	graphs_DIMACS.cc canonical.h digraph.h util.h
		clang++ -o graphs_DIMACS $(CCFLAGS) graphs_DIMACS.cc -std=c++11

test:	test.cc canonical.h digraph.h util.h
	clang++ -o test $(CCFLAGS) test.cc -std=c++11

clean:
	rm -f graphs_DIMACS test *~

