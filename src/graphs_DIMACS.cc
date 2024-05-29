#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "canonical.h"
#include "digraph.h"

using namespace std;

void usage(ostream &os, const string &exec_name) {
    os << exec_name << " <file_with_graph_filenames>" << endl;
}

int main(int argc, const char **argv) {
    if( argc != 2 ) {
        usage(cout, argv[0]);
        return -1;
    }

    CanonicalColoring canonical_coloring(0);
    auto clock_begin = chrono::steady_clock::now();

    int num_graphs = 0;
    ifstream ifs_graphs(argv[1]);
    for( string line; getline(ifs_graphs, line); ) {
        if( line == "" ) {
            // Skip blank line
        } else if( line[0] == '!' ) {
            // Comment line
        } else {
            auto clock_start = chrono::steady_clock::now();
            Digraph *g = Digraph::read_DIMACS(line);
            vector<int> alpha(g->order(), 1);
            vector<set<int> > partition = canonical_coloring.calculate(*g, alpha);
            vector<int> histogram = CanonicalColoring::histogram(canonical_coloring.partition());
            int num_colors = canonical_coloring.num_colors();
            auto clock_stop = chrono::steady_clock::now();
            double microseconds = chrono::duration_cast<chrono::microseconds>(clock_stop - clock_start).count();
            //cout << line << " (n=" << g->order() << ", m=" << g->num_edges() << ") " << histogram << " " << microseconds / 1e3 << " millisecond(s)" << endl;
            cout << line << " (n=" << g->order() << ", m=" << g->num_edges() << ") k=" << num_colors << " color(s) " << microseconds / 1e3 << " millisecond(s)" << endl;
            delete g;
            ++num_graphs;
        }
    }

    auto clock_end = chrono::steady_clock::now();
    double duration = chrono::duration_cast<chrono::microseconds>(clock_end - clock_begin).count();
    cout << num_graphs << " graph(s) processed in " << duration / 1e6 << " second(s)" << endl;

    return 0;
}

