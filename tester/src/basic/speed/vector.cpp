#include <memory>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <cstddef>
#include <limits>
#include <climits>
#include <stdio.h>
#include <time.h> 
#include "vector.hpp"
#include <iostream>
#define count 10000// dont go beyond 10000 takes too long
#ifdef TEST_FT
    #define ns ft
#else
    #define ns std
#endif
using namespace ns;


int main(int ac, char **av) {
    (void)ac;
    clock_t begin = clock();
    srand(atoi(av[1]));
    ns::vector<int> v(count, 1);


	for (int i = 0; i < count; i++)
		v.insert(v.begin() + rand() % v.size(), 42);


    v.insert(v.begin() +  rand() % v.size(), count, 42);


    while (!v.empty()) v.pop_back();


    for (int i = 0; i < count; i++) v.push_back(rand());

    v.assign(count, 42);    


    v.resize(v.size() * 10);

    clock_t end = clock();
    std::cout << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    
    return 0;
}