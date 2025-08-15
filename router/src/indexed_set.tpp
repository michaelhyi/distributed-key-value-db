#include <stdexcept>

template <typename T>
void IndexedSet<T>::insert(const T& data) {
    auto it = index_map.find(data);

    if (it != index_map.end()) {
        return;
    }

    index_map[data] = items.size();
    items.push_back(data);
}

template <typename T>
void IndexedSet<T>::remove(const T& data) {
    auto it = index_map.find(data);

    if (it == index_map.end()) {
        throw std::runtime_error("Data not found");
    }

    std::size_t index = it->second;
    std::swap(items[index], items[items.size() - 1]);
    index_map[items[index]] = index;
    index_map.erase(data);
    items.pop_back();
}

template <typename T>
std::size_t IndexedSet<T>::size() const {
    return items.size();
}

template <typename T>
bool IndexedSet<T>::empty() const {
    return items.size() == 0;
}

template <typename T>
const T& IndexedSet<T>::operator [](std::size_t index) const {
    if (index >= items.size()) {
        throw std::runtime_error("Index out of bounds");
    }

    return items[index];
}
