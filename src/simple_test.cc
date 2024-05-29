#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <cassert>

#include "canonical.h"
#include "digraph.h"

using namespace std;

int main(int argc, const char **argv) {
    CanonicalColoring canonical_coloring(0);

    //   0 - 1 - 2 - 3
    //   |   | X |   |
    //   4 - 5 - 6 - 7
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
    assert(g1.num_edges() == 2*12);
    vector<int> alpha = { 1, 1, 1, 1,  1, 1, 1, 2 };
    vector<set<int> > partition = canonical_coloring.calculate(g1, alpha);
    cout << "Canonical equitable partition: " << partition << endl;
    cout << "Histogram: " << canonical_coloring.histogram() << endl;

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
    assert(g2.num_edges() == 2*14);
    vector<int> beta = { 2, 2, 1, 1, 1,   1, 1, 1, 1, 1 };
    partition = canonical_coloring.calculate(g2, beta);
    cout << "Canonical equitable partition: " << partition << endl;
    cout << "Histogram: " << canonical_coloring.histogram() << endl;

    return 0;
}

