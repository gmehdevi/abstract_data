#include <iostream>
#include <queue>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "queue.hpp"
#ifdef TEST_FT
# define ns ft
#else
# define ns std
#endif

#define count 10000
using namespace ns;
typedef int T;

int main(int ac, char **av) {
    try {
        (void)ac;
        clock_t begin = clock();
        srand(atoi(av[1]));

        std::queue<T> myQueue;
        for (size_t i = 0; i < count; i++)
            myQueue.push(static_cast<T>(i));
        for (size_t i = 0; i < count; i++) {
            myQueue.pop();
            myQueue.push(static_cast<T>(i + count));
        }

        clock_t end = clock();
        std::cout << (double)(end - begin) / CLOCKS_PER_SEC << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
