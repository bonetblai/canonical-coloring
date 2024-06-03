#include <iostream>
#include <set>
#include <vector>

#include "canonical.h"
#include "digraph.h"

using namespace std;

int main(int argc, const char **argv) {
    CanonicalColoring canonical_coloring(0);
    vector<int> alpha;
    vector<set<int> > partition;

    //   0 - 1 - 2 - 3
    //   |   | X |   |
    //   4 - 5 - 6 - 7
    cout << "% Example with 8 vertices about Partition Fefinement in https://pallini.di.uniroma1.it/Introduction.html" << endl;
    Digraph g1(8);
    g1.uadd(0, 1);
    g1.uadd(0, 4);
    g1.uadd(1, 2);
    g1.uadd(1, 5);
    g1.uadd(1, 6);
    g1.uadd(2, 3);
    g1.uadd(2, 5);
    g1.uadd(2, 6);
    g1.uadd(3, 7);
    g1.uadd(4, 5);
    g1.uadd(5, 6);
    g1.uadd(6, 7);
    alpha = { 1, 1, 1, 1,  1, 1, 1, 2 };
    partition = canonical_coloring.calculate(g1, alpha, true);
    cout << "Canonical equitable partition: " << partition << endl;
    cout << "Histogram: " << CanonicalColoring::histogram(canonical_coloring.partition()) << endl;
    cout << "Quotient matrix: " << canonical_coloring.quotient_matrix() << endl;
    cout << "Representation: " << canonical_coloring.representation() << endl;

    cout << endl << "% Example with 10 vertices about Equitable Partition and Orbit Partition in https://pallini.di.uniroma1.it/Introduction.html" << endl;
    Digraph g2(10);
    g2.uadd(0, 2);
    g2.uadd(0, 3);
    g2.uadd(1, 4);
    g2.uadd(1, 5);
    g2.uadd(2, 6);
    g2.uadd(2, 9);
    g2.uadd(3, 7);
    g2.uadd(3, 8);
    g2.uadd(4, 6);
    g2.uadd(4, 8);
    g2.uadd(5, 7);
    g2.uadd(5, 9);
    g2.uadd(6, 8);
    g2.uadd(7, 9);
    alpha = { 2, 2, 1, 1, 1,   1, 1, 1, 1, 1 };
    partition = canonical_coloring.calculate(g2, alpha, true);
    cout << "Canonical equitable partition: " << partition << endl;
    cout << "Histogram: " << CanonicalColoring::histogram(canonical_coloring.partition()) << endl;
    cout << "Quotient matrix: " << canonical_coloring.quotient_matrix() << endl;
    cout << "Representation: " << canonical_coloring.representation() << endl;

    // Hexagon
    cout << endl << "% Hexagon" << endl;
    Digraph g3(6);
    g3.uadd(0, 1);
    g3.uadd(1, 2);
    g3.uadd(2, 3);
    g3.uadd(3, 4);
    g3.uadd(4, 5);
    g3.uadd(5, 0);
    alpha = { 1, 1, 1, 1, 1, 1 };
    partition = canonical_coloring.calculate(g3, alpha, true);
    cout << "Canonical equitable partition: " << partition << endl;
    cout << "Histogram: " << CanonicalColoring::histogram(canonical_coloring.partition()) << endl;
    cout << "Quotient matrix: " << canonical_coloring.quotient_matrix() << endl;
    cout << "Representation: " << canonical_coloring.representation() << endl;

    // Petersen graph
    cout << endl << "% Petersen graph" << endl;
    Digraph g4(10);
    g4.uadd(0, 1);
    g4.uadd(0,5);
    g4.uadd(1,2);
    g4.uadd(1,6);
    g4.uadd(2,3);
    g4.uadd(2,7);
    g4.uadd(3,4);
    g4.uadd(3,8);
    g4.uadd(4,0);
    g4.uadd(4,9);
    g4.uadd(5,7);
    g4.uadd(5,8);
    g4.uadd(6,8);
    g4.uadd(6,9);
    g4.uadd(7,9);
    alpha = { 1, 1, 1, 1, 1,  1, 1, 1, 1, 1 };
    partition = canonical_coloring.calculate(g4, alpha, true);
    cout << "Canonical equitable partition: " << partition << endl;
    cout << "Histogram: " << CanonicalColoring::histogram(canonical_coloring.partition()) << endl;
    cout << "Quotient matrix: " << canonical_coloring.quotient_matrix() << endl;
    cout << "Representation: " << canonical_coloring.representation() << endl;

    return 0;
}

