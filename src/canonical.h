#ifndef CANONICAL_H
#define CANONICAL_H

#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <vector>
#include <cassert>

#include "digraph.h"
#include "util.h"

template<typename T>
class Stack {
  protected:
    std::vector<T> stack_;

  public:
    Stack() { }
    ~Stack() { }

    void initialize(int n) {
        stack_.resize(0);
        stack_.reserve(n);
    }

    bool empty() const { return stack_.empty(); }
    const T& top() const {
        if( !stack_.empty() )
            return stack_.back();
        else
            throw std::runtime_error("Attempt top() on empty stack");
    }
    T pop() {
        if( !stack_.empty() ) {
            T item = stack_.back();
            stack_.pop_back();
            return item;
        } else {
            throw std::runtime_error("Attempt pop() on empty stack");
        }
    }
    int push(const T item) {
        stack_.push_back(item);
        return stack_.back();
    }

    void print(std::ostream &os) const {
        os << stack_;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream &os, const Stack<T> &stack) {
    stack.print(os);
    return os;
}

class CanonicalColoring {
  protected:
    const int debug_;

    std::vector<std::set<int> >    C_; // Indexed by color. Partition. C[c] is set of vertices with color c
    std::vector<std::vector<int> > A_; // Indexed by color. A[c] is vertices of color c adjacent to vertices of color r
    std::vector<int> colour_;          // Indexed by vertex. colour[v] is color of vertex v
    std::vector<int> cdeg_;            // Indexed by vertex. Color degree d^+_r(v) = |N^+(v) \cap C_r| (number of out-neighbors of vertex v of color r)
    std::vector<int> maxcdeg_;         // Indexed by color. maxcdeg[c] = max { d^+_r(v) : v is of color c }
    std::vector<int> mincdeg_;         // Indexed by color. mincdeg[c] = min { d^+_r(v) : v is of color c }

    bool valid_M_;                                        // Whether the factor matrix was computed
    std::vector<std::pair<std::pair<int, int>, int> > M_; // Factor matrix

    int k_;
    Stack<int> s_refine_;
    std::vector<bool> in_s_refine_;

    void split_up_color(int s) {
        int maxcdeg = maxcdeg_.at(s);
        std::vector<int> numcdeg(1 + maxcdeg, 0);
        for( auto const& v : A_.at(s) ) {
            assert(cdeg_.at(v) > 0);
            numcdeg.at(cdeg_.at(v)) = numcdeg.at(cdeg_.at(v)) + 1;
        }
        numcdeg.at(0) = C_.at(s).size() - A_.at(s).size();

        if( debug_ > 1 ) {
            std::cout << "             A[" << s << "]: " << A_.at(s) << std::endl;
            std::cout << "             C[" << s << "]: " << C_.at(s) << std::endl;
            std::cout << "       maxcdeg[" << s << "]: " << maxcdeg_.at(s) << std::endl;
            std::cout << "          numcdeg: " << numcdeg << std::endl;
        }

        int b = 0;
        for( int i = 1; i <= maxcdeg; ++i ) {
            if( numcdeg.at(i) > numcdeg.at(b) )
                b = i;
        }

        if( debug_ > 1 ) std::cout << "                b: " << b << " (index for max entry in numcdeg)" << std::endl;

        bool in_stack = in_s_refine_.at(s);

        if( debug_ > 1 ) {
            std::cout << "            stack: " << s_refine_ << std::endl;
            std::cout << "    Is s in stack? " << in_stack << std::endl;
        }

        std::vector<int> f(1 + maxcdeg, -1);
        for( int i = 0; i <= maxcdeg; ++i ) {
            if( numcdeg.at(i) > 0 ) {
                if( i == mincdeg_.at(s) ) {
                    f.at(i) = s;
                    if( !in_stack and i != b ) {
                        s_refine_.push(f.at(i));
                        in_s_refine_.at(f.at(i)) = true;
                    }
                } else {
                    k_ = k_ + 1;
                    f.at(i) = k_;
                    if( in_stack or i != b ) {
                        s_refine_.push(f.at(i));
                        in_s_refine_.at(f.at(i)) = true;
                    }
                }
            }
        }
        if( debug_ > 1 ) std::cout << "                f: " << f << std::endl;

        for( auto const& v : A_.at(s) ) {
            if( f.at(cdeg_.at(v)) != s ) {
                assert(C_.at(s).find(v) != C_.at(s).end());
                if( debug_ > 1 ) std::cout << "            Delete v=" << v << " from C[s]=C[" << s << "]" << std::endl;
                C_.at(s).erase(v);
                if( debug_ > 1 ) std::cout << "            Append v=" << v << " to C[f[cdeg[v]]]=C[" << f.at(cdeg_.at(v)) << "]" << std::endl;
                C_.at(f.at(cdeg_.at(v))).insert(v);
                colour_.at(v) = f.at(cdeg_.at(v));
            }
        }

        if( debug_ > 1 ) {
            std::cout << "                C: " << C_ << std::endl;
            std::cout << "            stack: " << s_refine_ << std::endl;
        }
    }

