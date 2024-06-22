#ifndef MULTIMAP_H
#define MULTIMAP_H
#include "./../utils.hpp"
#include "./../pair.hpp"
#include "./../RBTree.hpp"
#include "./../iterators.hpp"
#include "./../vector.hpp"
namespace ft
{
template
    <
    typename Key,
    typename T,
    typename Compare = less<Key>,
    typename Allocator = std::allocator<ft::pair<const Key, T> >
    > 
    class multimap {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type ;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer	;

        class value_compare {
			friend class multimap;
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type &x, const value_type &y) const {return comp(x.first, y.first);}
            value_compare(const key_compare &c = Compare()) : comp(c) {}
			value_compare(const value_compare &c) : comp(c.comp) {}
		protected:
			Compare comp;
		};
    public:
        typedef RBTree<value_type, value_compare, Allocator>  Tree;
		typedef typename Tree::iterator iterator;
		typedef typename Tree::const_iterator const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;	
    
        Tree                             tree;
    private:
        allocator_type                   alloc;
        key_compare                      k_comp;
        value_compare                    v_comp;
    
    public:

		explicit multimap(const key_compare comp = key_compare(), const allocator_type &alloc = allocator_type())
		:  tree(Tree(value_compare(comp), true)),alloc(alloc),k_comp(comp),v_comp(comp) {}		

		template <class InputIterator>
  		multimap (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		:  tree(Tree(value_compare(comp), true)),alloc(alloc),k_comp(comp),v_comp(comp) {		
			insert(first, last);
        }

		multimap(const multimap &cpy)
		:  tree(value_compare(cpy.k_comp), true),alloc(cpy.alloc),k_comp(cpy.k_comp),v_comp(cpy.v_comp) {		
			this->insert(cpy.begin(), cpy.end());
		}

		multimap& operator=(const multimap& cpy) { 
			k_comp = cpy.k_comp;
			v_comp = cpy.v_comp;
			this->clear();
			this->insert(cpy.begin(), cpy.end());
			return *this;
		}
        
        ~multimap()
        {}

        allocator_type &get_allocator(void) {return alloc;}
       
        //Element access
        T &at(Key &k) {
            RBNode<value_type> *tmp = tree.search(k);
            if (!tmp) 
                throw ft::out_of_range("multimap");
            return tmp->val;
        }

        T &operator[](const Key &k){
            return (*((insert(ft::make_pair(k,mapped_type()))).first)).second ;
        }
        
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
        bool empty() const {
            return !tree.size();
        }

        size_type size() const {
            return tree.size();
        }

        size_type max_size() const{
            return alloc.max_size();
        }

        //Modifiers
        void clear() {tree.clear();}
        
        iterator insert(const value_type& val ) {
            return iterator(tree.insert(val), tree._end);
        }
        
        iterator insert(iterator pos, const value_type& value ) {
            (void)pos;
            return iterator(tree.insert(value), tree._end);
        }
        
        template< class InputIt>
        void insert( InputIt first, InputIt last ) {
            while (first != last) 
                tree.insert(*first++);
        }

        void erase(iterator pos) {
            tree.erase(pos);        
        }

        void erase(iterator first, iterator last) {
            ft::vector<value_type> tmp;
            while (first != last) {
                tmp.push_back(*first);
                first++;
            }
            for (size_type i = 0; i < tmp.size(); i++) {
                tree.erase(tmp[i]);
            }
        }

        size_type erase(const Key& key )  {
            size_type ret = tree.count(ft::make_pair(key, mapped_type()));
            for (size_type i = 0; i < ret; i++) {
                tree.erase(ft::make_pair(key, mapped_type()));
            }
            return ret;
        }

        void swap(multimap& other ) {
			ft::swap(tree.root,  other.tree.root);
            ft::swap(tree._count, other.tree._count);
            ft::swap(tree._end, other.tree._end);
        }
        
		friend void swap (multimap &x, multimap &y) {
			x.swap(y);
		}

        size_type count( const Key& key ) const {return (tree.count(ft::make_pair(key,mapped_type())));}

        iterator find( const Key& key ) {return iterator(tree.search(ft::make_pair(key, mapped_type())),tree._end);}
        
        const_iterator find( const Key& key ) const {return const_iterator(tree.search(ft::make_pair(key, mapped_type())),tree._end);}

        iterator lower_bound( const Key& key ) {
            return (iterator(tree.lower_bound(ft::make_pair(key, mapped_type())),tree._end));
        }

        const_iterator lower_bound( const Key& key ) const {
            return (const_iterator(tree.lower_bound(ft::make_pair(key, mapped_type())),tree._end));
        }
        
        iterator upper_bound( const Key& key ) {
            return (iterator(tree.upper_bound(ft::make_pair(key, mapped_type())),tree._end));
        }
        const_iterator upper_bound( const Key& key ) const {
            return (const_iterator(tree.upper_bound(ft::make_pair(key, mapped_type())),tree._end));
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
        friend bool operator==( const multimap& lhs, const multimap& rhs ) {
            iterator l(lhs.tree.root);
            iterator r(rhs.tree.root);
            while (l != lhs.end() && r != rhs.end()) {
                if (l != r) return (0);
                l++;r++;
            }
            return l == r ? 1 : 0; 
        }

        friend bool operator!=( const multimap& lhs, const multimap& rhs ) {
            return !(lhs == rhs);
        }
        friend bool operator<( const multimap& lhs,const multimap& rhs ) {
            return ft::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(), rhs.end());
        }
        friend bool operator<=( const multimap& lhs, const multimap& rhs ) {
            return lhs == rhs || lhs < rhs;
        }
        friend bool operator>( const multimap& lhs,const multimap& rhs ) {
            return ft::lexicographical_compare(rhs.begin(),rhs.end(),lhs.begin(), lhs.end());
        }
        friend bool operator>=( const multimap& lhs, const multimap& rhs ) {
            return lhs == rhs || lhs > rhs;
        }
    };
}


#endif 