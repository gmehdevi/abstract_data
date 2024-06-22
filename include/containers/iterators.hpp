#ifndef ITERATORS_H
#define ITERATORS_H
#include <cstddef>
#include <iterator>
namespace ft
{
    struct input_iterator_tag : std::input_iterator_tag {};
    struct output_iterator_tag : std::output_iterator_tag {};
    struct forward_iterator_tag : std::forward_iterator_tag {};
    struct bidirectional_iterator_tag : std::bidirectional_iterator_tag {};
    struct random_access_iterator_tag : std::random_access_iterator_tag {};

    template <class Iterator>
    struct iterator_traits {
      typedef typename Iterator::difference_type		difference_type;
      typedef typename Iterator::value_type			    value_type;
      typedef typename Iterator::pointer				    pointer;
      typedef typename Iterator::reference			    reference;
      typedef typename Iterator::iterator_category	iterator_category;
    };

    template <class T>
    struct  iterator_traits<T*> {
		typedef ptrdiff_t	      difference_type;
		typedef T			          value_type;
		typedef T*			        pointer;
		typedef T&			        reference;
		typedef typename        ft::random_access_iterator_tag	iterator_category;
    };

    template <class T>
    struct  iterator_traits<const T*> {
		typedef ptrdiff_t	    difference_type;
		typedef T			        value_type;
		typedef T*			      pointer;
		typedef T&			      reference;
		typedef typename      ft::random_access_iterator_tag	iterator_category;
    };

    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };

    template <typename T>
    class random_access_iterator : public iterator<ft::random_access_iterator_tag, T>
    {

    public:
      typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category     iterator_category;
      typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
      typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type       difference_type;
      typedef T*                                                                              pointer;
      typedef T&                                                                              reference;

    private :
      pointer _ptr;

    public:
      random_access_iterator(pointer ptr = NULL) {_ptr = ptr;}
      random_access_iterator(const random_access_iterator &cpy) {_ptr = cpy._ptr;}
      random_access_iterator &operator=(const random_access_iterator &cpy) {
          _ptr = cpy._ptr;
          return *this;
      }

      reference operator [](difference_type n) {return (*(_ptr + n));}
      reference operator  *() {return *_ptr;}
      pointer   operator ->()  {return _ptr;}

      random_access_iterator  &operator ++() {
        ++_ptr;
        return (*this);
      }

      random_access_iterator &operator--() {
        --_ptr;
        return (*this);
      }

      random_access_iterator operator ++(int) {
        random_access_iterator out(*this);
        ++(*this);
        return out;
      }

      random_access_iterator operator --(int) {
        random_access_iterator out(*this);
        --(*this);
        return out;
      }
      random_access_iterator operator +=(const int& n) {
        _ptr += n;
        return *this;
      }

      random_access_iterator &operator +=(long n) {
        _ptr += n;
        return *this;
      }

      random_access_iterator operator -=(const int& n) {
        _ptr -= n;
        return *this;
      }

      random_access_iterator &operator -=(long n) {
        _ptr -= n;
        return *this;
      }

      random_access_iterator operator +(const int &n) {
          random_access_iterator out(*this);
          out += n;
          return out;
      }

      difference_type operator+(const random_access_iterator &r) {
          return _ptr + r._ptr;
      }

      friend random_access_iterator operator +(const int &n, random_access_iterator &r) {
          random_access_iterator out(r);
          out += n;
          return out;
      }
      random_access_iterator operator -(const int &n) {
          random_access_iterator out(*this);
          out -= n;
          return out;
      }

      friend random_access_iterator operator -(const int &n, random_access_iterator &r) {
          random_access_iterator out(r);
          out -= n;
          return out;
      }
      difference_type operator-(const random_access_iterator &op) {
          return _ptr - op._ptr;
      }

      friend difference_type operator-(const random_access_iterator &a, const random_access_iterator &b) {
        return a._ptr - b._ptr;
      }

      friend bool operator==(const random_access_iterator &a, const random_access_iterator &b) {
          return a._ptr == b._ptr;
      }

      friend bool operator!=(const random_access_iterator &a, const random_access_iterator &b) {
          return a._ptr != b._ptr;
      }

      friend bool operator<(const random_access_iterator &a, const random_access_iterator &b) {
          return a._ptr < b._ptr;
      }

      friend bool operator<=(const random_access_iterator &a, const random_access_iterator &b) {
          return a._ptr <= b._ptr;
      }

      friend bool operator>(const random_access_iterator &a, const random_access_iterator &b) {
          return a._ptr > b._ptr;
      }

      friend bool operator>=(const random_access_iterator &a, const random_access_iterator &b) {
          return a._ptr >= b._ptr;
      }
	/*------------------Conversion------------------*/

      operator random_access_iterator<const T>() const {
        random_access_iterator<const T> out(_ptr);
        return out;
      }

	/*------------------Arithmetic------------------*/

      friend random_access_iterator operator+(const int &n, const random_access_iterator &op) {
          random_access_iterator out(op);
          out += n;
          return out;
      }


    };


  template <typename Iter>
    class reverse_iterator {
    public:
      typedef Iter iterator_type;
      typedef typename Iter::value_type value_type;
      typedef typename Iter::difference_type difference_type;
      typedef typename Iter::pointer pointer;
      typedef typename Iter::reference reference;
      typedef typename Iter::iterator_category iterator_category;

    private:
      iterator_type it;

    public:
      reverse_iterator() : it() {}

      reverse_iterator(const Iter &it) : it(it) {}

      template<typename U>
      reverse_iterator(const reverse_iterator<U> &cpy) : it(cpy.base()) {}

      reverse_iterator &operator=(const reverse_iterator &cpy) {
        it = cpy.it;
        return *this;
      }

      ~reverse_iterator() {}

      iterator_type base() const {
        return it;
      }


      const reference operator*() const  {return *(--iterator_type(it));}

      pointer operator->() const {return &(this->operator*());}

      reference operator[](difference_type n) {return base()[-n-1];}


      reverse_iterator &operator++() {--it; return *this;}

      reverse_iterator operator++(int) {
              reverse_iterator out(*this);
              ++(*this);
              return out;
      }

      reverse_iterator &operator--() {++it; return *this;}

      reverse_iterator operator--(int) {
              reverse_iterator out(*this);
              --(*this);
              return out;
      }

      reverse_iterator &operator +=(const int& n) {
          it -= n;
          return *this;
      }
      reverse_iterator &operator -=(const int& n) {
          it += n;
          return *this;
      }

      difference_type operator-(const reverse_iterator &op) {
        return op.base() - base();
      }

      difference_type operator+(const reverse_iterator &op) {
        return base() + op.base();
      }

      reverse_iterator operator+(const int & n) {
      return reverse_iterator(base() - n);
          }

      template<typename It>
          friend reverse_iterator operator+(const int &n, const reverse_iterator<It> &op) {
        return reverse_iterator(op.base() - n);
          }

        reverse_iterator operator-(const int &n) {
          return reverse_iterator(base() + n);
        }

      template<typename It>
      friend reverse_iterator operator-(const int &n, const reverse_iterator<It> &op) {
       return reverse_iterator(op.base() + n);
      }


    };

      template <typename It1, typename It2> bool operator==(const reverse_iterator<It1>& lhs,
          const reverse_iterator<It2>& rhs) {return (lhs.base() == rhs.base());}

      template <typename It1, typename It2> bool operator!=(const reverse_iterator<It1>& lhs,
          const reverse_iterator<It2>& rhs) {return (lhs.base() != rhs.base());}

      template <typename It1, typename It2> bool operator<(const reverse_iterator<It1>& lhs,
          const reverse_iterator<It2>& rhs) {return (lhs.base() > rhs.base());}

      template <typename It1, typename It2> bool operator<=(const reverse_iterator<It1>& lhs,
          const reverse_iterator<It2>& rhs) {return (lhs.base() >= rhs.base());}

      template <typename It1, typename It2> bool operator>(const reverse_iterator<It1>& lhs,
          const reverse_iterator<It2>& rhs) {return (lhs.base() < rhs.base());}

      template <typename It1, typename It2> bool operator>=(const reverse_iterator<It1>& lhs,
          const reverse_iterator<It2>& rhs) {return (lhs.base() <= rhs.base());}

      // template<class InputIt>
      // typename iterator_traits<InputIt>::difference_type distance( InputIt first, InputIt last ) {
      //     ptrdiff_t dist = 0;
      //     while (first++ != last) dist++;
      //     return dist;
      // }

}







#endif