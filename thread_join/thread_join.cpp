#include <iostream>
#include <thread>

using namespace std;

void runningNumber()
{
	cout << "runningNumber: entering\n";
	const auto id = this_thread::get_id();
	for (int i = 0; i < 15; ++i)
	{
		cout << "runningNumber: thread id: " << id;
		cout << ", i=" << i << "\n";
	}

	cout << "runningNumber: leaving\n";
}


int main()
{
	// create a thread
	thread t1(runningNumber);
	cout << "main: started thread t1\n";

	// t1.detach()
	if (t1.joinable())
	{
		t1.join();
	}

	// all done here
	cout << "Hello World!\n";
}

