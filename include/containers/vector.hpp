#ifndef VECTOR_H
#define VECTOR_H
#include "iterators.hpp"
#include "utils.hpp"
#include <memory>
#include <algorithm>
#include <iostream>
#include "./new/list.hpp"

namespace ft
{
	template < class T, typename Alloc = std::allocator<T> >
	class vector
	{

    public:
        typedef T                                           value_type;
        typedef Alloc                                       allocator_type;
        typedef ft::size_t                                 size_type;
        typedef ft::random_access_iterator<T>                   iterator;
        typedef ft::random_access_iterator<const T>             const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
        typedef T&          reference;
        typedef const T&   const_reference;
        typedef	T*          pointer;
        typedef const T*     const_pointer;

    private:
        pointer arr;
        size_type _size;
        Alloc alloc;
       	size_type _capacity;

    public:
        explicit vector(const Alloc& alloc = Alloc()):arr(NULL),_size(0), alloc(alloc), _capacity(0) {;}

		template<class InputIt>
		vector(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last,
			const allocator_type& alloc = Alloc())
			: arr(NULL), _size(0), alloc(alloc), _capacity(0)
		{
				ft::list<value_type> temp(first, last);


				_size = _capacity = temp.size();
				arr = this->alloc.allocate(_capacity);


				typename ft::list<value_type>::const_iterator it = temp.begin();
				for (pointer current = arr; it != temp.end(); ++it, ++current) {
					this->alloc.construct(current, *it);
				}

		}

        vector(size_type count, const T& value = T(), const allocator_type& alloc = Alloc())
        :arr(NULL),_size(count), alloc(alloc), _capacity(count) {
			arr = this->alloc.allocate(count);
            for (size_type i = 0; i < _size; i++) {
				this->alloc.construct(arr + i, value);
			}
        }

        vector( const vector& other )
        : _size(other._size), alloc(other.alloc), _capacity(other._capacity){
        	arr = this->alloc.allocate(_capacity);
            for (size_type i = 0; i < _size; i++)
				this->alloc.construct(arr + i, *(other.arr + i));
        }
        ~vector() {
            clear();
            if (_capacity)
                alloc.deallocate(arr, _capacity);
        }


        vector& operator=( const vector& other ) {
            clear();
            alloc.deallocate(arr, _capacity);
            alloc = other.alloc; _capacity = other._capacity;  _size = other._size;
            arr = alloc.allocate(_capacity);
            for (size_type i = 0; i < _size; i++)
				alloc.construct(arr + i, *(other.arr + i));
            return (*this);
        }

		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type tmp = 0) {
			tmp += 1;
			clear();
			int sz = ft::distance(first, last);
			if (sz > (int)_capacity)
				reserve(sz);
			while (first != last)
				alloc.construct(arr + _size++, *first++);
		}

		void assign (size_type n, const value_type &val) {clear(), resize(n, val);}

        allocator_type getallocator() const    {
            return alloc;
        }

        //element access
        reference operator[] (size_type n) {return arr[n];}
        const_reference operator[] (size_type n) const {return arr[n];}

		reference at(size_type n) {
			if (n >= _size)
				throw ft::out_of_range("vector");
			return arr[n];
		}
		const_reference at(size_type n) const {
			if (n >= _size)
				throw ft::out_of_range("vector");
			return arr[n];
		}
		reference front() {return arr[0];}
		const_reference front() const {return arr[0];}
		reference back() {return arr[_size-1];}
		const_reference back() const {return arr[_size-1];}
        pointer data() {return arr;}
        const_pointer data() const {return arr;}

        //iterators
		iterator            	begin() 		{return iterator(arr);}
		iterator            	end() 			{return iterator(arr + _size);}
		const_iterator      	begin() const 	{return const_iterator(arr);}
		const_iterator      	end() const 	{return const_iterator(arr + _size);}
		reverse_iterator        rbegin() 		{return reverse_iterator((arr + _size));}
		reverse_iterator        rend() 			{return reverse_iterator(arr);}
		const_reverse_iterator  rbegin() const 	{return const_reverse_iterator((arr + _size));}
		const_reverse_iterator  rend() const 	{return const_reverse_iterator(arr);}

        //_capacity
        bool empty() const			{return !_size;}
        size_type size() const 		{return _size;}
        size_type max_size() const	{return alloc.max_size();}
		size_t capacity() const 	{return _capacity;}

		void reserve(size_type n) {
			if (n > alloc.max_size()){
				throw ft::out_of_range("vector::reserve");}
			if (n > _capacity) {
				pointer new_arr = alloc.allocate(n);
				for (size_type i = 0; i < _size; i++) {
					alloc.construct(new_arr + i, *(arr + i));
					alloc.destroy(arr + i);

				}
				if (arr) {
					alloc.deallocate(arr, _capacity);
				}
				arr = new_arr;
				_capacity = n;
			}
		}


		

