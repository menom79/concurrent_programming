#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int progress = 0; // Represents the progress of the task in percentage

void workerThread() {
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate a long-running task

        // Update progress and notify main thread
        std::unique_lock<std::mutex> lock(mtx);
        progress += 20;
        std::cout << "Worker thread: " << progress << "% completed." << std::endl;
        lock.unlock();
        cv.notify_one();
    }
}

int main() {
    std::thread worker(workerThread);

    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        // Wait for the worker thread to complete 20% of the task
        cv.wait(lock, [&] { return progress >= (i + 1) * 20; });
        std::cout << "Main thread: " << progress << "% completed." << std::endl;
    }

    worker.join();
    std::cout << "Worker thread completed." << std::endl;

    return 0;
}
