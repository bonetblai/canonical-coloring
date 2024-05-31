#include <iostream>
#include <set>
#include <vector>

// Forward reference
template<typename U, typename V> std::ostream& operator<<(std::ostream &os, const std::pair<U, V> &v);
template<typename T> std::ostream& operator<<(std::ostream &os, const std::set<T> &v);

template<typename U, typename V>
std::ostream& operator<<(std::ostream &os, const std::pair<U, V> &p) {
    os << "(" << p.first << "," << p.second << ")" << std::flush;
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "[";
    for( size_t i = 0; i < v.size(); ++i ) {
        os << v.at(i) << std::flush;
        if( i + 1 < v.size() ) os << " ";
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::set<T> &s) {
    os << "{";
    size_t i = 0;
    for( typename std::set<T>::const_iterator it = s.begin(); it != s.end(); ++it ) {
        os << *it << std::flush;
        if( i++ + 1 < s.size() ) os << " ";
    }
    os << "}";
    return os;
}