        //modifiers
        void clear() {
            for (size_type i = 0; i < _size; i++)
				alloc.destroy(arr + i);
            _size = 0;
        }

		void resize(size_type n, value_type val = value_type()) {
			if (n > _size) {
				if (n > _capacity) reserve(n);
				for (size_t i = _size; i < n; ++i) {
					alloc.construct(arr + i, val);
				}
			} else {
				for (size_t i = n; i < _size; ++i) {
					alloc.destroy(arr + i);
				}
			}
			_size = n;
		}



		iterator insert(iterator position, const value_type &val) {
			size_t gap = ft::distance(begin(), position);


			if (_size + 1 >= _capacity)
				this->reserve(ft::max(_capacity * 2, _size + 1));


			for (size_t i = _size; i > gap; --i) {
				alloc.construct(arr + i, *(arr + i - 1));
				alloc.destroy(arr + i - 1);
			}


			alloc.construct(arr + gap, val);
			_size++;

			return begin() + gap;
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type* = 0) {

			size_t index = ft::distance(begin(), position);

			for (InputIterator it = first; it != last; ++it) {

				if (_size == _capacity) {
					size_t new_capacity = _capacity == 0 ? 1 : _capacity * 2;
					reserve(new_capacity);
					position = begin() + index;
				}

				for (size_t i = _size; i > index; --i) {
					alloc.construct(arr + i, arr[i - 1]);
					alloc.destroy(arr + i - 1);
				}

				alloc.construct(arr + index, *it);
				++_size;
				++index;
			}
		}




	void insert(iterator pos, size_type n, const value_type& val) {
		size_t pos_index = ft::distance(begin(), pos);
		if (!n)
			return;
		if (_size + n > _capacity) {
			size_t new_capacity = ft::max(_capacity * 2, _size + n);
			pointer new_arr = alloc.allocate(new_capacity);

			for (size_t i = 0; i < pos_index; ++i) {
				alloc.construct(new_arr + i, *(arr + i));
				alloc.destroy(arr + i);
			}

			for (size_t i = 0; i < n; ++i)
				alloc.construct(new_arr + pos_index + i, val);

			for (size_t i = pos_index; i < _size; ++i) {
				alloc.construct(new_arr + i + n, *(arr + i));
				alloc.destroy(arr + i);
			}

			if (arr)
				alloc.deallocate(arr, _capacity);

			arr = new_arr;
			_capacity = new_capacity;
		}
		else {
			for (size_t i = _size; i > pos_index; --i) {
				alloc.construct(arr + i + n - 1, *(arr + i - 1));
				alloc.destroy(arr + i - 1);
			}

			for (size_t i = 0; i < n; ++i)
				alloc.construct(arr + pos_index + i, val);
		}

		_size += n;
	}



		iterator erase(iterator first, iterator last) {
			int gap = ft::distance(first, last);


			iterator to_move = last;
			iterator target = first;
			while (to_move != iterator(arr + _size)) {
				*target = *to_move;
				++target;
				++to_move;
			}


			iterator to_destroy = end() - gap;
			while (to_destroy != end()) {
				alloc.destroy(&(*to_destroy));
				++to_destroy;
			}


			_size -= gap;

			return first;
		}

		iterator erase(iterator position) {
			return this->erase(position, position + 1);
		}


		void push_back(const value_type& val) {
			if (_size == _capacity) {
				size_type new_capacity = _capacity ? _capacity * 2 : 1;
				reserve(new_capacity);
			}
			alloc.construct(arr + _size, val);
			_size++;
		}



        void pop_back() {
   			if (_size) {
				alloc.destroy(arr + _size - 1);
				_size--;
			}
        }

		void swap (vector& x) {
			ft::swap(arr, x.arr);
			ft::swap(alloc, x.alloc);
			ft::swap(_capacity, x._capacity);
			ft::swap(_size, x._size);
		}

        friend bool operator==( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
                if (lhs.size() != rhs.size())  return 0;
                for (size_t i = 0; i < lhs.size(); i++)
                    if (lhs[i] != rhs[i]) return 0;
                return 1;
        }
        friend bool operator!=( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
                        return !(lhs == rhs);
        }

        friend bool operator<( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
            return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }
        friend bool operator<=( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
            return (lhs == rhs || lhs < rhs);
        }
        friend bool operator>( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
            return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
        }
        friend bool operator>=( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
            return (lhs == rhs || lhs > rhs);
        }
    };

    template< class T, class Alloc >
    void swap(vector<T,Alloc>& lhs, vector<T,Alloc>& rhs) {
        lhs.swap(rhs);
    }


}


#endif