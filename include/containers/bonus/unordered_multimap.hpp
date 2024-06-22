#ifndef FT_UNORDERED_MULTIMAP_HPP
#define FT_UNORDERED_MULTIMAP_HPP

#include "hashtable.hpp"
#include "./../pair.hpp"
#include "./../vector.hpp"

namespace ft {

template <typename Key, typename T, typename Hash = ft::hash<Key>, typename KeyEqual = ft::equal_to<Key> >
class unordered_multimap {
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef ft::pair<Key, T> value_type;
    typedef Hash hasher;
    typedef KeyEqual key_equal;
    typedef ft::size_t size_type;

    typedef typename HashTable<Key, T, Hash, KeyEqual>::iterator iterator;
    typedef typename HashTable<Key, T, Hash, KeyEqual>::const_iterator const_iterator;

    unordered_multimap() : _hash_table() {}

    explicit unordered_multimap(size_type bucket_count, const hasher& hash = hasher(), const key_equal& equal = key_equal())
        : _hash_table(bucket_count, hash, equal) {}

    template <typename InputIterator>
    unordered_multimap(InputIterator first, InputIterator last, size_type bucket_count = 8, const hasher& hash = hasher(), const key_equal& equal = key_equal())
        : _hash_table(bucket_count, hash, equal) {
        insert(first, last);
    }

    bool insert(const value_type& value) {
        return _hash_table.insert(value);
    }

    iterator insert(iterator pos, const value_type& value) {
        return _hash_table.insert(pos, value);
    }

    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for (InputIterator it = first; it != last; ++it) {
            _hash_table.insert(*it);
        }
    }

    iterator find(const key_type& key) {
        return _hash_table.find(key);
    }

    const_iterator find(const key_type& key) const {
        return _hash_table.find(key);
    }

    size_type count(const key_type& key) const {
        size_type count = 0;
        for (const_iterator it = begin(); it != end(); ++it) {
            if (it->first == key) {
                count++;
            }
        }
        return count;
    }

    T get(const key_type& key) const {
        const_iterator it = find(key);
        if (it == end()) {
            throw ft::runtime_error("Key not found");
        } else {
            return it->second;
        }
    }

    ft::vector<T> get(const key_type& key)  {
        ft::vector<T> values;
        for (const_iterator it = begin(); it != end(); ++it) {
            if (it->first == key) {
                values.push_back(it->second);
            }
        }
        return values;
    }

    size_type erase(const key_type& key) {
        size_type count = 0;
        for (iterator it = begin(); it != end(); ) {
            if (it->first == key) {
                it = _hash_table.erase(it);
                count++;
            } else {
                ++it;
            }
        }
        return count;
    }

    iterator erase(iterator pos) {
        bool result = _hash_table.erase(pos->first);
        if (result) {
            return pos;
        } else {
            return end();
        }
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
    HashTable<Key, T, Hash, KeyEqual> _hash_table;
};

} // namespace ft

#endif // FT_UNORDERED_MULTIMAP_HPP
