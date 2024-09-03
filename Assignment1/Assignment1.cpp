#include <iostream>
#include <thread>
#include <vector>

void runLoop(int thread_id, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        std::cout << "Thread " << thread_id << " - Iteration " << i << std::endl;
    }
}

int main() {
    // Get the number of hardware threads (logical processors)
    unsigned int num_threads = std::thread::hardware_concurrency();

    if (num_threads == 0) {
        std::cerr << "Unable to detect the number of logical processors." << std::endl;
        return 1; // Error exit
    }

    // Create a vector to store thread objects
    std::vector<std::thread> threads;

    // Define the number of iterations each thread should run
    int iterations_per_thread = 1000;

    // Create and launch threads
    for (unsigned int i = 0; i < num_threads; ++i) {
        threads.emplace_back(runLoop, i, iterations_per_thread);
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
