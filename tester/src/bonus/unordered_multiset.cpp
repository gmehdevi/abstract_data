#include <iostream>
#include <cassert>
#include "unordered_multiset.hpp"

void test_insert_and_find() {
    ft::unordered_multiset<int> multiset;

    // Test single insertion
    multiset.insert(1);
    multiset.insert(2);
    multiset.insert(1); // Duplicate key

    // Find elements
    ft::unordered_multiset<int>::iterator it = multiset.find(1);
    assert(it != multiset.end());

    it = multiset.find(2);
    assert(it != multiset.end());

    it = multiset.find(3);
    assert(it == multiset.end()); // Key not present
}

void test_size_and_empty() {
    ft::unordered_multiset<int> multiset;

    assert(multiset.size() == 0);
    assert(multiset.empty());

    multiset.insert(1);
    assert(multiset.size() == 1);
    assert(!multiset.empty());

    multiset.insert(2);
    multiset.insert(1); // Duplicate key
    assert(multiset.size() == 3); // Multiset allows duplicates

    multiset.insert(3);
    assert(multiset.size() == 4);
}

void test_iterator() {
    ft::unordered_multiset<int> multiset;

    multiset.insert(1);
    multiset.insert(2);
    multiset.insert(1); // Duplicate key

    int count = 0;
    for (ft::unordered_multiset<int>::iterator it = multiset.begin(); it != multiset.end(); ++it) {
        assert(*it == 1 || *it == 2);
        ++count;
    }
    assert(count == 3);
    
    for (ft::unordered_multiset<int>::iterator it = multiset.begin(); it != multiset.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

void test_custom_initialization() {
    ft::unordered_multiset<int> multiset(16); // Custom bucket count

    multiset.insert(1);
    multiset.insert(2);

    assert(multiset.size() == 2);
}

int main() {
    std::cout << "Running unordered_multiset tests..." << std::endl;

    test_insert_and_find();
    std::cout << "Insert and find test passed." << std::endl;

    test_size_and_empty();
    std::cout << "Size and empty test passed." << std::endl;

    test_iterator();
    std::cout << "Iterator test passed." << std::endl;

    test_custom_initialization();
    std::cout << "Custom initialization test passed." << std::endl;

    std::cout << "All tests passed!" << std::endl;



    return 0;
}
