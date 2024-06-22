#ifdef TEST_FT
# include "set.hpp"
# define ns ft
#else
# include <set>
# define ns std
#endif

#include <iostream>
#include <list>

#define T1 int

using namespace ns;

template <typename T_SET>
void printSet(const T_SET& st) {
    for (typename T_SET::const_iterator it = st.begin(); it != st.end(); ++it) {
        std::cout  << *it << " ";
    }
    std::cout  << std::endl;
}

int main() {

    

    ns::set<T1> st1;
    for (int i = 1; i <= 5; i++) {
        st1.insert(i * 10);
    }

    std::cout  << "Section 1: Basic Set Operations" << std::endl;
    printSet(st1);
    

    st1.erase(20);
    st1.erase(40);

    std::cout  << "Section 2: Erasing Elements" << std::endl;
    printSet(st1);

    

    std::cout  << "Section 3: Checking Set Properties" << std::endl;
    std::cout  << "Size: " << st1.size() << std::endl;
    std::cout  << "Empty: " << st1.empty() << std::endl;

    

    ns::set<T1> st2;
    for (int i = 3; i < 6; i++) {
        st2.insert(i * 7);
    }

    std::cout  << "Section 5: Set Iterators" << std::endl;
    printSet(st1);
    std::cout  << std::endl;

    
    std::cout  << "Section 6: Testing upper_bound, lower_bound and set::equal_range" << std::endl;

    std::cout  << "Lower bound for 30: " << *st1.lower_bound(30) << std::endl;
    std::cout  << "Upper bound for 30: " << *st1.upper_bound(30) << std::endl;

    pair<set<int>::iterator, set<int>::iterator> range = st1.equal_range(30);
    std::cout  << "Equal range for 30: " << *range.first << " " << *range.second << std::endl;
    
    std::cout  << "Section 7: Testing set::insert return value" << std::endl;
    pair<set<int>::iterator, bool> result = st1.insert(50); 
    if (result.second) {
        std::cout  << "Insertion successful, value: " << *result.first << std::endl;
    } else {
        std::cout  << "Insertion failed, value already exists: " << *result.first << std::endl;
    }

    
    std::cout  << "Section 8: Clearing the set" << std::endl;
    st1.clear();
    std::cout  << "Size after clear: " << st1.size() << std::endl;

    for (set<int>::iterator it = st1.begin(); it != st1.end(); ++it) {
        std::cout  << *it << " ";
    }
    for (set<int>::reverse_iterator it = st1.rbegin(); it != st1.rend(); ++it) {
        std::cout  << *it << " ";
    }
    return 0;
}
