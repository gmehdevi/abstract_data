#ifndef UTILS_H
#define UTILS_H

#include <cstddef>
#include <string>
#include "iterators.hpp"

namespace ft
{
    //misc
    template <class T>
    void swap(T &a, T &b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    template <class T>
    T max (T a, T b) {
        return (a > b ? a : b);
    }

    typedef unsigned long size_t;
    //enable if
	template <class T, T v>
	struct integral_constant {
  		typedef T value_type;
  		typedef integral_constant<T,v> type;
  		static const value_type value = v;
  		operator value_type() {return v;}
	};

	typedef integral_constant<bool,false> false_type;
	typedef integral_constant<bool,true> true_type;

	template <typename T> struct is_integral : public false_type {};
	template <typename T> struct is_integral<const T> : public false_type {};
	template <> struct is_integral<bool> : public true_type {};
	template <> struct is_integral<char> : public true_type {};
	template <> struct is_integral<wchar_t> : public true_type {};
	template <> struct is_integral<signed char> : public true_type {};
	template <> struct is_integral<short> : public true_type {};
	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<long> : public true_type {};
	template <> struct is_integral<long long> : public true_type {};
	template <> struct is_integral<unsigned char> : public true_type {};
	template <> struct is_integral<unsigned short> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<unsigned long> : public true_type {};
	template <> struct is_integral<unsigned long long> : public true_type {};

    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };

    template <bool B, typename T, typename F>
    struct conditional {
        typedef T type;
    };

    template <typename T, typename F>
    struct conditional<false, T, F> {
        typedef F type;
    };

    template <typename T>
    struct is_void {
        enum { value = 0 };
    };

    template <>
    struct is_void<void> {
        enum { value = 1 };
    };


