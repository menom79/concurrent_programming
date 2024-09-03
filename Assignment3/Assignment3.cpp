#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::vector<int> dynamicArray;
std::mutex mtx; 

void addNumbers() {
    for (int i = 0; i < 10; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        dynamicArray.push_back(i);
        std::cout << "Added: " << i << std::endl;
    }
}

void eraseFirstElement() {
    for (int i = 0; i < 10; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        if (!dynamicArray.empty()) {
            int firstElement = dynamicArray.front();
            dynamicArray.erase(dynamicArray.begin());
            std::cout << "Erased: " << firstElement << std::endl;
        }
    }
}

int main() {
    std::thread t1(addNumbers);
    std::thread t2(eraseFirstElement);

    t1.join();
    t2.join();

    return 0;
}
