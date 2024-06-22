#include <iostream>
#include "unordered_set.hpp"

// //print pairs ostream << operator
template <class T1, class T2>
std::ostream &operator<<(std::ostream &os, const ft::pair<T1, T2> &p) {
    os << p.first << " " << p.second;
    return os;
}

//  ostream operator pair <T.T>
template <class T>
std::ostream &operator<<(std::ostream &os, const ft::pair<T, T> &p) {
    os << p.first << " " << p.second;
    return os;
}

void test_insert() {
    ft::unordered_set<int> uset;
    uset.insert(1);
    uset.insert(2);
    uset.insert(3);

    if (uset.size() == 3) {
        std::cout << "test_insert: Passed\n";
    } else {
        std::cout << "test_insert: Failed\n";
    }
}

void test_find() {
    ft::unordered_set<int> uset;
    uset.insert(1);
    uset.insert(2);
    uset.insert(3);
    
    if (uset.find(2) != uset.end() && uset.find(4) == uset.end()) {
        std::cout << "test_find: Passed\n";
    } else {
        std::cout << "test_find: Failed\n";
    }
}

void test_erase() {
    ft::unordered_set<int> uset;
    uset.insert(1);
    uset.insert(2);
    uset.insert(3);
    
    uset.erase(uset.find(2));
    
    if (uset.size() == 2 && uset.find(2) == uset.end()) {
        std::cout << "test_erase: Passed\n";
    } else {
        std::cout << "test_erase: Failed\n";
    }
}

void test_iteration() {
    ft::unordered_set<int> uset;
    uset.insert(1);
    uset.insert(2);
    uset.insert(3);

    int count = 0;
    for (ft::unordered_set<int>::iterator it = uset.begin(); it != uset.end(); ++it) {
        std::cout << *it << " "; // Print elements to debug
        count++;
    }
    std::cout << std::endl;

    if (count == 3) {
        std::cout << "test_iteration: Passed\n";
    } else {
        std::cout << "test_iteration: Failed\n";
    }
}

void test_capacity() {
    ft::unordered_set<int> uset;
    if (uset.empty() && uset.size() == 0) {
        std::cout << "test_capacity: Passed\n";
    } else {
        std::cout << "test_capacity: Failed\n";
    }
}

void test_clear() {
    ft::unordered_set<int> uset;
    uset.insert(1);
    uset.insert(2);
    uset.insert(3);
    
    uset.clear();
    
    if (uset.empty()) {
        std::cout << "test_clear: Passed\n";
    } else {
        std::cout << "test_clear: Failed\n";
    }
}

void test_swap() {
    ft::unordered_set<int> uset1;
    uset1.insert(1);
    uset1.insert(2);

    ft::unordered_set<int> uset2;
    uset2.insert(3);
    uset2.insert(4);

    uset1.swap(uset2);

    if (uset1.find(3) != uset1.end() && uset2.find(1) != uset2.end()) {
        std::cout << "test_swap: Passed\n";
    } else {
        std::cout << "test_swap: Failed\n";
    }
}

void run_all_tests() {
    test_insert();
    test_find();
    test_erase();
    test_iteration();
    test_capacity();
    test_clear();
    test_swap();
}

int main() {
    run_all_tests();
    return 0;
}
