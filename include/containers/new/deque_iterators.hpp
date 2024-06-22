#ifndef DEQUE_ITERATORS_HPP
#define DEQUE_ITERATORS_HPP

#include "./../iterators.hpp"
#include "./../vector.hpp"

namespace ft {

    template <typename T>
    class deque_iterator : public iterator<ft::random_access_iterator_tag, T> {
    public:
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
        typedef T* pointer;
        typedef T& reference;

    private:
        template <typename U>
        struct ConditionalVectorPtr {
            typedef ft::vector<U>* type;
        };

        template <typename U>
        struct ConditionalVectorPtr<const U> {
            typedef const ft::vector<const U>* type;
        };

        typedef typename ConditionalVectorPtr<T>::type VectorPtr;

    public:
        VectorPtr front;
        VectorPtr back;
        size_t index;

        deque_iterator(const VectorPtr f = NULL, const VectorPtr b = NULL, size_t i = 0) : front(f), back(b), index(i) {}

        template <typename U>
        deque_iterator(const deque_iterator<U>& other)
            : front(other.front), back(other.back), index(other.index) {}

        template <typename U>
        deque_iterator(const deque_iterator<const U>& other)
            : front(const_cast<VectorPtr>(other.front)), back(const_cast<VectorPtr>(other.back)), index(other.index) {}

        reference operator*() {
            if (index < front->size()) {
                return (*front)[index];
            } else {
                return (*back)[index - front->size()];
            }
        }

        reference operator[](const long int n) const {
            if (index + n < front->size()) {
                return (*front)[index + n];
            } else if (index + n < front->size() + back->size()) {
                return (*back)[index + n - front->size()];
            } else
                throw std::out_of_range("deque");
        }

        pointer operator->() {
            return &**this;
        }

        deque_iterator& operator=(const deque_iterator& other) {
            front = other.front;
            back = other.back;
            index = other.index;
            return *this;
        }

        bool operator==(const deque_iterator& rhs) const {
            return front == rhs.front && back == rhs.back && index == rhs.index;
        }

        bool operator!=(const deque_iterator& rhs) const {
            return !(*this == rhs);
        }

        bool operator<(const deque_iterator& rhs) const {
            if (front < rhs.front) {
                return true;
            } else if (front == rhs.front) {
                if (back < rhs.back) {
                    return true;
                } else if (back == rhs.back) {
                    return index < rhs.index;
                }
            }
            return false;
        }

        bool operator>(const deque_iterator& rhs) const {
            return rhs < *this;
        }

        bool operator<=(const deque_iterator& rhs) const {
            return !(rhs < *this);
        }

        bool operator>=(const deque_iterator& rhs) const {
            return !(*this < rhs);
        }

        deque_iterator& operator++() {
            if (index < front->size() + back->size())
                index++;
            return *this;
        }

        deque_iterator operator++(int) {
            deque_iterator temp = *this;
            ++(*this);
            return temp;
        }

        deque_iterator& operator--() {
            if (index > 0)
                --index;
            return *this;
        }

        deque_iterator operator--(int) {
            deque_iterator temp = *this;
            --(*this);
            return temp;
        }

        deque_iterator& operator+=(int n) {
            for (int i = 0; i < n; ++i)
                ++(*this);
            return *this;
        }

        deque_iterator& operator+=(deque_iterator other) {
            for (int i = 0; i < other.index; ++i)
                ++(*this);
            return *this;
        }

        deque_iterator& operator-=(int n) {
            for (int i = 0; i < n; ++i)
                --(*this);
            return *this;
        }

        deque_iterator& operator-=(deque_iterator other) {
            if (other.index > index) {
                index = 0;
            } else {
                index -= other.index;
            }
            return *this;
        }

        deque_iterator operator+(int n) const {
            deque_iterator temp = *this;
            temp += n;
            return temp;
        }

        deque_iterator operator+(deque_iterator other) const {
            deque_iterator temp = *this;
            temp += other;
            return temp;
        }

        deque_iterator operator-(int n) const {
            deque_iterator temp = *this;
            temp -= n;
            return temp;
        }

        difference_type operator-(deque_iterator other) const {
            if (other.index < index) {
                return index - other.index;
            } else {
                return other.index - index;
            }
        }

        deque_iterator friend operator+(int n, const deque_iterator &r) {
            deque_iterator out(r);
            out += n;
            return out;
        }

