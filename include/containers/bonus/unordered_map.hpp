#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <functional>
#include <memory>
#include "hashtable.hpp" // Include your HashTable implementation
#include "./../pair.hpp"
#include "./../utils.hpp"
#include "./../iterators.hpp"

namespace ft {

template<
    class Key,
    class T,
    class Hash = ft::hash<Key>,
    class KeyEqual = ft::equal_to<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
>
class unordered_map {
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef ft::pair<const Key, T> value_type;
    typedef ft::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Hash hasher;
    typedef KeyEqual key_equal;
    typedef Allocator allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename HashTable<Key, T, Hash, KeyEqual>::iterator iterator;
    typedef typename HashTable<Key, T, Hash, KeyEqual>::const_iterator const_iterator;

private:
    HashTable<Key, T, Hash, KeyEqual> table;
    hasher hash_fn;
    key_equal equals_fn;
    allocator_type alloc;

public:
    explicit unordered_map(size_type bucket_count = 16,
                           const Hash& hash = Hash(),
                           const KeyEqual& equal = KeyEqual(),
                           const Allocator& alloc = Allocator())
    : table(false, bucket_count, hash, equal), hash_fn(hash), equals_fn(equal), alloc(alloc) {}

    template <class InputIterator>
    unordered_map(InputIterator first, InputIterator last,
                  size_type bucket_count = 16,
                  const Hash& hash = Hash(),
                  const KeyEqual& equal = KeyEqual(),
                  const Allocator& alloc = Allocator())
    : table(bucket_count, hash, equal), hash_fn(hash), equals_fn(equal), alloc(alloc) {
        insert(first, last);
    }

    unordered_map(const unordered_map& other)
    : table(other.table), hash_fn(other.hash_fn), equals_fn(other.equals_fn), alloc(other.alloc) {}

    unordered_map& operator=(const unordered_map& other) {
        if (this != &other) {
            table = other.table;
            hash_fn = other.hash_fn;
            equals_fn = other.equals_fn;
            alloc = other.alloc;
        }
        return *this;
    }

    iterator begin() {
        return table.begin();
    }

    const_iterator begin() const {
        return table.begin();
    }

    iterator end() {
        return table.end();
    }

    const_iterator end() const {
        return table.end();
    }

    bool empty() const {
        return table.empty();
    }

    size_type size() const {
        return table.size();
    }

    size_type max_size() const {
        return alloc.max_size();
    }

    void clear() {
        table = HashTable<Key, T, Hash, KeyEqual>();
    }

    ft::pair<iterator, bool> insert(const value_type& value) {
        bool inserted = table.insert(value);
        return ft::make_pair(find(value.first), inserted);
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        while (first != last) {
            insert(*first);
            ++first;
        }
    }

    void erase(iterator pos) {
        table.erase(pos->first);
    }

    size_type erase(const key_type& key) {
        return table.erase(key);
    }

    void swap(unordered_map& other) {
        ft::swap(table, other.table);
        ft::swap(hash_fn, other.hash_fn);
        ft::swap(equals_fn, other.equals_fn);
        ft::swap(alloc, other.alloc);
    }

    size_type count(const key_type& key) const {
        return table.find(key) != table.end() ? 1 : 0;
    }

    iterator find(const key_type& key) {
        return table.find(key);
    }

    const_iterator find(const key_type& key) const {
        return table.find(key);
    }

    mapped_type& operator[](const key_type& key) {
        return table[key];
    }

    hasher hash_function() const {
        return hash_fn;
    }

    key_equal key_eq() const {
        return equals_fn;
    }

    allocator_type get_allocator() const {
        return alloc;
    }

    friend bool operator==(const unordered_map& lhs, const unordered_map& rhs) {
        return lhs.table == rhs.table;
    }

    friend bool operator!=(const unordered_map& lhs, const unordered_map& rhs) {
        return !(lhs == rhs);
    }
};

template <class Key, class T, class Hash, class KeyEqual, class Alloc>
void swap(unordered_map<Key, T, Hash, KeyEqual, Alloc>& lhs, unordered_map<Key, T, Hash, KeyEqual, Alloc>& rhs) {
    lhs.swap(rhs);
}

} // namespace ft

#endif // UNORDERED_MAP_H
