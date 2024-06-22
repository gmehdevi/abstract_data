#ifndef FT_HASHTABLE_HPP
#define FT_HASHTABLE_HPP

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <memory>
#include "./../vector.hpp"
#include "./../utils.hpp"
#include "./../pair.hpp"

namespace ft {

template <typename T>
struct KeyExtractor {
    static const T& key(const T& value) {
        return value;
    }
};

template <typename Key, typename T>
struct KeyExtractor<ft::pair<const Key, T> > {
    static const Key& key(const ft::pair<const Key, T>& value) {
        return value.first;
    }
};

template <typename Key, typename T = void, typename Hash = ft::hash<Key>, typename KeyEqual = ft::equal_to<Key>, typename Allocator = std::allocator<Key> >
class HashTable;

template <typename Key>
class HashTableIterator;

template <typename Key>
class HashTableConstIterator;

template <typename Key>
struct Node {
    Key value;
    bool is_occupied;

    Node() : value(), is_occupied(false) {}
    Node(const Key& value, bool is_occupied) : value(value), is_occupied(is_occupied) {}
};

template <typename Key>
class HashTableIterator {
public:
    typedef Key value_type;
    typedef value_type& reference;
    typedef value_type* pointer;

    HashTableIterator(Node<Key>* ptr = NULL, Node<Key>* end = NULL) : _ptr(ptr), _end(end) {
        advance_to_valid();
    }

    reference operator*() const {
        return _ptr->value;
    }

    pointer operator->() const {
        return &(_ptr->value);
    }

    HashTableIterator& operator++() {
        ++_ptr;
        advance_to_valid();
        return *this;
    }

    HashTableIterator operator++(int) {
        HashTableIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const HashTableIterator& other) const {
        return _ptr == other._ptr;
    }

    bool operator!=(const HashTableIterator& other) const {
        return _ptr != other._ptr;
    }

private:
    void advance_to_valid() {
        while (_ptr != _end && !_ptr->is_occupied) {
            ++_ptr;
        }
    }

    Node<Key>* _ptr;
    Node<Key>* _end;
};

template <typename Key>
class HashTableConstIterator {
public:
    typedef const Key value_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;

    HashTableConstIterator(const Node<Key>* ptr = NULL, const Node<Key>* end = NULL) : _ptr(ptr), _end(end) {
        advance_to_valid();
    }

    reference operator*() const {
        return _ptr->value;
    }

    pointer operator->() const {
        return &(_ptr->value);
    }

    HashTableConstIterator& operator++() {
        ++_ptr;
        advance_to_valid();
        return *this;
    }

    HashTableConstIterator operator++(int) {
        HashTableConstIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const HashTableConstIterator& other) const {
        return _ptr == other._ptr;
    }

    bool operator!=(const HashTableConstIterator& other) const {
        return _ptr != other._ptr;
    }

private:
    void advance_to_valid() {
        while (_ptr != _end && !_ptr->is_occupied) {
            ++_ptr;
        }
    }

    const Node<Key>* _ptr;
    const Node<Key>* _end;
};

template <typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
class HashTable {
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef typename ft::conditional<ft::is_void<T>::value, Key, ft::pair<const Key, T> >::type value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Hash hasher;
    typedef KeyEqual key_equal;
    typedef typename Allocator::template rebind<Node<value_type> >::other allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef HashTableIterator<value_type> iterator;
    typedef HashTableConstIterator<value_type> const_iterator;

    explicit HashTable(bool multi = true, size_type bucket_count = 8, const hasher& hash = hasher(), const key_equal& equal = key_equal(), const allocator_type& alloc = allocator_type())
        : _multi(multi), _bucket_count(bucket_count), _hash(hash), _key_equal(equal), _size(0), _buckets(alloc) {
        _buckets.resize(_bucket_count);
    }

    bool insert(const value_type& value) {
        if (_size >= _bucket_count / 2) {
            rehash(_bucket_count * 2);
        }

        const key_type& key = KeyExtractor<value_type>::key(value);
        size_type index = _hash(key) % _bucket_count;
        for (size_type i = 0; i < _bucket_count; ++i) {
            size_type idx = (index + i) % _bucket_count;
            if (_buckets[idx].is_occupied) {
                if (!_multi && _key_equal(KeyExtractor<value_type>::key(_buckets[idx].value), key)) {
                    return false;
                }
            } else {
                alloc.construct(&_buckets[idx], Node<value_type>(value, true));
                _buckets[idx].is_occupied = true;
                ++_size;
                return true;
            }
        }

        return false;
    }

    bool erase(const key_type& key) {
        size_type index = _hash(key) % _bucket_count;
        for (size_type i = 0; i < _bucket_count; ++i) {
            size_type idx = (index + i) % _bucket_count;
            if (_buckets[idx].is_occupied && _key_equal(KeyExtractor<value_type>::key(_buckets[idx].value), key)) {
                _buckets[idx].is_occupied = false;
                --_size;
                return true;
            }
        }

        return false;
    }

    iterator find(const key_type& key) {
        size_type index = _hash(key) % _bucket_count;
        for (size_type i = 0; i < _bucket_count; ++i) {
            size_type idx = (index + i) % _bucket_count;
            if (_buckets[idx].is_occupied && _key_equal(KeyExtractor<value_type>::key(_buckets[idx].value), key)) {
                return iterator(&_buckets[idx], &_buckets[0] + _bucket_count);
            }
        }

        return end();
    }

    const_iterator find(const key_type& key) const {
        size_type index = _hash(key) % _bucket_count;
        for (size_type i = 0; i < _bucket_count; ++i) {
            size_type idx = (index + i) % _bucket_count;
            if (_buckets[idx].is_occupied && _key_equal(KeyExtractor<value_type>::key(_buckets[idx].value), key)) {
                return const_iterator(&_buckets[idx], &_buckets[0] + _bucket_count);
            }
        }

        return end();
    }

    iterator begin() {
        return iterator(_buckets.data(), _buckets.data() + _bucket_count);
    }

    iterator end() {
        return iterator(_buckets.data() + _bucket_count, _buckets.data() + _bucket_count);
    }

    const_iterator begin() const {
        return const_iterator(_buckets.data(), _buckets.data() + _bucket_count);
    }

    const_iterator end() const {
        return const_iterator(_buckets.data() + _bucket_count, _buckets.data() + _bucket_count);
    }

    size_type size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

private:
    void rehash(size_type new_bucket_count) {
        ft::vector<Node<value_type>, allocator_type> new_buckets(new_bucket_count);

        for (size_type i = 0; i < _bucket_count; ++i) {
            if (_buckets[i].is_occupied) {
                const key_type& key = KeyExtractor<value_type>::key(_buckets[i].value);
                size_type index = _hash(key) % new_bucket_count;
                for (size_type j = 0; j < new_bucket_count; ++j) {
                    size_type idx = (index + j) % new_bucket_count;
                    if (!new_buckets[idx].is_occupied) {
                        alloc.construct(&_buckets[idx], Node<value_type>(_buckets[i].value, true));
                        new_buckets[idx].is_occupied = true;
                        break;
                    }
                }
            }
        }

        _bucket_count = new_bucket_count;
        _buckets.swap(new_buckets);
    }

    bool _multi;
    size_type _bucket_count;
    hasher _hash;
    key_equal _key_equal;
    size_type _size;
    ft::vector<Node<value_type>, allocator_type> _buckets;
    allocator_type alloc;
};

} // namespace ft

#endif // FT_HASHTABLE_HPP
