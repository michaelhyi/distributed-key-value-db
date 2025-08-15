#pragma once

#include <vector>
#include <unordered_map>

template <typename T>
class IndexedSet {
private:
    std::vector<T> items;
    std::unordered_map<T, std::size_t> index_map;

public:
    void insert(const T& data);
    void remove(const T& data);
    std::size_t size() const;
    bool empty() const;
    const T& operator [](std::size_t index) const;
};

#include "indexed_set.tpp"
