#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "canonical.h"
#include "digraph.h"
#include "openssl_digests.h"

using namespace std;

void usage(ostream &os, const string &exec_name) {
    os << exec_name << " [-d | --digest] <file_with_graph_filenames>" << endl;
}

int main(int argc, const char **argv) {
    const string exec_name = argv[0];
    bool digest = false;
    for( ++argv, --argc; argc > 0 and **argv == '-'; ++argv, --argc ) {
        if( std::string(*argv) == "-d" or std::string(*argv) == "--digest" )
            digest = true;
        else if( std::string(*argv) == "-" ) {
            ++argv;
            --argc;
            break;
        } else {
            cout << "Unrecognized option '" << *argv << "'" << endl;
            usage(cout, exec_name);
            return -1;
        }
    }

    if( argc < 1 ) {
        usage(cout, exec_name);
        return -1;
    }
    cout << "Reading '" << *argv << "'" << endl;

    OpenSSL::Digests openssl_digests;
    CanonicalColoring canonical_coloring(0);
    auto clock_begin = chrono::steady_clock::now();

    int num_graphs = 0;
    ifstream ifs_graphs(*argv);
    for( string line; getline(ifs_graphs, line); ) {
        if( line == "" ) {
            // Skip blank line
        } else if( line[0] == '!' ) {
            // Comment line
        } else {
            auto clock_start = chrono::steady_clock::now();
            Digraph *g = Digraph::read_DIMACS(line);
            vector<int> alpha(g->order(), 1);
            vector<set<int> > partition = canonical_coloring.calculate(*g, alpha, digest);
            vector<int> histogram = CanonicalColoring::histogram(canonical_coloring.partition());
            int num_colors = canonical_coloring.num_colors();
            auto clock_stop = chrono::steady_clock::now();
            double microseconds = chrono::duration_cast<chrono::microseconds>(clock_stop - clock_start).count();

            if( !digest) {
                cout << line << " (n=" << g->order() << ", m=" << g->num_edges() << ") k=" << num_colors << " color(s) " << microseconds / 1e3 << " millisecond(s)" << endl;
            } else {
                string sha256 = openssl_digests.sha256(canonical_coloring.representation());
                cout << line << " (n=" << g->order() << ", m=" << g->num_edges() << ") k=" << num_colors << " color(s) " << sha256 << " " <<  microseconds / 1e3 << " millisecond(s)" << endl;
            }

            delete g;
            ++num_graphs;
        }
    }

    auto clock_end = chrono::steady_clock::now();
    double duration = chrono::duration_cast<chrono::microseconds>(clock_end - clock_begin).count();
    cout << num_graphs << " graph(s) processed in " << duration / 1e6 << " second(s)" << endl;

    return 0;
}

