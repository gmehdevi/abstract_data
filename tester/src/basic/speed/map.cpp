#include <iostream>
#include <map>
#include "map.hpp"
#include <cstddef>
#include <utility>
#include <stdlib.h>
#ifdef TEST_FT
# define ns ft
#else
# define ns std
#endif
#define count 10000
using namespace ns;
typedef int T;

map<T, T>::iterator rand_it(map<T, T> &m) {
    map<T, T>::iterator ret = m.begin();
    for (int r = (rand() + 1)%m.size(); r > 0;r--)
        ret++;
    return ret;
}

int main(int ac, char **av) {
    try {
    (void )ac;
    clock_t begin = clock();
    srand(atoi(av[1]));
    map<T, T> m;
    for (size_t i = 0; i < count; i++)
        (void)m.insert(pair<int, int>(i, i));
    for (size_t i = 0; i < count; i++)
        (void)m.erase(rand_it(m));
    for (int i = 0; i < count; i++)
        (void)m.find(static_cast<const int>(i));
    clock_t end = clock();
    std::cout << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    } catch (ns::exception e){std::cerr << e.what() << std::endl;}

    return 0;
}