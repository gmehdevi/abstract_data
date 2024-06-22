#ifndef DEQUE_H
#define DEQUE_H

#include "./../vector.hpp"
#include "./../utils.hpp"
#include <memory>
#include "deque_iterators.hpp"

namespace ft {
    template <typename T, typename Alloc = std::allocator<T> >
    class deque {
    public:
        typedef Alloc Allocator;
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename Alloc::reference reference;
        typedef typename Alloc::const_reference const_reference;
        typedef size_t size_type;

        typedef ft::deque_iterator<T> iterator;
        typedef ft::deque_iterator<const T> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename iterator::difference_type difference_type;
        typedef T* pointer;
        typedef const T* const_pointer;


        ft::vector<T, Alloc> front_;
        ft::vector<T, Alloc> back_;
    public:
        deque() : front_(), back_() {}

        explicit deque(const Allocator& alloc): front_(alloc), back_(alloc) {}

        explicit deque(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
            : front_(count/2, value, alloc), back_(count - count/2, value, alloc) {}

        template <class InputIterator>
        deque(InputIterator first, InputIterator last, const Allocator& alloc = Allocator()) : front_(alloc), back_(alloc) {
            for (InputIterator it = first; it != last; it++) {
                push_back(*it);
            }
        }

        deque(const deque& other) : front_(other.front_), back_(other.back_) {}

        bool empty() const {
            return front_.empty() && back_.empty();
        }

        size_type size() const {
            return front_.size() + back_.size();
        }

        size_type max_size() const {
            return front_.max_size() + back_.max_size();
        }

        reference at(size_type pos)  {
            if (pos < front_.size()) {
                return front_.at(pos);
            } else if (pos < size()) {
                return back_.at(pos - front_.size());
            } else {
                throw ft::out_of_range("Index out of range.");
            }
        }

        const_reference at(size_type pos) const {
            if (pos < front_.size()) {
                return front_.at(pos);
            } else if (pos < size()) {
                return back_.at(pos - front_.size());
            } else {
                throw ft::out_of_range("Index out of range.");
            }
        }

        reference operator[](size_type n)  {
            if (n < front_.size()) {
                return front_[n];
            } else if (n < size()) {
                return back_[n - front_.size()];
            } else {
                throw ft::out_of_range("Index out of range.");
            }
        }

        const_reference operator[](size_type n) const {
            if (n < front_.size()) {
                return front_[n];
            } else if (n < size()) {
                return back_[n - front_.size()];
            } else {
                throw ft::out_of_range("Index out of range.");
            }
        }

        reference front() {
            if (!front_.empty()) {
                return front_.front();
            } else if (!back_.empty()) {
                return back_.front();
            } else {
                throw ft::out_of_range("Front of deque is empty.");
            }
        }

        const_reference front() const {
            if (!front_.empty()) {
                return front_.front();
            } else if (!back_.empty()) {
                return back_.front();
            } else {
                throw ft::out_of_range("Front of deque is empty.");
            }
        }

        reference back() {
            if (!back_.empty()) {
                return back_.back();
            } else if (!front_.empty()) {
                return front_.back();
            } else {
                throw ft::out_of_range("Back of deque is empty.");
            }
        }

        const_reference back() const {
            if (!back_.empty()) {
                return back_.back();
            } else if (!front_.empty()) {
                return front_.back();
            } else {
                throw ft::out_of_range("Back of deque is empty.");
            }
        }

        iterator begin() {
            return iterator(&front_, &back_, 0);
        }

        const_iterator begin() const {
            return const_iterator(&front_, &back_, 0);
        }

        iterator end() {
            return iterator(&front_, &back_, size());
        }

        const_iterator end() const {
            return const_iterator(&front_, &back_, size());
        }

        reverse_iterator rbegin() {
            return reverse_iterator(iterator(&front_, &back_, size()));
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(const_iterator(&front_, &back_, size()));
        }

        reverse_iterator rend() {
            return reverse_iterator(iterator(&front_, &back_, 0));
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(const_iterator(&front_, &back_, 0));
        }

        void clear() {
            front_.clear();
            back_.clear();
        }

        iterator insert(const_iterator pos, const value_type& val) {
            difference_type index = pos - begin();

            // If the index is in the first half, insert into the 'front_' vector.
            if (index < difference_type(front_.size())) {
                front_.insert(front_.begin() + index, val);
            } else {
                back_.insert(back_.begin() + (index - front_.size()), val);
            }

            while (front_.size() > back_.size() + 1) {
                back_.insert(back_.begin(), front_.back());
                front_.pop_back();
            }

            while (front_.size() + 1 < back_.size()) {
                front_.push_back(back_.front());
                back_.erase(back_.begin());
            }
            return begin() + index;
        }


        template <class InputIterator>
        void insert(const_iterator pos, InputIterator first, InputIterator last) {
            difference_type index = pos - begin();
            while (first != last) {
                insert(begin() + index, *first);
                first++;
                index++;
            }
        }

        void insert(const_iterator pos, size_type count, const T& value) {
            for (size_type i = 0; i < count; ++i) {
                insert(pos, value);
            }
        }

        iterator erase(iterator pos) {
            difference_type index = pos - begin();
            if (index < difference_type(front_.size())) {
                front_.erase(front_.begin() + index);
            } else {
                back_.erase(back_.begin() + (index - front_.size()));
            }
            return begin() + std::min(index, difference_type(size()));
        }

        iterator erase(iterator first, iterator last) {
            difference_type index_first = first - begin();
            difference_type index_last =  last - begin();
            while(index_first != index_last) {
                erase(begin() + index_first);
                index_last--;
            }
            return begin() + std::min(index_first, difference_type(size()));
        }


        void push_back(const value_type& val) {
            back_.push_back(val);
        }

        void push_front(const value_type& val) {
            front_.insert(front_.begin(), val);
        }

        void pop_back() {
            if (!back_.empty()) {
                back_.pop_back();
            } else if (!front_.empty()) {
                front_.pop_back();
            }
        }

        void pop_front() {
            if (!front_.empty()) {
                front_.erase(front_.begin());
            } else if (!back_.empty()) {
                back_.erase(back_.begin());
            }
        }

        void resize(size_type count) {
            size_type sz = size();
            if (count < sz) {
                for (size_type i = 0; i < sz - count; i++) {
                    pop_back();
                }
            } else if (count > sz) {
                for (size_type i = 0; i <  count - sz; i++) {
                    push_back(value_type());
                }
            }
        }

        void resize(size_type count, const value_type& value) {
            if (count < size()) {
                for (size_type i = 0; i < size() - count; i++) {
                    pop_back();
                }
            } else if (count > size()) {
                for (size_type i = 0; i < count - size(); i++) {
                    push_back(value);
                }
            }
        }

        bool operator>=(const deque& other) const {
            vector<T> this_vector(this->begin(), this->end());
            vector<T> other_vector(other.begin(), other.end());
            return this_vector >= other_vector;
        }

        bool operator<=(const deque& other) const {
            vector<T> this_vector(this->begin(), this->end());
            vector<T> other_vector(other.begin(), other.end());
            return this_vector <= other_vector;
        }

        bool operator>(const deque& other) const {
            vector<T> this_vector(this->begin(), this->end());
            vector<T> other_vector(other.begin(), other.end());
            return this_vector > other_vector;
        }

        bool operator<(const deque& other) const {
            vector<T> this_vector(this->begin(), this->end());
            vector<T> other_vector(other.begin(), other.end());
            return this_vector < other_vector;
        }

        void swap(deque& other) {
            ft::swap(front_, other.front_);
            ft::swap(back_, other.back_);
        }

        friend void swap(deque& lhs, deque& rhs) {
            lhs.swap(rhs);
        }

        bool operator==(const deque& other) const {
            vector<T> this_vector(this->begin(), this->end());
            vector<T> other_vector(other.begin(), other.end());
            return this_vector == other_vector;
        }

        bool operator!=(const deque& other) const {
            return !(*this == other);
        }

    };
}

#endif
