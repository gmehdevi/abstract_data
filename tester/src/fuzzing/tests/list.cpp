#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "SequenceTests.hpp"
#include "ListTests.hpp"

int main(int argc, char** argv) {
    if (argc != 3)
        std::cerr << "Usage: " << argv[0] << " <iterations> <seed>" << std::endl;

    std::string args[] = {argv[1], argv[2]};

    int iterations = std::atoi(args[0].data());
    int seed = std::atoi(args[1].data());

    srand(seed);

    typedef ns::list<int> ContainerInt;
    typedef ns::list<std::string> ContainerString;

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
    tester_int.addFunction(test_constructors<ContainerInt>);
    tester_int.addFunction(test_range_insert<ContainerInt>);
    tester_int.addFunction(test_copy_assignment<ContainerInt>);
    tester_int.addFunction(test_iterators<ContainerInt>);
    tester_int.addFunction(test_relational_operators<ContainerInt>);
    tester_int.addFunction(merge<ContainerInt>);
    tester_int.addFunction(splice<ContainerInt>);
    tester_int.addFunction(splice_range<ContainerInt>);
    tester_int.addFunction(remove<ContainerInt>);
    tester_int.addFunction(remove_if<ContainerInt>);
    tester_int.addFunction(unique<ContainerInt>);
    tester_int.addFunction(sort<ContainerInt>);
    tester_int.addFunction(reverse<ContainerInt>);
    tester_int.addFunction(splice_it<ContainerInt>);
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
    tester_string.addFunction(test_constructors<ContainerString>);
    tester_string.addFunction(test_range_insert<ContainerString>);
    tester_string.addFunction(test_copy_assignment<ContainerString>);
    tester_string.addFunction(test_iterators<ContainerString>);
    tester_string.addFunction(test_relational_operators<ContainerString>);
    tester_string.addFunction(splice_it<ContainerString>);
    tester_string.testOperations(iterations);

    return 0;
}
