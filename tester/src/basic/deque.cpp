#include <iostream>
#include <iterator>
#include <vector>
#ifdef TEST_FT
    #include "deque.hpp" // Include your deque implementation header here
    #define NAMESPACE ft
#else
    #include <deque>
    #define NAMESPACE std
#endif

using namespace NAMESPACE;

int main() {
    // Create a deque of integers
    deque<int> myDeque;

    // Insert elements into the deque
    myDeque.push_back(1);
    myDeque.push_back(2);
    myDeque.push_back(3);

    // Iterate over the deque and print its contents
    std::cout << "Deque contents:" << std::endl;
    for (deque<int>::iterator it = myDeque.begin(); it != myDeque.end(); it++) {
        std::cout << *it << "|";
         std::cout << std::endl;
        
    }
    std::cout << std::endl;

    for (deque<int>::reverse_iterator it = myDeque.rbegin(); it != myDeque.rend(); it++) {
        std::cout << *it << " ";
    }

    std::cout << std::endl;



    std::cout << std::endl;

    // Test other deque operations
    std::cout << "Deque size: " << myDeque.size() << std::endl;

    // Access elements by index (requires random access iterator)
    deque<int>::iterator it = myDeque.begin();
    ++it; // Manually increment the iterator
    std::cout << "Element at index 1: " << *it << std::endl;

    // Insert an element at a specific position
    it = myDeque.begin();
    ++it; // Move to the second element
    myDeque.insert(it, 4);

    std::cout << "Deque contents after insertion:" << std::endl;
    for (deque<int>::const_iterator it = myDeque.begin(); it != myDeque.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Remove elements from the deque
    it = myDeque.begin();

    ++it; // Move to the second element
    myDeque.erase(it);

    

    it = myDeque.begin();


    std::cout << "here" << std::endl;

    std::cout << "Deque contents after removal:" << std::endl;
    for (deque<int>::iterator it = myDeque.begin(); it != myDeque.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Clear the deque
    myDeque.clear();
    std::cout << "Deque size after clear: " << myDeque.size() << std::endl;

    // Test empty and front functions
    deque<int> emptyDeque;
    std::cout << "Is emptyDeque empty? " << (emptyDeque.empty() ? "Yes" : "No") << std::endl;
    emptyDeque.push_back(42);
    std::cout << "Front element of emptyDeque: " << emptyDeque.front() << std::endl;

    // Test copying and assignment
    deque<int> copiedDeque;
    copiedDeque.push_back(5);
    copiedDeque.push_back(6);
    deque<int> assignedDeque = copiedDeque;

    std::cout << "Copied deque contents:" << std::endl;
    for (deque<int>::const_iterator it = copiedDeque.begin(); it != copiedDeque.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Assigned deque contents:" << std::endl;
    for (deque<int>::const_iterator it = assignedDeque.begin(); it != assignedDeque.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Test insert
    deque<int> insertDeque;
    vector<int> insertVector;

    for (int i = 0; i < 10; i++) {
        insertDeque.push_back(i);
    }

    for (deque<int>::const_iterator it = insertDeque.begin(); it != insertDeque.end(); ++it) {
        std::cout << *it << " ";
    }
std::cout << std::endl;
    insertDeque.insert(insertDeque.begin(), 42);

    for (deque<int>::const_iterator it = insertDeque.begin(); it != insertDeque.end(); ++it) {
        std::cout << *it << " ";
    }
    insertDeque.insert(insertDeque.end(), 42);

std::cout << std::endl;
    for (deque<int>::const_iterator it = insertDeque.begin(); it != insertDeque.end(); ++it) {
        std::cout << *it << " ";
    }
    insertDeque.insert(insertDeque.begin() + 5, 42);
std::cout << std::endl;
    for (deque<int>::const_iterator it = insertDeque.begin(); it != insertDeque.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    insertDeque.insert(insertDeque.begin() + insertDeque.size() / 2, insertVector.begin(), insertVector.end());
    
    for (deque<int>::const_iterator it = insertDeque.begin(); it != insertDeque.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout<< std::endl;


    // Test erase
    deque<int> eraseDeque;
    

    return 0;
}
