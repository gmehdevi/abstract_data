#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#define FNAME std::cout  << "~~~~~~~~~~~~" << __FUNCTION__ << "~~~~~~~~~~~~" << std::endl;
#ifdef TEST_FT
# define ns ft
# include "utility.hpp"
# include "exception.hpp"
#else
# define ns std
# include <utility>
# include <exception>
#endif

#define BASE_SIZE 20

template <typename T>
T generate_value();

template <>
int generate_value<int>() {
    return !(std::rand() % 3) ? (std::rand() % 10) : (std::rand());
}

template <>
std::string generate_value<std::string>() {
    static const char* choices[] = {"apple", "banana", "cherry", "date", "mango", "orange", "pear", "plum"};
    return choices[std::rand() % (sizeof(choices) / sizeof(choices[0]))];
}

template <typename K, typename V>
ns::pair<K, V> generate_pair() {
    return ns::make_pair(generate_value<K>(), generate_value<V>());
}

template <class C>
typename C::iterator get_random_it(C &c) {
    if (c.empty()) {
        return c.end();
    }
    int index = rand() % c.size();
    typename C::iterator it = c.begin();
    for (int i = 0; i < index; ++i) {
        ++it;
    }
    return it;
}

template <class Iterator>
Iterator get_random_it(Iterator begin, Iterator end) {
    if (begin == end) {
        return end;
    }
    int index = rand() % std::distance(begin, end);
    Iterator it = begin;
    for (int i = 0; i < index; ++i) {
        ++it;
    }
    return it;
}

template <class T>
std::vector<T> get_random_vector() {
    std::vector<T> v;
    int size = rand() % BASE_SIZE;
    for (int i = 0; i < size; ++i) {
        v.push_back(generate_value<T>());
    }
    return v;
}

template<typename A, typename B>
std::ostream &operator<<(std::ostream &s, const ns::pair<A, B>& p) {
    return s << "{" << p.first << ", " << p.second << "}";
}

template<class C>
void print_it(C &c, typename C::iterator it) {
    if (it == c.end())
        std::cout << "end iterator";
    else
        std::cout << "it -> [" << *it << "]";
}

template<class C>
void print_it(C &c, ns::pair<typename C::iterator, bool> ret) {
    std::cout << "ret = ";
    print_it(c, ret.first);
    std::cout << ", " << ret.second << std::endl;
}


template <class BidirectionalIterator>
BidirectionalIterator prev(BidirectionalIterator it, typename std::iterator_traits<BidirectionalIterator>::difference_type n = 1) {
    for (typename std::iterator_traits<BidirectionalIterator>::difference_type i = 0; i < n; ++i) {
        --it;
    }
    return it;
}

template<typename Container>
class ContainerTester {
public:
    Container container;
    std::vector<void (*)(Container&)> functions;

    virtual void logContainerState() {
        return;
    }

    void addFunction(void (*func)(Container&)) {
        functions.push_back(func);
    }

    void testOperations(int numOperations) {
        for (int i = 0; i < numOperations; ++i) {
            if (!functions.empty()) {
                int index = std::rand() % functions.size();
                functions[index](container);
                logContainerState();
            }
        }
    }

    virtual ~ContainerTester() {}  // Ensure virtual destructor for base class
};
