#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

class Sensor {
public:
    Sensor() : stopThread(false) {
        std::srand(std::time(0));
    }

    void start(std::promise<int>& promise) {
        sensorThread = std::thread([this, &promise] {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> sensorValues(0, 4095);

            while (!stopThread) {
                int value = sensorValues(gen);
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate sensor reading delay
                if (value > 4000) {
                    std::cout << "Sensor Value: " << value << std::endl;
                    promise.set_value(value);
                    break; // Break the loop after sending the value over 4000
                }
            }
            });
    }

    void stop() {
        stopThread = true;
        if (sensorThread.joinable()) {
            sensorThread.join();
        }
    }

private:
    std::thread sensorThread;
    std::atomic<bool> stopThread;
};

class SensorReader {
public:
    SensorReader() {
        for (int i = 0; i < 4; ++i) {
            sensors.push_back(std::make_unique<Sensor>());
        }
    }

    void start() {
        std::vector<std::future<int>> futures;
        for (auto& sensor : sensors) {
            std::promise<int> promise;
            futures.push_back(promise.get_future());
            sensor->start(promise);
        }

        // Wait for the result and print it
        for (auto& future : futures) {
            int sensorValue = future.get();
            std::cout << "Sensor value over 4000: " << sensorValue << std::endl;
        }
    }

    void stop() {
        for (auto& sensor : sensors) {
            sensor->stop();
        }
    }

private:
    std::vector<std::unique_ptr<Sensor>> sensors;
};

int main() {
    SensorReader sensorReader;
    sensorReader.start();

    std::cout << "Press enter to stop the SensorReader..." << std::endl;
    std::cin.get(); // Wait for user input

    sensorReader.stop();

    return 0;
}
