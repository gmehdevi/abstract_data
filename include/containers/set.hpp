#ifndef SET_H
#define SET_H
#include "utils.hpp"
#include "pair.hpp"
#include "RBTree.hpp"
#include "tree_iterators.hpp"
#include "iterators.hpp"
#include <memory>

namespace ft
{
    template
    <
    class Key,
    class Compare = ft::less<Key>,
    class Allocator = std::allocator<Key>
    >
    class set {
    public:
        typedef Key key_type;
        typedef Key value_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type ;
        typedef Compare key_compare;
        typedef Compare value_compare;
        typedef Allocator allocator_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef bidirectional_iterator<value_type, Compare, allocator_type, RBNode<value_type> >        iterator;
        typedef bidirectional_iterator<const value_type, Compare, allocator_type, RBNode<value_type> >  const_iterator;
        typedef ft::reverse_iterator<iterator>                                                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                                                    const_reverse_iterator;

    private:
        typedef RBTree<value_type, value_compare, Allocator>  Tree;
        typedef RBNode<value_type>                           *NodePtr;
        Tree                             tree;
        allocator_type                   alloc;
        key_compare                      k_comp;
        value_compare                    v_comp;

    public:

		explicit set(const key_compare &comp = key_compare(),
              const allocator_type &alloc = allocator_type())
		:  tree(Tree(value_compare(comp))),alloc(alloc),k_comp(comp),v_comp(comp){}

		template <class InputIterator>
  		set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		:  tree(Tree(value_compare(comp))),alloc(alloc),k_comp(comp),v_comp(comp) {
			insert(first, last);
        }

		set(const set &cpy)
		:  tree(Tree(value_compare(cpy.k_comp))),alloc(cpy.alloc),k_comp(cpy.k_comp),v_comp(cpy.v_comp) {
			this->insert(cpy.begin(), cpy.end());
		}

		set& operator=(const set& cpy) {
			k_comp = cpy.k_comp;
			v_comp = cpy.v_comp;
			this->clear();
			this->insert(cpy.begin(), cpy.end());
			return *this;
		}

        ~set()
        {}

        allocator_type get_allocator(void)  const {return allocator_type();}

        //Iterators
        iterator begin() {
            return (iterator(tree.minimum(tree.root),tree._end));
        }
        const_iterator begin() const {
            return (const_iterator(tree.minimum(tree.root),tree._end));
        }
        iterator end() {
            tree._end ->parent = tree.maximum(tree.root);
            return (iterator(tree._end, tree._end));
        }
        const_iterator end() const {
            tree._end->parent  = tree.maximum(tree.root);
            return (const_iterator(tree._end,tree._end));
        }
		reverse_iterator rbegin() {return reverse_iterator(end());}
		const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
		reverse_iterator rend() {return reverse_iterator(begin());}
		const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

        //Capacity
        bool empty() const{
            return (!tree.size());
        }

        size_type size()  const{
            return tree.size();
        }

        size_type max_size() const {
            return (alloc.max_size() - 1)/10;
        }
        void clear() {tree.clear();}

        pair<iterator, bool> insert(const value_type& val ) {
            NodePtr tmp = tree.search(val);
            if(!tmp || tmp != tree._end)
                return ft::make_pair(iterator(tmp, tree._end), false);
            tmp = tree.insert(val);
            return ft::make_pair(iterator(tmp, tree._end), true);
        }

        iterator insert( iterator pos, const value_type& value ) {
            (void)pos;
            tree.insert(value);
            return iterator(tree.search(value), tree._end);
        }

        template< class InputIt>
        void insert( InputIt first, InputIt last ) {
            while (first != last) {
                insert(*first);
                first++;
            }

        }

        void erase( iterator pos ) {
            tree.erase(*pos);
        }
        void erase( iterator first, iterator last ) {
            while (first != last) tree.erase(*first++);
        }

        size_type erase(const Key& key )  {
            return tree.erase(key);
        }

        void swap(set& other) {
            if (this == &other) return;
            ft::swap(tree.root,  other.tree.root);
            ft::swap(tree._count, other.tree._count);
            ft::swap(tree._end, other.tree._end);
        }

        //Lookup
        size_type count( const Key& key ) const {return (tree.search(key) ?  1 : 0);}

        iterator find( const Key& key ) {return iterator(tree.search(key));}

        const_iterator find( const Key& key ) const {return const_iterator(tree.search(key));}


        iterator lower_bound( const Key& key ) {
            return (iterator(tree.lower_bound(key)));
        }

        const_iterator lower_bound( const Key& key ) const {
            return (const_iterator(tree.lower_bound(key)));
        }

        iterator upper_bound( const Key& key ) {
             return (iterator(tree.upper_bound(key)));
        }

        const_iterator upper_bound( const Key& key ) const {
            return (const_iterator(tree.upper_bound(key)));
        }

        pair<iterator,iterator> equal_range( const Key& key ) {
            return (ft::make_pair(lower_bound(key),upper_bound(key)));
        }

        pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
            return (ft::make_pair(lower_bound(key),upper_bound(key)));
        }
        //Observers
        key_compare key_comp() const {return key_compare();}

        value_compare value_comp() const {return value_compare();}

        //Non-member functions
        friend void swap(set& lhs, set& rhs ) {lhs.swap(rhs);}

        friend bool operator==( const set& lhs, const set& rhs ) {
            iterator l(lhs.tree.root);
            iterator r(rhs.tree.root);
            while (l != lhs.end() && r != rhs.end()) {
                if (l != r) return (0);
                l++;r++;
            }
            return (lhs.end() == rhs.end() ? 1 : 0);
        }

        friend bool operator!=( const set& lhs, const set& rhs ) {
            return !(lhs == rhs);
        }
        friend bool operator<( const set& lhs,const set& rhs ) {
            return ft::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(), rhs.end());
        }
        friend bool operator<=( const set& lhs, const set& rhs ) {
            return lhs == rhs || lhs < rhs;
        }
        friend bool operator>( const set& lhs,const set& rhs ) {
            return ft::lexicographical_compare(rhs.begin(),rhs.end(),lhs.begin(), lhs.end());
        }
        friend bool operator>=( const set& lhs, const set& rhs ) {
            return lhs == rhs || lhs > rhs;
        }
    };
}


#endif