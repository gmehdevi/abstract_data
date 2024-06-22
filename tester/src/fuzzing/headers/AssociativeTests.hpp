#include "Common.hpp"

#ifdef TEST_FT
# define ns ft
# include "map.hpp"  // Adjust according to actual filename
# include "set.hpp"
#else
# define ns std
# include <map>
# include <set>
#endif

// template <typename T1, typename T2>
// std::ostream &operator<<(std::ostream &os, const ns::pair<T1, T2> &p) {
//     os << p.first << " " << p.second;
//     return os;
// }

template<typename Container>
void erase(Container& a) {
    FNAME
    if (!a.empty()) {
        typename Container::iterator it = a.begin();  // Typically erase the first element for simplicity
        a.erase(it);
        std::cout << "Element erased." << std::endl;
    } else {
        std::cout << "Attempt to erase from an empty container." << std::endl;
    }
}

template<typename Container>
void erase_range(Container& a) {
    FNAME
    if (!a.empty()) {
        typename Container::iterator first = a.begin();
        typename Container::iterator last = a.end();
        a.erase(first, last);
        std::cout << "Range erased." << std::endl;
    } else {
        std::cout << "Attempt to erase from an empty container." << std::endl;
    }
}



template<typename Container>
void find(Container& a) {
    FNAME
    typename Container::key_type key = generate_value<typename Container::key_type>();
    typename Container::iterator it = a.find(key);
    if (it != a.end()) {
        std::cout << "Element with key " << key << " found." << std::endl;
    } else {
        std::cout << "Element with key " << key << " not found." << std::endl;
    }
}

template<typename Container>
void test_iterators(Container& a) {
    std::cout << "Iterating through container:" << std::endl;
    for (typename Container::const_iterator it = a.begin(); it != a.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template<typename Container>
void test_constructors(Container& a) {
    FNAME
    Container copy_constructor(a);
    std::cout << "Copy constructed container: ";
    test_iterators(copy_constructor);
}

template<typename Container>
void test_copy_assignment(Container& a) {
    FNAME
    Container copy_assignment;
    copy_assignment = a;
    std::cout << "Performed copy assignment: ";
    test_iterators(copy_assignment);
}


template<typename Container>
void test_const_iterators( Container& a) {
    std::cout << "Iterating through container:" << std::endl;
    for (typename Container::const_iterator it = a.begin(); it != a.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template<typename Container>
class AssociativeTester : public ContainerTester<Container> {
public:
    virtual void logContainerState() {
        std::cout << "Container state: ";
        test_iterators(this->container);
    }
};
