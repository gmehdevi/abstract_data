#include <iostream>
#ifdef TEST_FT
# define ns ft
#include "map.hpp"
#include "iterator.hpp"
#else
# define ns std
#include <map>
#include <vector>
#endif


int main() {
    ns::multimap<int, std::string> multimap;

    
    multimap.insert(ns::make_pair(1, "apple"));
    multimap.insert(ns::make_pair(2, "banana"));
    multimap.insert(ns::make_pair(2, "blueberry")); 
    multimap.insert(ns::make_pair(2, "razpberry")); 
    multimap.insert(ns::make_pair(3, "cherry"));
    multimap.insert(ns::make_pair(3, "cranberry")); 

    
    std::cout << "Multimap contents:" << std::endl;
    for (ns::multimap<int, std::string>::iterator it = multimap.begin(); it != multimap.end(); ++it) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    }
    
    std::cout << "Multimap size: " << multimap.size() << std::endl;
    
    std::cout << multimap.count(1) << std::endl;
    std::cout << multimap.count(2) << std::endl;
    std::cout << multimap.count(3) << std::endl;

    
    int keyToFind = 2;
    ns::pair<ns::multimap<int, std::string>::iterator, ns::multimap<int, std::string>::iterator> range = multimap.equal_range(keyToFind);
    std::cout << "Elements with key " << keyToFind << ":" << std::endl;
    for (ns::multimap<int, std::string>::iterator it = range.first; it != range.second; ++it) {
        std::cout << "Value: " << it->second << std::endl;
    }

    std::cout << multimap.count(1) << std::endl;
    multimap.erase(1);
    std::cout << multimap.count(1) << std::endl;
    
    std::cout << "Multimap contents after erasing key " << 1 << ":" << std::endl;
    for (ns::multimap<int, std::string>::iterator pair = multimap.begin(); pair != multimap.end(); ++pair) {
        std::cout << "Key: " << pair->first << ", Value: " << pair->second << std::endl;
    }

    int keyToErase = 3;
    std::cout << multimap.count(keyToErase) << std::endl;
    std::cout << multimap.erase(keyToErase) << std::endl;
    std::cout << "Multimap contents after erasing key " << keyToErase << ":" << std::endl;
    for (ns::multimap<int, std::string>::iterator pair = multimap.begin(); pair != multimap.end(); ++pair) {
        std::cout << "Key: " << pair->first << ", Value: " << pair->second << std::endl;
    }

    return 0;
}
