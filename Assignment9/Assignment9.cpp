#include <iostream>
#include <chrono>
#include <thread>

class Airport {
public:
    Airport(int numSecurityLines) : securityLines(numSecurityLines) {}

    void processPassenger(int id) {
        // Scanning boarding pass takes 1 minute
        std::this_thread::sleep_for(std::chrono::minutes(1));

        // Doing security check takes 10 minutes
        std::this_thread::sleep_for(std::chrono::minutes(10 / securityLines));

        std::cout << "Passenger " << id << " has completed the process." << std::endl;
    }

private:
    int securityLines;
};

int main() {
    Airport airportWithOneLine(1);
    Airport airportWithTwoLines(2);
    Airport airportWithFourLines(4);

    std::cout << "Processing passengers with 1 security line:" << std::endl;
    for (int i = 1; i <= 4; ++i) {
        airportWithOneLine.processPassenger(i);
    }

    std::cout << "Processing passengers with 2 security lines:" << std::endl;
    for (int i = 1; i <= 4; ++i) {
        airportWithTwoLines.processPassenger(i);
    }

    std::cout << "Processing passengers with 4 security lines:" << std::endl;
    for (int i = 1; i <= 4; ++i) {
        airportWithFourLines.processPassenger(i);
    }

    return 0;
}
