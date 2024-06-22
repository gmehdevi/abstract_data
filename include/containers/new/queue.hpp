#ifndef QUEUE_H
#define QUEUE_H

#include "./deque.hpp"

namespace ft {

    template <typename T, typename Container = ft::deque<T> >
    class queue {

    protected:
        Container c;

    public:
        typedef T value_type;
        typedef Container container_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

        explicit queue(const Container& cont = Container()) : c(cont) {}

        queue(const queue& other) : c(other.c) {}

        ~queue() {}

        queue& operator=(const queue& other) {
            c = other.c;
            return *this;
        }

        // Element access
        reference front() {
            return c.front();
        }

        const_reference front() const {
            return c.front();
        }

        reference back() {
            return c.back();
        }

        const_reference back() const {
            return c.back();
        }

        // Capacity
        bool empty() const {
            return c.empty();
        }

        size_type size() const {
            return c.size();
        }

        // Modifiers
        void push(const value_type& value) {
            c.push_back(value);
        }

        void pop() {
            c.pop_front();
        }

        void swap(queue& other) {
            c.swap(other.c);
        }

        // Non-member functions
        friend bool operator==(const queue& rhs, const queue& lhs) {
            return (rhs.c == lhs.c);
        }

        friend bool operator!=(const queue& rhs, const queue& lhs) {
            return (rhs.c != lhs.c);
        }

        friend bool operator<(const queue& rhs, const queue& lhs) {
            return (rhs.c < lhs.c);
        }

        friend bool operator>(const queue& rhs, const queue& lhs) {
            return (rhs.c > lhs.c);
        }

        friend bool operator<=(const queue& rhs, const queue& lhs) {
            return (rhs.c <= lhs.c);
        }

        friend bool operator>=(const queue& rhs, const queue& lhs) {
            return (rhs.c >= lhs.c);
        }
    };
}

#endif
