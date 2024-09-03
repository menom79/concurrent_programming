#include <iostream>
#include <thread>
#include <mutex>
#include <random>

class BankAccount {
public:
    BankAccount(int initialBalance) : balance(initialBalance) {}

    void deposit(int amount) {
        std::lock_guard<std::mutex> lock(accountMutex);
        balance += amount;
        std::cout << "Deposited: " << amount << ", New Balance: " << balance << std::endl;
    }

    void withdraw(int amount) {
        std::lock_guard<std::mutex> lock(accountMutex);
        if (balance >= amount) {
            balance -= amount;
            std::cout << "Withdrawn: " << amount << ", New Balance: " << balance << std::endl;
        }
        else {
            std::cout << "Insufficient funds for withdrawal: " << amount << std::endl;
        }
    }

    int getBalance() {
        std::lock_guard<std::mutex> lock(accountMutex);
        return balance;
    }

private:
    int balance;
    std::mutex accountMutex;
};

void simulateTransactions(BankAccount& account1, BankAccount& account2) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> amountDistribution(1, 100);

    for (int i = 0; i < 10; ++i) {
        int amount = amountDistribution(gen);
        if (i % 2 == 0) {
            account1.deposit(amount);
            account2.withdraw(amount);
        }
        else {
            account2.deposit(amount);
            account1.withdraw(amount);
        }
    }
}

int main() {
    BankAccount account1(1000);
    BankAccount account2(1500);

    std::thread t1(simulateTransactions, std::ref(account1), std::ref(account2));
    std::thread t2(simulateTransactions, std::ref(account1), std::ref(account2));
    std::thread t3(simulateTransactions, std::ref(account1), std::ref(account2));
    std::thread t4(simulateTransactions, std::ref(account1), std::ref(account2));

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "Account 1 Balance: " << account1.getBalance() << std::endl;
    std::cout << "Account 2 Balance: " << account2.getBalance() << std::endl;

    return 0;
}