    //compare
    template< class InputIt1, class InputIt2, class Compare >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                    InputIt2 first2, InputIt2 last2,
                                    Compare comp )

    {
        while (first1 != last1 && first2 != last2)
        {
            if      (comp(*first1, *first2))  return true;
            else if (comp(*first2, *first1)) return false;
            ++first1; ++first2;
        }
        return (first1 == last1 && first2 != last2);
    }

    template< class InputIt1, class InputIt2 >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                    InputIt2 first2, InputIt2 last2)
    {
        while (first1 != last1 && first2 != last2)
        {
            if      (*first1 < *first2) return true;
            else if (*first2 < *first1) return false;
            ++first1; ++first2;
        }
        return (first1 == last1 && first2 != last2);
    }

    template< class InputIt1, class InputIt2 >
    bool equal( InputIt1 first1, InputIt1 last1,
                InputIt2 first2 );

    template< class InputIt1,
            class InputIt2,
            class BinaryPredicate >
    bool equal( InputIt1 first1,
                InputIt1 last1,
                InputIt2 first2,
                BinaryPredicate p);


    template <bool flag, class IsTrue, class IsFalse>
    struct choose;

    template <class IsTrue, class IsFalse>
    struct choose<true, IsTrue, IsFalse> {
    typedef IsTrue type;
    };

    template <class IsTrue, class IsFalse>
    struct choose<false, IsTrue, IsFalse> {
    typedef IsFalse type;
    };


	template<typename It>
	int distance(It from, It to) {
		int ret = 0;
		for (; from != to; from++, ret++);
		return ret;
	}
    
    // template <typename InputIt>
    // typename ft::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last)
    // {
    //     typename ft::iterator_traits<InputIt>::difference_type dist = 0;
    //     while (first != last)
    //     {
    //         ++dist;
    //         first++;
    //     }
    //     return dist;
    // }


    //this is pretty cool actually even if it's ugly
    template<bool b, typename F, typename T>
    struct isConst {};

    template<typename T, typename F>
    struct isConst<0, F, T> {
        typedef F type;
    };

    template<typename T, typename F>
    struct isConst<1, F, T> {
        typedef T type;
    };

	template<typename T = void>
	struct less {
		typedef bool result_type;
		typedef T first_argument_type;
		typedef T second_argument_type;

		bool operator()(const T &lhs, const T &rhs) const {
			return (lhs < rhs);
		}
	};

    template <typename T = void>
    struct greater {
        typedef bool result_type;
        typedef T first_argument_type;
        typedef T second_argument_type;

        bool operator()(const T &lhs, const T &rhs) const {
            return (lhs > rhs);
        }
    };

    template <class iterators>
    void reverse(iterators first, iterators last) {
        while ((first != last) && (first != --last)) {
            ft::swap(*first++, *last);
        }
    }

    template <typename T>
    struct hash {
        ft::size_t operator()(const T& val) const {
            ft::size_t hash_val = 0;
            const char* data = reinterpret_cast<const char*>(&val);
            for (ft::size_t i = 0; i < sizeof(T); ++i) {
                hash_val ^= (ft::size_t)data[i] << (i * 8);
            }
            return hash_val;
        }
    };

    template <typename T>
    struct equal_to {
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs == rhs;
        }
    };



    class exception {
    public:
        exception() {}

        exception(const exception&) {}

        exception& operator=(const exception&) {
            return *this;
        }

        virtual ~exception() {}

        virtual const char* what() const {
            return "Exception";
        }
    };



    class logic_error : public exception {
    public:
        explicit logic_error(const std::string& what_arg) : what_message(what_arg) {}

        explicit logic_error(const char* what_arg) : what_message(what_arg) {}

        logic_error(const logic_error& other) : exception(other),  what_message(other.what_message) {}

        logic_error& operator=(const logic_error& other) {
            if (this != &other) {
                exception::operator=(other);
                what_message = other.what_message;
            }
            return *this;
        }

        virtual ~logic_error() {}

        virtual const char* what() const {
            return what_message.c_str();
        }

    private:
        std::string what_message;
    };

    class  length_error : public logic_error {
    public:
        explicit length_error(const std::string& what_arg) : logic_error(what_arg) {}

        explicit length_error(const char* what_arg) : logic_error(what_arg) {}

        length_error(const length_error& other) : logic_error(other) {}

        length_error& operator=(const length_error& other) {
            if (this != &other) {
                logic_error::operator=(other);
            }
            return *this;
        }

        virtual ~length_error() {}
    };

    class out_of_range : public logic_error {
    public:
        explicit out_of_range(const std::string& what_arg) : logic_error(what_arg) {}

        explicit out_of_range(const char* what_arg) : logic_error(what_arg) {}

        out_of_range(const out_of_range& other) : logic_error(other) {}

        out_of_range& operator=(const out_of_range& other) {
            if (this != &other) {
                logic_error::operator=(other);
            }
            return *this;
        }

        virtual ~out_of_range() {}
    };

    class runtime_error : public exception {
    public:
        explicit runtime_error(const std::string& what_arg) : what_message(what_arg) {}

        explicit runtime_error(const char* what_arg) : what_message(what_arg) {}

        runtime_error(const runtime_error& other) : exception(other), what_message(other.what_message) {}

        runtime_error& operator=(const runtime_error& other) {
            if (this != &other) {
                exception::operator=(other);
                what_message = other.what_message;
            }
            return *this;
        }

        virtual ~runtime_error() {}

        virtual const char* what() const {
            return what_message.c_str();
        }

    private:
        std::string what_message;
    };


    //next and prev
    template <class BidirectionalIterator>
    BidirectionalIterator prev (BidirectionalIterator it,
                                typename ft::iterator_traits<BidirectionalIterator>::difference_type n = 1) {
        while (n > 0) {
            --it;
            --n;
        }
        return it;
    }

    template <class BidirectionalIterator>
    BidirectionalIterator next (BidirectionalIterator it,
                                typename ft::iterator_traits<BidirectionalIterator>::difference_type n = 1) {
        while (n > 0) {
            ++it;
            --n;
        }
        return it;
    }

    template <class InputIterator, class Distance>
    void advance (InputIterator& it, Distance n) {
        while (n > 0) {
            ++it;
            --n;
        }
    }

    template <typename T>
    T& move(T& arg)
    {
        return arg;
    }

    template <typename T>
    const T& move(const T& arg)
    {
        return arg;
    }

    template <class InputIt, class ForwardIt>
    ForwardIt uninitialized_move(InputIt first, InputIt last, ForwardIt d_first)
    {
        typedef typename iterator_traits<InputIt>::value_type ValueType;
        ForwardIt current = d_first;
        try
        {
            while (first != last)
            {
                new (static_cast<void*>(&*current)) ValueType(move(*first));
                ++first;
                ++current;
            }
            return current;
        }
        catch (...)
        {
            while (d_first != current)
            {
                d_first->~ValueType();
                ++d_first;
            }
            throw ft::runtime_error("uninitialized_copy failed");
        }
    }

    template <class InputIt, class ForwardIt>
    ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first)
    {
        typedef typename std::iterator_traits<InputIt>::value_type ValueType;
        ForwardIt current = d_first;
        try
        {
            while (first != last)
            {
                new (static_cast<void*>(&*current)) ValueType(*first);
                ++first;
                ++current;
            }
            return current;
        }
        catch (...)
        {
            while (d_first != current)
            {
                d_first->~ValueType();
                ++d_first;
            }
            throw ft::runtime_error("uninitialized_copy failed");
        }
    }

    // Base definition of numeric_limits
    template <class T>
    class numeric_limits {
            public:
        static T min() {
            return T();
        }

        static T max() {
            return T();
        }
    };

    // Specializations for numeric_limits
    template <>
    class numeric_limits<int> {
    public:
        static int min() {
            return (int)0x80000000;
        }

        static int max() {
            return 0x7FFFFFFF;
        }
    };

    template <>
    class numeric_limits<unsigned int> {
    public:
        static unsigned int min() {
            return 0;
        }

        static unsigned int max() {
            return 0xFFFFFFFF;
        }
    };

    template <>
    class numeric_limits<long> {
    public:
        static long min() {
            return (long)0x80000000;
        }

        static long max() {
            return 0x7FFFFFFF;
        }
    };

    template <>
    class numeric_limits<unsigned long> {
    public:
        static unsigned long min() {
            return 0;
        }

        static unsigned long max() {
            return 0xFFFFFFFF;
        }
    };

    template <>
    class numeric_limits<long long> {
    public:
        static long long min() {
            return (long long)0x8000000000000000;
        }

        static long long max() {
            return 0x7FFFFFFFFFFFFFFF;
        }
    };

    template <>
    class numeric_limits<unsigned long long> {
    public:
        static unsigned long long min() {
            return 0;
        }

        static unsigned long long max() {
            return 0xFFFFFFFFFFFFFFFF;
        }
    };


    template <typename T>
    std::string to_string(T val) {
        std::string ret;
        if (val == 0) {
            ret = "0";
        } else {
            bool is_negative = false;
            if (val < 0) {
                is_negative = true;
                val = -val;
            }
            while (val > 0) {
                ret = (char)('0' + (val % 10)) + ret;
                val /= 10;
            }
            if (is_negative) {
                ret = "-" + ret;
            }
        }
        return ret;
    }

}

#endif