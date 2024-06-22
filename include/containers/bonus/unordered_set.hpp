#ifndef UNORDERED_SET_OPEN_ADDRESSING_H
#define UNORDERED_SET_OPEN_ADDRESSING_H

#include <functional>
#include <memory>
#include "hashtable.hpp"
#include "./../pair.hpp"
#include "./../utils.hpp"
#include "./../iterators.hpp"

namespace ft {

template<
    typename Key,
    typename Hash = ft::hash<Key>,
    typename Allocator = std::allocator<Key> >
class unordered_set {
public:
    typedef Key key_type;
    typedef Key value_type;
    typedef ft::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Hash hasher;
    typedef Allocator allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;

    typedef typename HashTable<Key, void, Hash>::iterator iterator;
    typedef typename HashTable<Key, void, Hash>::const_iterator const_iterator;

    unordered_set(size_t initial_capacity = 16)
        : _hash_table(false, initial_capacity), element_count(0) {}

    void insert(const Key& key) {
        if (_hash_table.insert(key)) {
            ++element_count;
        }
    }

    bool remove(const Key& key) {
        if (_hash_table.erase(key)) {
            --element_count;
            return true;
        }
        return false;
    }

    bool contains(const Key& key) const {
        return _hash_table.find(key) != _hash_table.end();
    }

    size_t size() const {
        return element_count;
    }

    iterator find(const key_type& key) {
        return _hash_table.find(key);
    }

    const_iterator find(const key_type& key) const {
        return _hash_table.find(key);
    }

    void erase(iterator position) {
        if (_hash_table.erase(*position)) {
            --element_count;
        }
    }

    size_type erase(const key_type& key) {
        return remove(key) ? 1 : 0;
    }

    void clear() {
        _hash_table = HashTable<Key, void, Hash>(false);
        element_count = 0;
    }

    bool empty() const {
        return element_count == 0;
    }

    // swap
    void swap(unordered_set& other) {
        ft::swap(_hash_table, other._hash_table);
        ft::swap(element_count, other.element_count);
    }

    iterator begin() {
        return _hash_table.begin();
    }

    const_iterator begin() const {
        return _hash_table.begin();
    }

    iterator end() {
        return _hash_table.end();
    }

    const_iterator end() const {
        return _hash_table.end();
    }

private:
    HashTable<Key, void, Hash> _hash_table;
    size_t element_count;
};

} // namespace ft

#endif // UNORDERED_SET_OPEN_ADDRESSING_H
