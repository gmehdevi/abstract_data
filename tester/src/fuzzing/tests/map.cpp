#include <iostream>
#include <cstdlib>
#include "AssociativeTests.hpp"


template<typename Container>
void insert(Container& a) {
    FNAME
    ns::pair<typename Container::key_type, typename Container::mapped_type> value = generate_pair<typename Container::key_type, typename Container::mapped_type>();
    a.insert(value);
    std::cout << "Inserted pair: " << value.first << " -> " << value.second << std::endl;
}

template<typename Container>
void insert_range(Container& a) {
    FNAME
    std::vector<ns::pair<typename Container::key_type, typename Container::mapped_type> > range;
    for (int i = 0; i < BASE_SIZE; ++i) {
        range.push_back(generate_pair<typename Container::key_type, typename Container::mapped_type>());
    }
    a.insert(range.begin(), range.end());
    std::cout << "Inserted range:" << std::endl;
    for (typename std::vector<ns::pair<typename Container::key_type, typename Container::mapped_type> >::iterator it = range.begin(); it != range.end(); ++it) {
        std::cout << it->first << " -> " << it->second << std::endl;
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <iterations> <seed>" << std::endl;
        return 1;
    }

    int iterations = std::atoi(argv[1]);
    int seed = std::atoi(argv[2]);
    srand(seed);

    typedef ns::map<std::string, int> MapStringInt;
    typedef ns::map<int, std::string> MapIntString;


    AssociativeTester<MapIntString> tester_is;
    AssociativeTester<MapStringInt> tester_si;

    tester_is.addFunction(insert<MapIntString>);
    tester_is.addFunction(erase<MapIntString>);
    tester_is.addFunction(find<MapIntString>);
    tester_is.addFunction(test_constructors<MapIntString>);
    tester_is.addFunction(test_copy_assignment<MapIntString>);
    tester_is.addFunction(insert_range<MapIntString>);
    tester_is.addFunction(erase_range<MapIntString>);
    tester_is.addFunction(test_iterators<MapIntString>);
    tester_is.addFunction(test_const_iterators<MapIntString>);
    tester_is.testOperations(iterations);

    tester_si.addFunction(insert<MapStringInt>);
    tester_si.addFunction(erase<MapStringInt>);
    tester_si.addFunction(find<MapStringInt>);
    tester_si.addFunction(test_constructors<MapStringInt>);
    tester_si.addFunction(test_copy_assignment<MapStringInt>);
    tester_si.addFunction(insert_range<MapStringInt>);
    tester_si.addFunction(erase_range<MapStringInt>);
    tester_si.addFunction(test_iterators<MapStringInt>);
    tester_si.addFunction(test_const_iterators<MapStringInt>);
    tester_si.testOperations(iterations);

    return 0;
}
