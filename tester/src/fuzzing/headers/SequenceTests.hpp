#include "Common.hpp"

#ifdef TEST_FT
# define ns ft
# include "vector.hpp"
# include "deque.hpp"
# include "list.hpp"
#else
# define ns std
# include <vector>
# include <deque>
# include <list>
#endif


template<typename Container>
void print_container(const Container& v) {
    FNAME
    for (typename Container::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

}

template<typename Container>
void push_back(Container& a) {
    FNAME
    typename Container::value_type value = generate_value<typename Container::value_type>();
    std::cout << "a.push_back(" << value << ")" << std::endl;
    a.push_back(value);
}

template<typename Container>
void pop_back(Container& a) {
    FNAME
    if (!a.empty()) {
        std::cout << "a.pop_back()" << std::endl;
        a.pop_back();
    }
}

template<typename Container>
void insert(Container& a) {
    FNAME
    if (a.empty()) return;
    int index = rand() % a.size();
    typename Container::value_type value = generate_value<typename Container::value_type>();
    typename Container::iterator pos =get_random_it(a);
    a.insert(pos, value);
    std::cout << "a.insert(" << index << ", " << value << ")" << std::endl;
}

template<typename Container>
void erase(Container& a) {
    FNAME
    if (!a.empty()) {

        typename Container::iterator pos =get_random_it(a);
        a.erase(pos);
    }
}

template<typename Container>
void clear(Container& a) {
    FNAME
    a.clear();
    std::cout << "a.clear()" << std::endl;
}

template<typename Container>
void resize(Container& a) {
    FNAME
    int newSize = rand() % BASE_SIZE;
    a.resize(newSize);
    std::cout << "a.resize(" << newSize << ")" << std::endl;
    std::cout << "size after (" << a.size() << ")" << std::endl;
}

template<typename Container>
void check_front(Container& a) {
    FNAME
    if (!a.empty()) {
        std::cout << "a.front() = " << a.front() << std::endl;
    }
}

template<typename Container>
void check_back(Container& a) {
    FNAME
    if (!a.empty()) {
        std::cout << "a.back() = " << a.back() << std::endl;
    }
}

template<typename Container>
void check_empty(Container& a) {
    FNAME
    std::cout << "a.empty() = " << (a.empty() ? "true" : "false") << std::endl;
}

template<typename Container>
void test_range_insert(Container& a) {
    FNAME
    if (a.size() < BASE_SIZE / 2) return;  // Ensure there's enough space based on BASE_SIZE

    std::vector<typename Container::value_type> new_values = get_random_vector<typename Container::value_type>(); // Use get_random_vector to generate new values
    if (new_values.size() == 0) return; // Ensure there are new values to insert

    typename Container::iterator it = a.begin();
    if (a.size() > BASE_SIZE / 4) {
        std::advance(it, BASE_SIZE / 4);
    }

    a.insert(it, new_values.begin(), new_values.end());
    std::cout << "Inserted range of values: ";
    print_container(new_values);
}

template<typename Container>
void check_capacity(Container& a) {
    FNAME
    std::cout << "a.capacity() = " << a.capacity() << std::endl;
}

template<typename Container>
void test_reserve(Container& a) {
    FNAME
    size_t new_capacity = a.size() + BASE_SIZE / 2; // Reserve more space

    std::cout << "old capacity: " << a.capacity() << std::endl;
    a.reserve(new_capacity);
    std::cout << "a.reserve(" << new_capacity << "), new capacity = " << a.capacity() << std::endl;
}

template<typename Container>
void test_swap(Container& a) { 
    FNAME
    Container other(a.size(), generate_value<typename Container::value_type>());
    a.swap(other);
    std::cout << "a.swap(other), new a size = " << a.size() << ", other size = " << other.size() << std::endl;
}

template<typename Container>
void check_at(Container& a) {
    FNAME
    if (!a.empty()) {
        try {
            std::cout << "a.at(0) = " << a.at(0) << std::endl;
        } catch (const std::out_of_range& e) {
            std::cout << "Out of range error: " << std::endl;
        }
    }
}

template<typename Container>
void test_constructors(Container& a) {
    FNAME
    Container copy_constructor(a); // Copy constructor
    Container range_constructor(a.begin(), a.end()); // Range constructor
    std::cout << "Copy constructed vector: ";
    print_container(copy_constructor);
    std::cout << "Range constructed vector: ";
    print_container(range_constructor);
}

template<typename Container>
void test_copy_assignment(Container& a) {
    FNAME
    std::vector<typename Container::value_type> tmp = get_random_vector<typename Container::value_type>();
    Container copy_assignment(tmp.begin(), tmp.end());
    a = copy_assignment;
    std::cout << "Performed copy assignment." << std::endl;
}

template<typename Container>
void modify_back(Container& a) {
    FNAME
    if (!a.empty()) {
        a.back() = generate_value<typename Container::value_type>();  // Modify the last element
        std::cout << "Modified back element: " << a.back() << std::endl;
    }
}

template<typename Container>
void test_iterators(Container& a) {
    FNAME
    std::cout << "Iterating forward: ";
    for (typename Container::iterator it = a.begin(); it != a.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Iterating backward: ";
    for (typename Container::reverse_iterator rit = a.rbegin(); rit != a.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;
}

template<typename Container>
void test_exceptions(Container& a) {
    FNAME
    try {
        std::cout << "Exception test: " << a.at(a.size() + 1) << std::endl;
    } catch (const ns::out_of_range& e) {
        std::cout << "Caught out of range" << std::endl;
    }

    try {
        std::cout << "Exception test: " << a.at(-1) << std::endl;
    } catch (const ns::out_of_range& e) {
        std::cout << "Caught out of range" << std::endl;
    }
}

template<typename Container>
void test_relational_operators(Container& a) {
    FNAME
    std::vector<typename Container::value_type> b = get_random_vector<typename Container::value_type>();
    Container other(b.begin(), b.end());
    std::cout << "a == other: " << (a == other) << std::endl;
    std::cout << "a != other: " << (a != other) << std::endl;
    std::cout << "a < other: " << (a < other) << std::endl;
    std::cout << "a <= other: " << (a <= other) << std::endl;
    std::cout << "a > other: " << (a > other) << std::endl;
    std::cout << "a >= other: " << (a >= other) << std::endl;
}

//create vector tester inherit from container tester
template<typename Container>
class SequenceTester : public ContainerTester<Container> {
public:
    virtual void logContainerState() {
        for (typename Container::iterator it = this->container.begin(); it != this->container.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
};