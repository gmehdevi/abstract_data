#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "./../vector.hpp"
#include "queue.hpp"
#include <algorithm>

namespace ft {

    template <typename RandomAccessIterator, typename Compare>
    void sift_down(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator start, Compare comp) {
        ptrdiff_t n = last - first;
        ptrdiff_t i = start - first;

        while (true) {
            ptrdiff_t left_child = 2 * i + 1;
            ptrdiff_t right_child = left_child + 1;
            ptrdiff_t largest = i;
            if (left_child < n && comp(*(first + i), *(first + left_child)))
                largest = left_child;
            if (right_child < n && comp(*(first + largest), *(first + right_child)))
                largest = right_child;
            if (largest != i) {
                swap(*(first + i), *(first + largest));
                i = largest;
            } else {
                break;
            }
        }
    }

    template <typename RandomAccessIterator, typename Compare>
    void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        if (first == last) return;

        ptrdiff_t child = last - first - 1;
        ptrdiff_t parent;

        while (child > 0) {
            parent = (child - 1) / 2;
            if (!comp(*(first + parent), *(first + child)))
                break;

            ft::swap(*(first + parent), *(first + child));
            child = parent;
        }
    }

    template <typename RandomAccessIterator, typename Compare>
    void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        if (last - first < 2) return;

        ptrdiff_t n = (last - first);
        for (ptrdiff_t parent = (n / 2) - 1; parent >= 0; --parent) {
            sift_down(first, last, first + parent, comp);
        }
    }

    template <typename RandomAccessIterator, typename Compare>
    void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        if (first == last) return;

        ptrdiff_t n = last - first;
        swap(*first, *(first + n - 1));
        sift_down(first, last - 1, first, comp);
    }

    template <typename T, typename Container = ft::vector<T>, class Compare =ft::less<typename Container::value_type> >
    class priority_queue {

    protected:
        Container c;
        Compare comp;
    public:
        typedef T value_type;
        typedef Compare value_compare;
        typedef Container container_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;
        typedef typename Container::iterator iterator;
        typedef typename Container::const_iterator const_iterator;
        typedef typename Container::reverse_iterator reverse_iterator;
        typedef typename Container::const_reverse_iterator const_reverse_iterator;


        priority_queue(const Container& cont = Container()) : c(cont) {
            ft::make_heap(c.begin(), c.end(), comp);
        }

        priority_queue(const priority_queue& other) : c(other.c) {
            ft::make_heap(c.begin(), c.end(), comp);
        }

        priority_queue(const Compare& comp, const Container& cont = Container()) : c(cont), comp(comp) {
            ft::make_heap(c.begin(), c.end(), comp);
        }

        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Container& cont = Container()) : c(cont), comp(comp) {
            c.insert(c.end(), first, last);
            ft::make_heap(c.begin(), c.end(), comp);
        }

        priority_queue& operator=(const priority_queue& other) {
            c = other.c;
            return *this;
        }

        const_reference top() const {
            return c.front();
        }

        bool empty() const {
            return c.empty();
        }

        size_type size() const {
            return c.size();
        }

        void push(const value_type& value) {
            c.push_back(value);
            ft::push_heap(c.begin(), c.end(), comp);
        }


        void pop() {
            ft::pop_heap(c.begin(), c.end(), comp);
            c.pop_back();
        }

        void swap(priority_queue& other) {
            c.swap(other.c);
            ft::swap(comp, other.comp);
        }

        friend bool operator==(const priority_queue &rhs, const priority_queue &lhs) {
            return rhs.c == lhs.c;
        }

        friend bool operator!=(const priority_queue &rhs, const priority_queue &lhs) {
            return rhs.c != lhs.c;
        }

        friend bool operator<(const priority_queue &rhs, const priority_queue &lhs) {
            return rhs.c < lhs.c;
        }

        friend bool operator>(const priority_queue &rhs, const priority_queue &lhs) {
            return rhs.c > lhs.c;
        }

        friend bool operator<=(const priority_queue &rhs, const priority_queue &lhs) {
            return rhs.c <= lhs.c;
        }

        friend bool operator>=(const priority_queue &rhs, const priority_queue &lhs) {
            return rhs.c >= lhs.c;
        }

        friend void swap(priority_queue &x, priority_queue &y) {
           x.swap(y);
        }
    };
}

#endif
