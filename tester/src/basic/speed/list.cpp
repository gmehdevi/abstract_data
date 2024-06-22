#include <iostream>
#include <list>
#include <cstddef>
#include <cstdlib>
#include <ctime>

#ifdef TEST_FT
# define ns ft
# include "list.hpp"
#else
# define ns std
# include <list>
#endif

#define count 10000
using namespace ns;
typedef int T;

template <typename Container>
typename Container::iterator rand_it(Container &c) {
    typename Container::iterator it = c.begin();
    std::advance(it, rand() % c.size());
    return it;
}

int main(int ac, char **av) {
    try {
        (void)ac;
        clock_t begin = clock();
        srand(atoi(av[1]));

        ns::list<T> myList;
        for (size_t i = 0; i < count; i++)
            myList.push_back(static_cast<T>(i));
        for (size_t i = 0; i < count; i++)
            myList.erase(rand_it(myList));

        clock_t end = clock();
        std::cout << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
