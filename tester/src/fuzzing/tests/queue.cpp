#include <iostream>
#include <cstdlib>
#include "AdapterTests.hpp"


template<typename Container>
class QueueTester : public ContainerTester<Container> {
public:
    virtual void logContainerState() {
        std::cout << "Container state: ";
        Container copy = this->container;
        while (!copy.empty()) {
            std::cout << copy.front() << " ";
            copy.pop();
        }
        std::cout << std::endl;
    }
};

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


    typedef ns::queue<int,  ns::deque<int> > ContainerInt;
    typedef ns::queue<std::string, ns::deque<std::string> > ContainerString;

    QueueTester<ContainerInt> tester_int;
    QueueTester<ContainerString> tester_string;

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


