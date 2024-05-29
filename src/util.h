#include <iostream>
#include <set>
#include <vector>

// Forward reference
template<typename T> std::ostream& operator<<(std::ostream &os, const std::set<T> &v);

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "[";
    for( size_t i = 0; i < v.size(); ++i ) {
        os << v.at(i);
        if( i + 1 < v.size() ) os << " ";
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::set<T> &v) {
    os << "{";
    size_t i = 0;
    for( typename std::set<T>::const_iterator it = v.begin(); it != v.end(); ++it ) {
        os << *it;
        if( i++ + 1 < v.size() ) os << " ";
    }
    os << "}";
    return os;
}

