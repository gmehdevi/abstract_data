#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "unordered_multimap.hpp"

void test_insert_and_get() {
    ft::unordered_multimap<int, std::string> umm;
    umm.insert(ft::make_pair(1, "one"));
    umm.insert(ft::make_pair(2, "two"));
    umm.insert(ft::make_pair(1, "uno"));

    assert(umm.count(1) == 2);
    assert(umm.count(2) == 1);

    std::cout << "test_insert_and_get passed." << std::endl;
}

void test_remove() {
    ft::unordered_multimap<int, std::string> umm;
    umm.insert(ft::make_pair(1, "one"));
    umm.insert(ft::make_pair(1, "uno"));
    umm.insert(ft::make_pair(2, "two"));

    umm.erase(umm.find(1));
    assert(umm.count(1) == 1);
    assert(umm.count(2) == 1);

    umm.erase(umm.find(1));
    assert(umm.count(1) == 0);
    assert(umm.count(2) == 1);

    std::cout << "test_remove passed." << std::endl;
}

void test_contains() {
    ft::unordered_multimap<int, std::string> umm;
    umm.insert(ft::make_pair(1, "one"));
    umm.insert(ft::make_pair(2, "two"));

    assert(umm.count(1) == 1);
    assert(umm.count(2) == 1);
    assert(umm.count(3) == 0);

    std::cout << "test_contains passed." << std::endl;
}

void test_size() {
    ft::unordered_multimap<int, std::string> umm;
    umm.insert(ft::make_pair(1, "one"));
    umm.insert(ft::make_pair(2, "two"));
    umm.insert(ft::make_pair(1, "uno"));

    assert(umm.size() == 3);

    umm.erase(umm.find(1));
    assert(umm.size() == 2);

    umm.erase(umm.find(1));
    assert(umm.size() == 1);

    std::cout << "test_size passed." << std::endl;
}

void test_iteration() {
    ft::unordered_multimap<int, std::string> umm;
    umm.insert(ft::make_pair(1, "one"));
    umm.insert(ft::make_pair(2, "two"));
    umm.insert(ft::make_pair(3, "three"));
    umm.insert(ft::make_pair(1, "uno"));

    std::vector<ft::pair<int, std::string> > elements;
    for (ft::unordered_multimap<int, std::string>::iterator it = umm.begin(); it != umm.end(); ++it) {
        elements.push_back(*it);
        std::cout << it->first << " " << it->second << std::endl;
    }

    assert(elements.size() == 4);
    std::cout << "test_iteration passed." << std::endl;
}

int main() {
    test_insert_and_get();
    test_remove();
    test_contains();
    test_size();
    test_iteration();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
