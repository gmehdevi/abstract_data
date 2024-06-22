#include <iostream>
#include <queue>

#ifdef TEST_FT
# define ns ft
#include "queue.hpp"
#else
# define ns std
#endif

class CustomItem {
public:
    CustomItem(int id) : id(id) {}
    int getId() const { return id; }

private:
    int id;
};

int main() {
   
    ns::queue<int> intQueue;

   
    std::cout << "Queue contents (int):" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        intQueue.push(i);
        std::cout << i << " ";
    }
    std::cout << std::endl;

   
    std::cout << "Front element (int): " << intQueue.front() << std::endl;

   
    std::cout << "Queue size (int): " << intQueue.size() << std::endl;

   
    std::cout << "Is the queue empty (int)? " << (intQueue.empty() ? "Yes" : "No") << std::endl;

   
    std::cout << "Popping elements (int):" << std::endl;
    while (!intQueue.empty()) {
        std::cout << "Front element: " << intQueue.front() << std::endl;
        intQueue.pop();
    }

   
    ns::queue<CustomItem> customQueue;

   
    std::cout << "Queue contents (CustomItem):" << std::endl;
    for (int i = 1; i <= 3; ++i) {
        customQueue.push(CustomItem(i));
        std::cout << "CustomItem(" << i << ") ";
    }
    std::cout << std::endl;

   
    std::cout << "Front element (CustomItem): " << customQueue.front().getId() << std::endl;

   
    std::cout << "Queue size (CustomItem): " << customQueue.size() << std::endl;

   
    std::cout << "Is the queue empty (CustomItem)? " << (customQueue.empty() ? "Yes" : "No") << std::endl;

   
    std::cout << "Popping elements (CustomItem):" << std::endl;
    while (!customQueue.empty()) {
        std::cout << "Front element: " << customQueue.front().getId() << std::endl;
        customQueue.pop();
    }

    return 0;
}
