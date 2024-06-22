#ifndef LIST_ITERATORS_HPP
#define LIST_ITERATORS_HPP

#include "./../iterators.hpp"

namespace ft {
    template <typename T>
    struct ListNode {
        T data;
        ListNode* next;
        ListNode* prev;

        ListNode(const T& val = T(), ListNode* n = NULL, ListNode* p = NULL)
            : data(val), next(n), prev(p) {}

        ListNode(const ListNode& cpy)
            : data(cpy.data), next(cpy.next), prev(cpy.prev) {}
    };

    template <typename T>
    class list_iterator : public iterator<ft::bidirectional_iterator_tag, T> {
        typedef ListNode<T> Node;

    public:
        Node* current;

        list_iterator(Node* ptr = NULL) : current(ptr) {}

        template <typename U>
        list_iterator(const list_iterator<U>& other)
            : current(other.current) {}

        template <typename U>
        list_iterator(const list_iterator<const U>& other)
            : current(other.current) {}

        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type value_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type difference_type;
        typedef T* pointer;
        typedef T& reference;

        reference operator*() {
            return current->data;
        }

        reference operator*() const {
            return current->data;
        }

        pointer operator->() {
            return &current->data;
        }

        // const pointer operator->() const {
        //     return &current->data;
        // }

        list_iterator& operator++() {
            current = current->next;
            return *this;
        }

        list_iterator operator++(int) {
            list_iterator temp = *this;
            ++(*this);
            return temp;
        }

        list_iterator& operator--() {
            current = current->prev;
            return *this;
        }

        list_iterator operator--(int) {
            list_iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const list_iterator& rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const list_iterator& rhs) const {
            return current != rhs.current;
        }
    };

    template <typename T>
    class list_iterator<const T> : public iterator<ft::bidirectional_iterator_tag, const T> {
        typedef ListNode<T> Node;

    public:
        Node* current;

        list_iterator(Node* ptr = NULL) : current(ptr) {}

        template <typename U>
        list_iterator(const list_iterator<U>& other)
            : current(other.current) {}

        typedef typename ft::iterator<ft::bidirectional_iterator_tag, const T>::iterator_category iterator_category;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, const T>::value_type value_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, const T>::difference_type difference_type;
        typedef const T* pointer;
        typedef const T& reference;

        reference operator*() const {
            return current->data;
        }

        pointer operator->() const {
            return &current->data;
        }

        list_iterator& operator++() {
            current = current->next;
            return *this;
        }

        list_iterator operator++(int) {
            list_iterator temp = *this;
            ++(*this);
            return temp;
        }

        list_iterator& operator--() {
            current = current->prev;
            return *this;
        }

        list_iterator operator--(int) {
            list_iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const list_iterator& rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const list_iterator& rhs) const {
            return current != rhs.current;
        }
    };
}
#endif
