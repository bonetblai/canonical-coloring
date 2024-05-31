CC=clang++
CCFLAGS=-O3 -DNDEBUG -pedantic -Wall -std=c++11

all:		graphs_DIMACS simple_test

graphs_DIMACS:	graphs_DIMACS.cc canonical.h digraph.h util.h
		$(CC) -o graphs_DIMACS $(CCFLAGS) graphs_DIMACS.cc

simple_test:	simple_test.cc canonical.h digraph.h util.h
		$(CC) -o simple_test $(CCFLAGS) simple_test.cc

clean:
		rm -f graphs_DIMACS simple_test *~

