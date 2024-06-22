#include <iostream>
#include "unordered_map.hpp"

void test_insert() {
    ft::unordered_map<int, std::string> umap;
    //insert
    umap.insert(ft::make_pair(1, "one"));
    umap.insert(ft::make_pair(2, "two"));
    umap.insert(ft::make_pair(3, "three"));

    if (umap.size() == 3) {
        std::cout << "test_insert: Passed\n";
    } else {
        std::cout << "test_insert: Failed\n";
    }
}

void test_find() {
    ft::unordered_map<int, std::string> umap;
    umap.insert(ft::make_pair(1, "one"));
    umap.insert(ft::make_pair(2, "two"));
    umap.insert(ft::make_pair(3, "three"));
    
    if (umap.find(2) != umap.end() && umap.find(4) == umap.end()) {
        std::cout << "test_find: Passed\n";
    } else {
        std::cout << "test_find: Failed\n";
    }
}

void test_erase() {
    ft::unordered_map<int, std::string> umap;
    umap.insert(ft::make_pair(1, "one"));
    umap.insert(ft::make_pair(2, "two"));
    umap.insert(ft::make_pair(3, "three"));
    
    umap.erase(umap.find(2));
    
    if (umap.size() == 2 && umap.find(2) == umap.end()) {
        std::cout << "test_erase: Passed\n";
    } else {
        std::cout << "test_erase: Failed\n";
    }
}

void test_iteration() {
    ft::unordered_map<int, std::string> umap;
    umap.insert(ft::make_pair(1, "one"));
    umap.insert(ft::make_pair(2, "two"));
    umap.insert(ft::make_pair(3, "three"));

    int count = 0;
    for (ft::unordered_map<int, std::string>::iterator it = umap.begin(); it != umap.end(); ++it) {
        std::cout << it->first << " => " << it->second << " "; // Print elements to debug
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
    ft::unordered_map<int, std::string> umap;
    if (umap.empty() && umap.size() == 0) {
        std::cout << "test_capacity: Passed\n";
    } else {
        std::cout << "test_capacity: Failed\n";
    }
}

void test_clear() {
    ft::unordered_map<int, std::string> umap;
    umap.insert(ft::make_pair(1, "one"));
    umap.insert(ft::make_pair(2, "two"));
    umap.insert(ft::make_pair(3, "three"));
    
    umap.clear();
    
    if (umap.empty()) {
        std::cout << "test_clear: Passed\n";
    } else {
        std::cout << "test_clear: Failed\n";
    }
}

void test_swap() {
    ft::unordered_map<int, std::string> umap1;
    umap1.insert(ft::make_pair(1, "one"));
    umap1.insert(ft::make_pair(2, "two"));

    ft::unordered_map<int, std::string> umap2;
    umap2.insert(ft::make_pair(3, "three"));
    umap2.insert(ft::make_pair(4, "four"));

    umap1.swap(umap2);

    if (umap1.find(3) != umap1.end() && umap2.find(1) != umap2.end()) {
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
