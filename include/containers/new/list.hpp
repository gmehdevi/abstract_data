#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <algorithm>
#include <iostream>
#include <cstddef>
#include "list_iterators.hpp"
#include <limits>
#include "./../utils.hpp"
#include "./../iterators.hpp"

namespace ft {

template <typename T, typename Alloc = std::allocator<ListNode<T> > >
class list {
private:
    typedef ListNode<T> Node;

public:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef list_iterator<T> iterator;
    typedef list_iterator<const T> const_iterator;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;

    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;

private:
    Node* sentinel;
    size_type count;
    Alloc nodeAllocator;

public:
    list() : count(0) {
        sentinel = nodeAllocator.allocate(1);
        nodeAllocator.construct(sentinel, Node());
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
    }

    explicit list(size_type n, const value_type& val = value_type()) : count(0) {
        sentinel = nodeAllocator.allocate(1);
        nodeAllocator.construct(sentinel, Node());
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        insert(begin(), n, val);
    }

    template <class InputIterator>
    list(InputIterator first, InputIterator last) : count(0) {
        sentinel = nodeAllocator.allocate(1);
        nodeAllocator.construct(sentinel, Node());
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        insert(begin(), first, last);
    }

    list(const list& other) : count(0) {
        sentinel = nodeAllocator.allocate(1);
        nodeAllocator.construct(sentinel, Node());
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        insert(begin(), other.begin(), other.end());
    }

    list& operator=(const list& other) {
        if (this != &other) {
            clear();
            insert(begin(), other.begin(), other.end());
        }
        return *this;
    }

    ~list() {
        clear();
        nodeAllocator.destroy(sentinel);
        nodeAllocator.deallocate(sentinel, 1);
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void push_back(const value_type& val) {
        Node* newNode = nodeAllocator.allocate(1);
        nodeAllocator.construct(newNode, Node(val));

        newNode->prev = sentinel->prev;
        newNode->next = sentinel;
        sentinel->prev->next = newNode;
        sentinel->prev = newNode;
        ++count;
    }

    void push_front(const value_type& val) {
        Node* newNode = nodeAllocator.allocate(1);
        nodeAllocator.construct(newNode, Node(val));

        newNode->next = sentinel->next;
        newNode->prev = sentinel;
        sentinel->next->prev = newNode;
        sentinel->next = newNode;
        ++count;
    }

    void pop_back() {
        if (!empty()) {
            Node* toDelete = sentinel->prev;
            toDelete->prev->next = sentinel;
            sentinel->prev = toDelete->prev;

            nodeAllocator.destroy(toDelete);
            nodeAllocator.deallocate(toDelete, 1);
            --count;
        }
    }

    void pop_front() {
        if (!empty()) {
            Node* toDelete = sentinel->next;
            toDelete->next->prev = sentinel;
            sentinel->next = toDelete->next;

            nodeAllocator.destroy(toDelete);
            nodeAllocator.deallocate(toDelete, 1);
            --count;
        }
    }

    iterator insert(const_iterator pos, const value_type& val) {
        Node* newNode = nodeAllocator.allocate(1);
        nodeAllocator.construct(newNode, Node(val));
        Node* current = pos.current;

        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        ++count;
        return iterator(newNode);
    }

    void insert(const_iterator pos, size_type n, const value_type& val) {
        for (size_type i = 0; i < n; ++i) {
            insert(pos, val);
        }
    }

    template <class InputIterator>
    void insert(const_iterator pos, InputIterator first, InputIterator last) {
        while (first != last) {
            insert(pos, *first);
            first++;
        }
    }

    iterator erase(iterator pos) {
        if (pos != end()) {
            Node* toRemove = pos.current;
            toRemove->prev->next = toRemove->next;
            toRemove->next->prev = toRemove->prev;
            iterator retVal(toRemove->next);

            nodeAllocator.destroy(toRemove);
            nodeAllocator.deallocate(toRemove, 1);
            --count;
            return retVal;
        }
        return end();
    }

    iterator erase(iterator first, iterator last) {
        while (first != last) {
            first = erase(first);
        }
        return last;
    }

    void resize(size_type n, value_type val = value_type()) {
        if (n < count) {
            iterator it = begin();
            ft::advance(it, n);
            erase(it, end());
        } else if (n > count) {
            insert(end(), n - count, val);
        }
    }

    void assign(size_type n, const value_type& val) {
        clear();
        insert(begin(), n, val);
    }

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last) {
        clear();
        insert(begin(), first, last);
    }

    void swap(list& other) {
        ft::swap(sentinel, other.sentinel);
        ft::swap(count, other.count);
    }

    template <class Compare>
    void merge(list& other, Compare comp) {
        iterator it = begin(), ot = other.begin();
        while (it != end() && ot != other.end()) {
            if (comp(*ot, *it)) {
                iterator next_ot = ft::next(ot);
                splice(it, other, ot, next_ot);
                ot = next_ot;
            } else {
                ++it;
            }
        }
        if (ot != other.end()) {
            splice(end(), other, ot, other.end());
        }
    }

