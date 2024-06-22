#ifndef FT_UNORDERED_MULTISET_HPP
#define FT_UNORDERED_MULTISET_HPP

#include "hashtable.hpp"

namespace ft {

template <typename Key, typename Hash = ft::hash<Key>, typename KeyEqual = ft::equal_to<Key> >
class unordered_multiset {
public:
    typedef Key key_type;
    typedef Key value_type;
    typedef Hash hasher;
    typedef KeyEqual key_equal;
    typedef ft::size_t size_type;
    typedef HashTableIterator<Key> iterator;
    typedef HashTableConstIterator<Key> const_iterator;

    explicit unordered_multiset(size_type bucket_count = 8, const hasher& hash = hasher(), const key_equal& equal = key_equal())
        : _hash_table(true, bucket_count, hash, equal) {}

    template <typename InputIterator>
    unordered_multiset(InputIterator first, InputIterator last, size_type bucket_count = 8, const hasher& hash = hasher(), const key_equal& equal = key_equal())
        : _hash_table(true, bucket_count, hash, equal) {
        insert(first, last);
    }

    bool insert(const value_type& value) {
        return _hash_table.insert(value);
    }

    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for (InputIterator it = first; it != last; ++it) {
            _hash_table.insert(*it);
        }
    }

    bool erase(const key_type& key) {
        return _hash_table.erase(key);
    }

    iterator find(const key_type& key) {
        return _hash_table.find(key);
    }

    const_iterator find(const key_type& key) const {
        return _hash_table.find(key);
    }

    size_type size() const {
        return _hash_table.size();
    }

    bool empty() const {
        return _hash_table.empty();
    }

    iterator begin() {
        return _hash_table.begin();
    }

    iterator end() {
        return _hash_table.end();
    }

    const_iterator begin() const {
        return _hash_table.begin();
    }

    const_iterator end() const {
        return _hash_table.end();
    }

private:
    HashTable<Key, void, Hash, KeyEqual> _hash_table;
};

} // namespace ft

#endif // FT_UNORDERED_MULTISET_HPP
