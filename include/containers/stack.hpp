#ifndef STACK_H
#define STACK_H
#include "vector.hpp"

namespace ft
{
	template <typename T, typename Container = ft::vector<T> >
    class stack {

	protected:
		Container c;
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

    explicit stack( const Container& cont = Container()) : c(cont) {} 
    stack(const stack &other) :c(other.c) {}
    ~stack() {}
    
    stack &operator=(const stack &other) {
        c = other.c;
        return *this;
    }
    
    //Element access
   reference top() {
        return (c.back());
    }
    const_reference top() const{
        return (c.back());
    }
    
    //Capacity
    bool empty() const {
        return (c.empty());
    }

    size_type size() const {
        return (c.size());
    }
    
    //Modifiers
    void push(const value_type& value) {
        c.push_back(value);
    }
    void pop() {
        c.pop_back();
    }
    
    //Non-member functions
    friend bool operator==(const stack &rhs, const stack &lhs) {
       return (rhs.c  == lhs.c) ;}
    friend bool operator!=(const stack &rhs, const stack &lhs) {
       return (rhs.c  != lhs.c) ;}
    friend bool operator<(const stack &rhs, const stack &lhs) {
       return (rhs.c  < lhs.c) ;}
    friend bool operator>(const stack &rhs, const stack &lhs) {
       return (rhs.c  > lhs.c) ;}
    friend bool operator<=(const stack &rhs, const stack &lhs) {
       return (rhs.c <= lhs.c) ;}
    friend bool operator>=(const stack &rhs, const stack &lhs) {
       return (rhs.c  >= lhs.c) ;}
    };

}


#endif 