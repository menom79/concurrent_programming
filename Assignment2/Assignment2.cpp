#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function to set array elements to random numbers
void setRandomNumbers(int* array, int size) {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < size; ++i) {
        array[i] = std::rand();
    }
}

int main() {
    // Asking the user for the number of elements
    int num_elements;
    std::cout << "Enter the number of elements to allocate: ";
    std::cin >> num_elements;

    if (num_elements <= 0) {
        std::cerr << "Invalid number of elements. Exiting." << std::endl;
        return 1;
    }

    // Allocating an array of numbers
    int* number_array = new int[num_elements];

    // Creating a thread to set array elements to random numbers
    std::thread t(setRandomNumbers, number_array, num_elements);

    // Wait for the thread to finish
    t.join();

    // Printing the contents of the array
    std::cout << "Array contents:" << std::endl;
    for (int i = 0; i < num_elements; ++i) {
        std::cout << number_array[i] << " ";
    }
    std::cout << std::endl;

    // Deallocating the array
    delete[] number_array;

    return 0;
}
