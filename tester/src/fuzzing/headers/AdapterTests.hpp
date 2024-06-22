#pragma once
#include "Common.hpp"
#ifdef TEST_FT
# define ns ft
# include "stack.hpp"
# include "queue.hpp"
#else
# define ns std
# include <stack>
# include <queue>
#endif

template<typename Container>
void push(Container& s) {
    typename Container::value_type value = generate_value<typename Container::value_type>();
    std::cout << "s.push(" << value << ")" << std::endl;
    s.push(value);
}

template<typename Container>
void pop(Container& s) {
    if (!s.empty()) {
        s.pop();
        std::cout << "s.pop()" << std::endl;
    } else {
        std::cout << "Attempted to pop from an empty stack." << std::endl;
    }
}

template<typename Container>
void top(Container& s) {
    if (!s.empty()) {
        std::cout << "s.top() = " << s.top() << std::endl;
    } else {
        std::cout << "Attempted to access top from an empty stack." << std::endl;
    }
}

template<typename Container>
void empty(Container& s) {
    std::cout << "s.empty() = " << (s.empty() ? "true" : "false") << std::endl;
}

template<typename Container>
void size(Container& s) {
    std::cout << "s.size() = " << s.size() << std::endl;
}

template<typename Container>
void test_default_constructor(Container&) {
    Container stack_default;
    std::cout << "Created a default stack." << std::endl;
}

template<typename Container>
void test_copy_constructor(Container& s) {
    Container stack_copy(s);
    std::cout << "Created a copy of a stack." << std::endl;
}

template<typename Container>
void test_assignment_operator(Container& s) {
    Container stack_assigned;
    stack_assigned = s;
    std::cout << "Assigned a stack using the assignment operator." << std::endl;
}

template<typename Container>
void test_exceptions(Container& s) {
    try {
        s.pop();
    } catch (std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

template<typename Container>
class AdapterTester : public ContainerTester<Container> {
public:
    virtual void logContainerState() {
        Container tmp = this->container;
        std::cout << "Stack state (top to bottom): ";
        while (!tmp.empty()) {
            std::cout << tmp.top() << " ";
            tmp.pop();
        }
        std::cout << "\n";
    }
};
