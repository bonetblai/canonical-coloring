#ifndef DIGRAPH_H
#define DIGRAPH_H

#include<vector>
#include<cassert>

class Digraph {
  protected:
    int n_; // number of vertices
    int m_; // number of edges
    std::vector<std::vector<int> > in_, out_;
    std::set<std::pair<int, int> > edges_;

  public:
    Digraph(int n) : n_(n), m_(0) {
        in_.resize(n_);
        out_.resize(n_);
    }
    void uadd(int u, int v) {
        add(u, v);
        add(v, u);
    }
    void add(int u, int v) {
        assert(0 <= u and u < n_);
        assert(0 <= v and v < n_);
        auto edge = std::make_pair(u, v);
        if( edges_.find(edge) == edges_.end() ) {
            edges_.insert(edge);
            in_.at(v).push_back(u);
            out_.at(u).push_back(v);
            ++m_;
        }
    }
    int order() const { return n_; }
    int num_edges() const { return m_; }
    const std::vector<int>& in(int u) const { return in_.at(u); }
    const std::vector<int>& out(int u) const { return out_.at(u); }
};

#endif