    void calculate_factor_matrix(const Digraph &graph) {
        M_ = std::vector<std::pair<std::pair<int, int>, int> >();
        for( int i = 0; i < k_; ++i ) {
            int u = *C_.at(i).begin();
            std::vector<int> frequency(k_, 0);
            for( auto& v : graph.out(u-1) ) {
                int j = colour_.at(v+1);
                frequency.at(j-1) += 1;
            }
            assert(frequency.at(i) == 0);
            frequency.at(i) = C_.at(i).size();
            for( size_t j = 0; j < frequency.size(); ++j ) {
                if( frequency.at(j) > 0 )
                    M_.push_back(std::make_pair(std::make_pair(i+1, j+1), frequency.at(j)));
            }
        }
        valid_M_ = true;
    }

  public:
    CanonicalColoring(int debug = 0) : debug_(debug) { }
    ~CanonicalColoring() { }

    const std::vector<int>& coloring() const { return colour_; }
    const std::vector<std::set<int> >& partition() const { return C_; }
    int num_colors() const { return k_; }

    static std::vector<int> histogram(const std::vector<std::set<int> > &partition) {
        std::vector<int> hist;
        for( size_t i = 0; i < partition.size(); ++i )
            hist.push_back(partition.at(i).size());
        return hist;
    }

    static int check_coloring(const std::vector<int> &alpha, bool verbose=true) {
        int status = 0;

        // Check that min color in alpha is 1
        int min_color = std::numeric_limits<int>::max();
        for( auto const& c : alpha )
            min_color = std::min(min_color, c);
        if( min_color != 1 ) {
            status |= 1;
            if( verbose ) std::cout << "check_coloring: minimum color must be 1, got " << min_color  << std::endl;
        }
        if( min_color < 0 ) return status;

        // Check that there are no "color gaps"
        std::vector<int> frequency, gaps;
        for( auto const& c : alpha ) {
            frequency.resize(std::max(int(frequency.size()), 1 + c), 0);
            assert(c < frequency.size());
            frequency.at(c) += 1;
        }

        for( size_t i = frequency.size() - 1; i > 0; --i ) {
            assert(frequency.at(i) > 0);
            if( i > 1 and frequency.at(i-1) == 0 )
                gaps.push_back(i-1);
        }
        if( !gaps.empty() ) status |= 2;

        if( verbose and !gaps.empty()) {
            std::cout << "check_coloring: color gap(s) at";
            for( int i = gaps.size() - 1; i >= 0; --i ) {
              std::cout << " " << gaps.at(i);
              if( i > 0 ) std::cout << ",";
            }
            std::cout << std::endl;
        }

        return status;
    }