    void merge(list& other) {
        merge(other, ft::less<value_type>());
    }

    void splice(const_iterator pos, list& other) {
        if (this != &other && !other.empty()) {
            Node* first_of_other = other.sentinel->next;
            Node* last_of_other = other.sentinel->prev;

            first_of_other->prev = pos.current->prev;
            pos.current->prev->next = first_of_other;

            last_of_other->next = pos.current;
            pos.current->prev = last_of_other;

            other.sentinel->next = other.sentinel;
            other.sentinel->prev = other.sentinel;

            this->count += other.count;
            other.count = 0;
        }
    }

    void splice(const_iterator pos, list& other, const_iterator it) {
        if (this == &other) {
            return;
        }
        if (it == other.end()) {
            return;
        }
        Node* current = it.current;
        current->prev->next = current->next;
        current->next->prev = current->prev;

        current->next = pos.current;
        current->prev = pos.current->prev;
        pos.current->prev->next = current;
        pos.current->prev = current;
        ++count;
        other.count--;
    }

    void splice(const_iterator pos, list& other, const_iterator first, const_iterator last) {
        if (this == &other) {
            return;
        }
        insert(pos, first, last);
        other.erase(first, last);
    }

    void remove(const value_type& val) {
        iterator it = begin();
        while (it != end()) {
            if (*it == val) {
                it = erase(it);
            } else {
                it++;
            }
        }
    }

    template <class Predicate>
    void remove_if(Predicate pred) {
        iterator it = begin();
        while (it != end()) {
            if (pred(*it)) {
                it = erase(it);
            } else {
                it++;
            }
        }
    }

    void unique() {
        iterator it = begin();
        while (it != end()) {
            iterator next = it;
            next++;
            if (next != end() && *it == *next) {
                erase(next);
            } else {
                it++;
            }
        }
    }

    template <class BinaryPredicate>
    void unique(BinaryPredicate binary_pred) {
        iterator it = begin();
        while (it != end()) {
            iterator next = it;
            next++;
            if (next != end() && binary_pred(*it, *next)) {
                erase(next);
            } else {
                it++;
            }
        }
    }

    void reverse() {
        if (empty()) {
            return;
        }
        Node* current = sentinel;
        do {
            ft::swap(current->next, current->prev);
            current = current->prev;  // move to the next node which is now previous
        } while (current != sentinel);
    }

    template <class Compare>
    void sort(Compare comp) {
        if (count <= 1) return;

        list left;
        list right;
        size_type middle = count / 2;
        Node* current = sentinel->next;

        // Splitting the list into two halves
        for (size_type i = 0; i < middle; ++i) {
            left.push_back(current->data);
            current = current->next;
        }

        while (current != sentinel) {
            right.push_back(current->data);
            current = current->next;
        }

        // Recursively sort both lists
        left.sort(comp);
        right.sort(comp);

        // Clearing the original list
        clear();

        // Merging the sorted lists back into the original list
        iterator lit = left.begin();
        iterator rit = right.begin();
        while (lit != left.end() && rit != right.end()) {
            if (comp(*lit, *rit)) {
                push_back(*lit++);
            } else {
                push_back(*rit++);
            }
        }

        // Adding any remaining elements
        while (lit != left.end()) {
            push_back(*lit++);
        }

        while (rit != right.end()) {
            push_back(*rit++);
        }
    }

    void sort() {
        sort(ft::less<value_type>());
    }

    size_type size() const {
        return count;
    }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max() / sizeof(Node);
    }

    bool empty() const {
        return count == 0;
    }

    reference front() {
        return *(begin());
    }

    const_reference front() const {
        return *(begin());
    }

    reference back() {
        return *(--end());
    }

    const_reference back() const {
        return *(--end());
    }

    iterator begin() {
        return iterator(sentinel->next);
    }

    iterator end() {
        return iterator(sentinel);
    }

    const_iterator begin() const {
        return const_iterator(sentinel->next);
    }

    const_iterator end() const {
        return const_iterator(sentinel);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    allocator_type get_allocator() const {
        return allocator_type();
    }

    bool operator==(const list& rhs) const {
        if (size() != rhs.size()) {
            return false;
        }
        const_iterator it1 = begin();
        const_iterator it2 = rhs.begin();
        while (it1 != end()) {
            if (*it1 != *it2) {
                return false;
            }
            it1++;
            it2++;
        }
        return true;
    }

    bool operator!=(const list& rhs) const {
        return !(*this == rhs);
    }

    bool operator<(const list& rhs) const {
        const_iterator it1 = begin();
        const_iterator it2 = rhs.begin();
        while (it1 != end() && it2 != rhs.end()) {
            if (*it1 < *it2) {
                return true;
            } else if (*it1 > *it2) {
                return false;
            }
            it1++;
            it2++;
        }
        return size() < rhs.size();
    }

    bool operator<=(const list& rhs) const {
        return !(rhs < *this);
    }

    bool operator>(const list& rhs) const {
        return rhs < *this;
    }

    bool operator>=(const list& rhs) const {
        return !(*this < rhs);
    }

};

} // namespace ft

#endif // LINKED_LIST_H