        deque_iterator friend operator-(int n, const deque_iterator &r) {
            deque_iterator out(r);
            out -= n;
            return out;
        }
    };

    // Const deque_iterator
    template <typename T>
    class deque_iterator<const T> : public iterator<ft::random_access_iterator_tag, const T> {
    public:
        typedef typename ft::iterator<ft::random_access_iterator_tag, const T>::iterator_category iterator_category;
        typedef typename ft::iterator<ft::random_access_iterator_tag, const T>::value_type value_type;
        typedef typename ft::iterator<ft::random_access_iterator_tag, const T>::difference_type difference_type;
        typedef const T* pointer;
        typedef const T& reference;

    private:
        template <typename U>
        struct ConditionalVectorPtr {
            typedef const ft::vector<U>* type;
        };

        typedef typename ConditionalVectorPtr<T>::type VectorPtr;

    public:
        VectorPtr front;
        VectorPtr back;
        size_t index;

        deque_iterator(VectorPtr f = NULL, VectorPtr b = NULL, size_t i = 0) : front(f), back(b), index(i) {}

        template <typename U>
        deque_iterator(const deque_iterator<U>& other)
            : front(other.front), back(other.back), index(other.index) {}

        reference operator*() const {
            if (index < front->size()) {
                return (*front)[index];
            } else if (index < front->size() + back->size()) {
                return (*back)[index - front->size()];
            } else
                throw std::out_of_range("deque");

        }

        reference operator[](const long int n) const {
            if (index + n < front->size()) {
                return (*front)[index + n];
            } else if (index + n < front->size() + back->size()) {
                return (*back)[index + n - front->size()];
            } else
                throw std::out_of_range("deque");
        }


        pointer operator->() const {
            return &**this;
        }

        deque_iterator& operator=(const deque_iterator& other) {
            front = other.front;
            back = other.back;
            index = other.index;
            return *this;
        }

        bool operator==(const deque_iterator& rhs) const {
            return front == rhs.front && back == rhs.back && index == rhs.index;
        }

        bool operator!=(const deque_iterator& rhs) const {
            return !(*this == rhs);
        }

        bool operator<(const deque_iterator& rhs) const {
            if (front < rhs.front) {
                return true;
            } else if (front == rhs.front) {
                if (back < rhs.back) {
                    return true;
                } else if (back == rhs.back) {
                    return index < rhs.index;
                }
            }
            return false;
        }

        bool operator>(const deque_iterator& rhs) const {
            return rhs < *this;
        }

        bool operator<=(const deque_iterator& rhs) const {
            return !(rhs < *this);
        }

        bool operator>=(const deque_iterator& rhs) const {
            return !(*this < rhs);
        }

        deque_iterator& operator++() {
            if (index < front->size() + back->size())
                index++;
            return *this;
        }

        deque_iterator operator++(int) {
            deque_iterator temp = *this;
            ++(*this);
            return temp;
        }

        deque_iterator& operator--() {
            if (index > 0)
                --index;
            return *this;
        }

        deque_iterator operator--(int) {
            deque_iterator temp = *this;
            --(*this);
            return temp;
        }

        deque_iterator& operator+=(int n) {
            for (int i = 0; i < n; ++i)
                ++(*this);
            return *this;
        }

        deque_iterator& operator+=(deque_iterator other) {
            for (int i = 0; i < other.index; ++i)
                ++(*this);
            return *this;
        }

        deque_iterator& operator-=(int n) {
            for (int i = 0; i < n; ++i)
                --(*this);
            return *this;
        }

        deque_iterator& operator-=(deque_iterator other) {
            if (other.index > index) {
                index = 0;
            } else {
                index -= other.index;
            }
            return *this;
        }

        deque_iterator operator+(const long n) const {
            deque_iterator temp = *this;
            temp += n;
            return temp;
        }

        deque_iterator operator+(deque_iterator other) const {
            deque_iterator temp = *this;
            temp += other;
            return temp;
        }

        deque_iterator operator-(int n) const {
            deque_iterator temp = *this;
            temp -= n;
            return temp;
        }

        difference_type operator-(deque_iterator other) const {
            if (other.index < index) {
                return index - other.index;
            } else {
                return other.index - index;
            }
        }

        deque_iterator friend operator+(int n, const deque_iterator &r) {
            deque_iterator out(r);
            out += n;
            return out;
        }

        deque_iterator friend operator-(int n, const deque_iterator &r) {
            deque_iterator out(r);
            out = n;
            return out;
        }



    };
}

#endif