    const std::vector<std::set<int> >& calculate(const Digraph &graph, const std::vector<int> &alpha, bool factor_matrix = false) {
        if( CanonicalColoring::check_coloring(alpha, true) != 0 )
            throw std::runtime_error("invalid initial coloring");

        int n = graph.order();
        colour_ = std::vector<int>(n+1, 0);
        C_ = std::vector<std::set<int> >(n+1);
        A_ = std::vector<std::vector<int> >(n+1);
        mincdeg_ = std::vector<int>(n+1, -1);
        maxcdeg_ = std::vector<int>(n+1, 0);
        cdeg_ = std::vector<int>(n+1, 0);
        maxcdeg_.at(0) = -1;
        valid_M_ = false;

        // Create initial partition
        k_ = 0;
        colour_.at(0) = -1;
        for( int v = 0; v < n; ++v ) {
            C_.at(alpha.at(v)).insert(v+1);
            colour_.at(v+1) = alpha.at(v);
            k_ = std::max(k_, alpha.at(v));
        }

        if( debug_ > 0 ) {
            std::cout << "           C: " << C_ << std::endl;
            std::cout << "      colour: " << colour_ << std::endl;
            std::cout << "           k: " << k_ << std::endl;
        }

        std::vector<int> colors_adj;   // Colors adjacent to color r (popped from stack)
        std::vector<int> colors_split; // Colors in colors_adj that generate non-trivial splits

        s_refine_.initialize(n);
        in_s_refine_ = std::vector<bool>(n+1, false);
        std::vector<bool> in_colors_adj(n+1, false);
        colors_adj.reserve(n+1);
        colors_split.reserve(n+1);

        // Initialize stack
        for( int c = 1; c <= k_; ++c ) {
            in_s_refine_.at(c) = true;
            s_refine_.push(c);
        }

        if( debug_ > 0 ) {
            std::cout << "       stack: " << s_refine_ << std::endl;
            std::cout << "    in_stack: " << in_s_refine_ << std::endl;
        }

        // Main loop
        while( !s_refine_.empty() ) {
            int r = s_refine_.pop();
            in_s_refine_.at(r) = false;

            if( debug_ > 0 ) {
                std::cout << std::endl << "** Pop color r=" << r << ", stack: " << s_refine_ << std::endl;
                std::cout << "        colour: " << colour_ << std::endl;
                std::cout << "          cdeg: " << cdeg_ << std::endl;
                std::cout << "       maxcdeg: " << maxcdeg_ << std::endl;
                std::cout << "          C[" << r << "]: " << C_.at(r) << std::endl;
            }

            // Compute color degrees, max color degrees, A[i], and color_adj
            for( auto const& v : C_.at(r) ) {
                for( auto const& w : graph.in(v-1) ) {
                    cdeg_.at(w+1) = cdeg_.at(w+1) + 1;
                    if( cdeg_.at(w+1) == 1 ) {
                        // Conditional is to avoid inserting same vertex twice in array A
                        A_.at(colour_.at(w+1)).push_back(w+1);
                    }

                    if( !in_colors_adj.at(colour_.at(w+1)) ) {
                        in_colors_adj.at(colour_.at(w+1)) = true;
                        colors_adj.push_back(colour_.at(w+1));
                    }

                    if( cdeg_.at(w+1) > maxcdeg_.at(colour_.at(w+1)) )
                        maxcdeg_.at(colour_.at(w+1)) = cdeg_.at(w+1);
                }
            }

            if( debug_ > 0 ) {
                std::cout << "          cdeg: " << cdeg_ << std::endl;
                std::cout << "       maxcdeg: " << maxcdeg_ << std::endl;
                std::cout << "             A: " << A_ << std::endl;
                std::cout << "    colors_adj: " << colors_adj << std::endl;
                std::cout << " in_colors_adj: " << in_colors_adj << std::endl;
            }

            // Compute mincdeg for color r
            for( auto const& c : colors_adj ) {
                if( C_.at(c).size() != A_.at(c).size() ) {
                    mincdeg_.at(c) = 0;
                } else {
                    mincdeg_.at(c) = maxcdeg_.at(c);
                    for( auto const& v : A_.at(c) ) {
                        if( cdeg_.at(v) < mincdeg_.at(c) )
                            mincdeg_.at(c) = cdeg_.at(v);
                    }
                }
            }

            if( debug_ > 0 ) std::cout << "       mincdeg: " << mincdeg_ << std::endl;

            // Compute colors form colors_adj that result in non-trivial splits
            colors_split.resize(0);
            for( auto const& c : colors_adj ) {
                if( mincdeg_.at(c) < maxcdeg_.at(c) )
                    colors_split.push_back(c);
            }
            sort(colors_split.begin(), colors_split.end());

            if( debug_ > 0 ) std::cout << "  colors_split: " << colors_split << " (ordered)" << std::endl;

            // Calculate refinement
            for( auto const& s : colors_split )
                split_up_color(s);

            // Reset data structures
            if( debug_ > 0 ) std::cout << "  ** Reset data structures for next iteration" << std::endl;
            for( auto const& c : colors_adj ) {
                for( auto const& v : A_.at(c) )
                    cdeg_.at(v) = 0;
                mincdeg_.at(c) = -1; // EXTRA
                maxcdeg_.at(c) = 0;
                A_.at(c).resize(0);
                in_colors_adj.at(c) = false;
            }
            colors_adj.resize(0);

            if( debug_ > 0 ) {
                std::cout << "     new stack: " << s_refine_ << std::endl;
                std::cout << "      in_stack: " << in_s_refine_ << std::endl;
            }
        }

        // Simplify, compute factor matrix,  and return canonical equitable partition
        C_.assign(C_.begin() + 1, C_.begin() + 1 + k_);
        if( factor_matrix ) calculate_factor_matrix(graph);
        return C_;
    }

    std::string factor_matrix() const {
        if( !valid_M_ ) throw std::runtime_error("invalid factor matrix: call calculate() with third argument set to true");

        std::string code;
        for( auto& p : M_ ) {
           if( code != "" ) code += "-";
           //code += std::to_string(p.first.first) + ":" + std::to_string(p.first.second) + ":" + std::to_string(p.second);
           code += std::to_string(p.second) + "@(" + std::to_string(p.first.first) + "," + std::to_string(p.first.second) + ")";
        }
        return code;
    }
};

#endif

