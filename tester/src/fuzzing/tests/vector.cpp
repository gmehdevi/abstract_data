#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "SequenceTests.hpp"


int main(int argc, char** argv) {
    if (argc != 3)
        std::cerr << "Usage: " << argv[0] << " <iterations> <seed>" << std::endl;

    int seed = std::atoi(argv[2]);
    int iterations = std::atoi(argv[1]);

    srand(seed);

    typedef ns::vector<int> ContainerInt;
    typedef ns::vector<std::string> ContainerString;

    SequenceTester<ContainerInt> tester_int;
    SequenceTester<ContainerString> tester_string;

    tester_int.addFunction(push_back<ContainerInt>);
    tester_int.addFunction(pop_back<ContainerInt>);
    tester_int.addFunction(insert<ContainerInt>);
    tester_int.addFunction(erase<ContainerInt>);
    tester_int.addFunction(clear<ContainerInt>);
    tester_int.addFunction(resize<ContainerInt>);
    tester_int.addFunction(check_front<ContainerInt>);
    tester_int.addFunction(check_back<ContainerInt>);
    tester_int.addFunction(check_empty<ContainerInt>);
    tester_int.addFunction(test_swap<ContainerInt>);
    tester_int.addFunction(check_at<ContainerInt>);
    tester_int.addFunction(test_constructors<ContainerInt>);
    tester_int.addFunction(test_range_insert<ContainerInt>);
    tester_int.addFunction(test_copy_assignment<ContainerInt>);
    tester_int.addFunction(modify_back<ContainerInt>);
    tester_int.addFunction(test_iterators<ContainerInt>);
    tester_int.addFunction(test_exceptions<ContainerInt>);
    tester_int.addFunction(test_relational_operators<ContainerInt>);
    tester_int.testOperations(iterations);

    tester_string.addFunction(push_back<ContainerString>);
    tester_string.addFunction(pop_back<ContainerString>);
    tester_string.addFunction(insert<ContainerString>);
    tester_string.addFunction(erase<ContainerString>);
    tester_string.addFunction(clear<ContainerString>);
    tester_string.addFunction(resize<ContainerString>);
    tester_string.addFunction(check_front<ContainerString>);
    tester_string.addFunction(check_back<ContainerString>);
    tester_string.addFunction(check_empty<ContainerString>);
    tester_string.addFunction(test_swap<ContainerString>);
    tester_string.addFunction(check_at<ContainerString>);
    tester_string.addFunction(test_constructors<ContainerString>);
    tester_string.addFunction(test_range_insert<ContainerString>);
    tester_string.addFunction(test_copy_assignment<ContainerString>);
    tester_string.addFunction(modify_back<ContainerString>);
    tester_string.addFunction(test_iterators<ContainerString>);
    tester_string.addFunction(test_exceptions<ContainerString>);
    tester_string.addFunction(test_relational_operators<ContainerString>);
    tester_string.testOperations(iterations);

    return 0;
}
