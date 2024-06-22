#include <iostream>
#include <cstddef>
#include <utility>
#ifdef TEST_FT
# define ns ft
#include "queue.hpp"
#else
# define ns std
#include <queue>
#endif
#include <cstdlib>
#define T1 int

template <typename T_QUEUE>
void printQueue(const T_QUEUE& pq) {
    T_QUEUE temp = pq;
    while (!temp.empty()) {
        std::cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << std::endl;
}

int main() {
    srand(0);
    ns::priority_queue<T1> pq1;
    for (int i = 1; i <= 5; i++) {
        pq1.push(rand() * 10);
    }

    printQueue(pq1);

    pq1.pop();
    printQueue(pq1);

    std::cout << "Size: " << pq1.size() << std::endl;
    std::cout << "Empty: " << pq1.empty() << std::endl;

    ns::priority_queue<T1> pq2;
    for (int i = 3; i < 6; i++) {
        pq2.push(rand() * 7);
    }

    ns::swap(pq1, pq2);

    std::cout << "Priority Queue 1: ";
    printQueue(pq1);
    std::cout << "Priority Queue 2: ";
    printQueue(pq2);


    while (!pq1.empty()) {
        pq1.pop();
    }
    std::cout << "Size after clear: " << pq1.size() << std::endl;

    pq1.push(50);
    pq1.push(30);
    pq1.push(70);
    pq1.push(20);

    printQueue(pq1);

    std::cout << "Top element: " << pq1.top() << std::endl;

    
    ns::priority_queue<T1> pq3(pq1);
    std::cout << "Priority Queue 3: ";
    printQueue(pq3);

    ns::priority_queue<T1> pq4;
    pq4 = pq1;
    std::cout << "Priority Queue 4: ";
    printQueue(pq4);

    return 0;
}
