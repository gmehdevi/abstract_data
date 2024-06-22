#include <iostream>
#include <cstddef>
#include <utility>
#ifdef TEST_FT
# define ns ft
#include "set.hpp"
#include "iterator.hpp"
#else
# define ns std
#include <set>
#include <vector>
#endif

#define T1 int

template <typename T_SET>
void printSet(const T_SET& st) {
    for (typename T_SET::const_iterator it = st.begin(); it != st.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {

    
    ns::multiset<T1> st1;
    for (int i = 1; i <= 5; i++) {
        st1.insert(i * 10);
    }

    std::cout << "Section 1: Basic Set Operations" << std::endl;
    printSet(st1);

    
    st1.erase(20);
    st1.erase(40);

    std::cout << "Section 2: Erasing Elements" << std::endl;
    printSet(st1);

    
    std::cout << "Section 3: Checking Set Properties" << std::endl;
    std::cout << "Size: " << st1.size() << std::endl;
    std::cout << "Empty: " << st1.empty() << std::endl;

    
    ns::multiset<T1> st2;
    for (int i = 3; i < 6; i++) {
        st2.insert(i * 7);
    }

    std::cout << "Section 4: Set Operations" << std::endl;

    
    std::cout << "Section 5: Set Iterators" << std::endl;
    for (ns::multiset<T1>::reverse_iterator it = st1.rbegin(); it != st1.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    printSet(st1);

    
    std::cout << "Section 6: Testing multiset::equal_range" << std::endl;
    std::cout << "Manual lower_bound(30): " << (st1.lower_bound(30) != st1.end() ? *st1.lower_bound(30) : -1) << std::endl;
    std::cout << "Manual upper_bound(30): " << (st1.upper_bound(30) != st1.end() ? *st1.upper_bound(30) : -1) << std::endl;

    ns::pair<ns::multiset<T1>::iterator, ns::multiset<T1>::iterator> range = st1.equal_range(30);
    std::cout << "over " <<std::endl;
    std::cout << *(range.first) << " ";
    std::cout << *(range.second) << " ";

    
    std::cout << "Section 8: Clearing the multiset" << std::endl;
    st1.clear();
    std::cout << "Size after clear: " << st1.size() << std::endl;

    
    std::cout << "Section 9: Testing multiset::swap" << std::endl;
    ns::multiset<T1> st3;
    st3.insert(1);
    st3.insert(2);
    st3.insert(3);

    ns::multiset<T1> st4;
    st4.insert(4);
    st4.insert(5);

    st3.swap(st4);

    std::cout << "Set 3: ";
    printSet(st3);
    std::cout << "Set 4: ";
    printSet(st4);

    
    std::cout << "Section 10: Counting elements in the multiset" << std::endl;
    std::cout << "Number of 30s in the multiset: " << st4.count(30) << std::endl;

    for (ns::multiset<T1>::iterator it = st4.begin(); it != st4.end(); ++it) {
        std::cout << *it << " ";
    }
    
    std::cout << "Section 11: Finding elements in the multiset" << std::endl;
    ns::multiset<T1>::iterator found = st4.find(20);
    if (found != st4.end()) {
        std::cout << "Found element 20 in the multiset: " << *found << std::endl;
    } else {
        std::cout << "Element 20 not found in the multiset." << std::endl;
    }

    return 0;
}
