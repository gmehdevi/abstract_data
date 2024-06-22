#include <iostream>
#include <cstdlib>
#include "AdapterTests.hpp"

template <class Container>
void underlying_constructor(Container &a) {
	std::vector<typename Container::value_type> v = get_random_vector<typename Container::value_type>();
	typename Container::container_type underlying(v.begin(), v.end());
	std::cout << "a = C(compare(), underlying) with underlying: " << std::endl;
	for (typename Container::container_type::iterator it = underlying.begin(); it != underlying.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	a = C(typename Container::value_compare(), underlying);
}


int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <iterations> <seed>" << std::endl;
        return 1;
    }

    int iterations = std::atoi(argv[1]);
    int seed = std::atoi(argv[2]);

    if (iterations <= 0 || seed <= 0) {
        std::cerr << "Please provide positive integers for iterations and seed." << std::endl;
        return 1;
    }

    srand(seed);


    typedef ns::priority_queue<int,  ns::vector<int> > ContainerInt;
    typedef ns::priority_queue<std::string, ns::vector<std::string> > ContainerString;

    AdapterTester<ContainerInt> tester_int;
    AdapterTester<ContainerString> tester_string;

    tester_int.addFunction(push<ContainerInt>);
    tester_int.addFunction(pop<ContainerInt>);
    tester_int.addFunction(size<ContainerInt>);
    tester_int.addFunction(empty<ContainerInt>);
    tester_int.addFunction(test_default_constructor<ContainerInt>);
    tester_int.addFunction(test_copy_constructor<ContainerInt>);
    tester_int.addFunction(test_assignment_operator<ContainerInt>);
    tester_int.testOperations(iterations);

    tester_string.addFunction(push<ContainerString>);
    tester_string.addFunction(pop<ContainerString>);
    tester_string.addFunction(size<ContainerString>);
    tester_string.addFunction(empty<ContainerString>);
    tester_string.addFunction(test_default_constructor<ContainerString>);
    tester_string.addFunction(test_copy_constructor<ContainerString>);
    tester_string.addFunction(test_assignment_operator<ContainerString>);
    tester_string.testOperations(iterations);

    return 0;
}


