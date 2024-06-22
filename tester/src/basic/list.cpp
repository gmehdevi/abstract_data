#include <iostream>
#include <list>
#include <iterator>

#ifdef TEST_FT
    #include "list.hpp"
    #define NAMESPACE ft
#else
    #include <list>
    #define NAMESPACE std
#endif

using namespace NAMESPACE;

int main() {
    list<int> myList;

    std::cout << "List contents:" << std::endl;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);

    std::cout << "List contents:" << std::endl;
    for (list<int>::iterator it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "List size: " << myList.size() << std::endl;

    list<int>::iterator it = myList.begin();
    advance(it, 1);
    std::cout << "Element at index 1: " << *it << std::endl;

    myList.insert(++myList.begin(), 4);

    std::cout << "List contents after insertion:" << std::endl;
    for (list<int>::const_iterator it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    myList.remove(2);

    std::cout << "List contents after removal:" << std::endl;
    for (list<int>::const_iterator it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    myList.clear();
    std::cout << "List size after clear: " << myList.size() << std::endl;

    list<int> emptyList;
    std::cout << "Is emptyList empty? " << (emptyList.empty() ? "Yes" : "No") << std::endl;
    emptyList.push_back(42);
    std::cout << "Front element of emptyList: " << emptyList.front() << std::endl;

    list<int> copiedList;
    copiedList.push_back(5);
    copiedList.push_back(6);
    list<int> assignedList = copiedList;

    std::cout << "Copied list contents:" << std::endl;
    for (list<int>::const_iterator it = copiedList.begin(); it != copiedList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Assigned list contents:" << std::endl;
    for (list<int>::const_iterator it = assignedList.begin(); it != assignedList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    return 0;
}
