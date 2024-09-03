#include <iostream>
#include <thread>

using namespace std;

void runningNumber(int count, const string& message)
{
	for (int i = 0; i = count; ++i)
	{
		cout << message << ", i=" << i << "\n";
	}
}

void increaseNumber(int& number, int count)
{
	while (--count)
	{
		++number;
		cout << "increaseNumber: " << number << "\n";
	}
}


int main()
{
	int count = 100;
	thread t1(runningNumber, 100, "hello from main");
	if (t1.joinable()) t1.join();

	int number = 0;
	thread t2(increaseNumber, ref(number), 100);
	if (t2.joinable()) t2.join();
	cout << "t2 done, number=" << number << "\n";
}

