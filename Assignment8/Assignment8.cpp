#include <iostream>
#include <vector>
#include <future>
#include <chrono>
#include <random>

class RandomNumberGenerator {
public:
    enum TaskType { LIGHT, HEAVY };

    RandomNumberGenerator(TaskType type) : taskType(type) {}

    std::vector<int> generateNumbers() {
        std::vector<int> numbers;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, 1000);

        int count = (taskType == LIGHT) ? 100 : 10000000;
        for (int i = 0; i < count; ++i) {
            numbers.push_back(distribution(gen));
        }

        return numbers;
    }

private:
    TaskType taskType;
};

int main() {
    std::vector<RandomNumberGenerator> generators;
    std::vector<std::future<std::vector<int>>> futures;

    // Allocate 100 RandomNumberGenerators with random task types
    for (int i = 0; i < 100; ++i) {
        RandomNumberGenerator::TaskType type = (std::rand() % 2 == 0) ? RandomNumberGenerator::LIGHT : RandomNumberGenerator::HEAVY;
        generators.emplace_back(type);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Run all generators as async tasks
    for (auto& generator : generators) {
        futures.push_back(std::async(std::launch::async, &RandomNumberGenerator::generateNumbers, &generator));
    }

    // Wait for all tasks to complete
    for (auto& future : futures) {
        future.wait();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time taken to complete all generators: " << duration << " milliseconds" << std::endl;

    return 0;
}
