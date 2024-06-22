#include <iostream>
#include <cstdlib>
#include "AssociativeTests.hpp"

template<typename Container>
void insert(Container& a) {
    typename Container::value_type value(generate_value<typename Container::value_type>());
    print_it(a, a.insert(value));
}

template<typename Container>
void insert_hint(Container& a) {
    typename Container::value_type value(generate_value<typename Container::value_type>());
    typename Container::iterator hint = get_random_it(a);
    typename Container::iterator ret = a.insert(hint, value);
    std::cout << "ret = ";
    print_it(a, ret);
    std::cout << std::endl;
}

template<typename Container>
void insert_range(Container& a) {
    std::vector<typename Container::value_type> range = get_random_vector<typename Container::value_type>();
    a.insert(range.begin(),range.end());
}


int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <iterations> <seed>" << std::endl;
        return 1;
    }

    int iterations = std::atoi(argv[1]);
    int seed = std::atoi(argv[2]);
    srand(seed);

    typedef ns::multiset<int> SetInt;
    typedef ns::multiset<std::string> SetString;


    AssociativeTester<SetInt> tester_is;
    AssociativeTester<SetString> tester_si;

    tester_is.addFunction(insert<SetInt>);
    tester_is.addFunction(erase<SetInt>);
    tester_is.addFunction(find<SetInt>);
    tester_is.addFunction(test_constructors<SetInt>);
    tester_is.addFunction(test_copy_assignment<SetInt>);
    tester_is.addFunction(insert_hint<SetInt>);
    tester_is.addFunction(insert_range<SetInt>);
    tester_is.addFunction(erase_range<SetInt>);
    tester_is.addFunction(test_iterators<SetInt>);
    tester_is.addFunction(test_const_iterators<SetInt>);

    tester_is.testOperations(iterations);

    tester_si.addFunction(insert<SetString>);
    tester_si.addFunction(erase<SetString>);
    tester_si.addFunction(find<SetString>);
    tester_si.addFunction(test_constructors<SetString>);
    tester_si.addFunction(test_copy_assignment<SetString>);
    tester_si.addFunction(insert_hint<SetString>);
    tester_si.addFunction(insert_range<SetString>);
    tester_si.addFunction(erase_range<SetString>);
    tester_si.addFunction(test_iterators<SetString>);
    tester_si.addFunction(test_const_iterators<SetString>);

    tester_si.testOperations(iterations);

    return 0;
}
