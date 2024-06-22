#ifndef MULTI_TREE_ITERATORS_H
#define MULTI_TREE_ITERATORS_H

#include "RBTree.hpp"
#include "utils.hpp"
#include "iterators.hpp"
namespace ft {

    template<typename T, typename Compare, typename Alloc, typename Node>
    class bidirectional_iterator : public iterator<ft::bidirectional_iterator_tag, T>
    {
    public:
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
        typedef Alloc                                                                               allocator_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer               pointer;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference             reference;

    private:
        typedef Node* NodePtr;

    public:
        NodePtr _ptr;
        NodePtr _end;
        Compare _comp;

        bidirectional_iterator(const NodePtr ptr = NULL, const NodePtr tend = NULL)
            : _ptr(ptr), _end(tend), _comp(Compare()) {}

        bidirectional_iterator(const bidirectional_iterator& cpy)
            : _ptr(cpy._ptr), _end(cpy._end), _comp(cpy._comp) {}

        bidirectional_iterator& operator=(const bidirectional_iterator& cpy) {
            _ptr = cpy._ptr;
            _end = cpy._end;
            return *this;
        }

        ~bidirectional_iterator() {}

        reference operator*() const { return _ptr->data; }
        pointer operator->() const { return &(**this); }

        bidirectional_iterator& operator++() {
            if (_ptr) {
                // If there's a right subtree, go to the leftmost node of that subtree
                if (_ptr->right && _ptr->right != _end) {
                    _ptr = _ptr->right;
                    while (_ptr->left && _ptr->left != _end)
                        _ptr = _ptr->left;
                } else {
                    // Otherwise, move up the tree until we find the parent
                    // for which we're in the left subtree
                    NodePtr parent = _ptr->parent;
                    while (parent != NULL && _ptr == parent->right) {
                        _ptr = parent;
                        parent = parent->parent;
                    }
                    _ptr = parent;
                }
            }

            // If _ptr is NULL, we've reached the end
            if (!_ptr) _ptr = _end;
            return *this;
        }


        bidirectional_iterator& operator--() {
            if (_ptr) {
                // If the iterator is at the end, move to the maximum node
                if (_ptr == _end) {
                    _ptr = _end->parent;
                    while (_ptr && _ptr->right && _ptr->right != _end)
                        _ptr = _ptr->right;
                } else {
                    // If there's a left subtree, go to the rightmost node of that subtree
                    if (_ptr->left && _ptr->left != _end) {
                        _ptr = _ptr->left;
                        while (_ptr->right && _ptr->right != _end)
                            _ptr = _ptr->right;
                    } else {
                        // Otherwise, move up the tree until we find the parent
                        // for which we're in the right subtree
                        NodePtr parent = _ptr->parent;
                        while (parent != NULL && _ptr == parent->left) {
                            _ptr = parent;
                            parent = parent->parent;
                        }
                        _ptr = parent;
                    }
                }
            }

            // If _ptr is NULL, we've reached the end
            if (!_ptr) _ptr = _end;
            return *this;
        }

        bidirectional_iterator operator++(int) {
            bidirectional_iterator out(*this);
            ++(*this);
            return out;
        }



        bidirectional_iterator operator--(int) {
            bidirectional_iterator out(*this);
            --(*this);
            return out;
        }

        friend bool operator==(const bidirectional_iterator& x, const bidirectional_iterator& y) { return (x._ptr == y._ptr); }
        friend bool operator!=(const bidirectional_iterator& x, const bidirectional_iterator& y) { return (x._ptr != y._ptr); }

        operator bidirectional_iterator<const T, Compare, Alloc, Node>() const {
            bidirectional_iterator<const T, Compare, Alloc, Node> out(_ptr, _end);
            return out;
        }
    };

} // namespace ft
#endif