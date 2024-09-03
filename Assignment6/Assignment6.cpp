#include <iostream>
#include <thread>
#include <atomic>
#include <random>

class BankAccount {
public:
    BankAccount(double initialBalance) : balance(initialBalance), operationsCount(0) {}

    void deposit(double amount) {
        double oldBalance = balance.load();
        while (!balance.compare_exchange_weak(oldBalance, oldBalance + amount)) {
            // Retry if the balance was updated by another thread
        }
        operationsCount.fetch_add(1, std::memory_order_relaxed);
    }

    void withdraw(double amount) {
        double oldBalance = balance.load();
        while (!balance.compare_exchange_weak(oldBalance, oldBalance - amount)) {
            // Retry if the balance was updated by another thread
        }
        operationsCount.fetch_add(1, std::memory_order_relaxed);
    }

    double getBalance() const {
        return balance.load(std::memory_order_relaxed);
    }

    void addInterest() {
        if (operationsCount.load(std::memory_order_relaxed) >= 100) {
            double oldBalance = balance.load(std::memory_order_relaxed);
            double interest = oldBalance * 0.0005; // 0.05% interest
            balance.store(oldBalance + interest, std::memory_order_relaxed);
            operationsCount.store(0, std::memory_order_relaxed); // Reset operations count
        }
    }

private:
    std::atomic<double> balance;
    std::atomic<int> operationsCount;
};

void simulateTransactions(BankAccount& account1, BankAccount& account2) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> amountDistribution(1, 100);

    for (int i = 0; i < 100; ++i) {
        double amount = amountDistribution(gen);
        if (i % 2 == 0) {
            account1.deposit(amount);
            account2.withdraw(amount);
        }
        else {
            account2.deposit(amount);
            account1.withdraw(amount);
        }
        account1.addInterest();
        account2.addInterest();
    }
}

int main() {
    BankAccount account1(1000);
    BankAccount account2(1500);

    std::thread t1(simulateTransactions, std::ref(account1), std::ref(account2));
    std::thread t2(simulateTransactions, std::ref(account1), std::ref(account2));

    t1.join();
    t2.join();

    std::cout << "Account 1 Balance: " << account1.getBalance() << std::endl;
    std::cout << "Account 2 Balance: " << account2.getBalance() << std::endl;

    return 0;
}
