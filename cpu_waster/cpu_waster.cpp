#include <iostream>
#include <thread>
#include <chrono>

using namespace std;


void cpu_waster()
{
    //print process and thread id
    cout << "cpu_waster process id: " << _getpid() << "\n";
    cout << "cpu_waster process id: " << this_thread::get_id() << "\n";

    // infinite loop, just doing nothing
    while (true)
    {
    }
}


int main()
{
    //print process and thread id
    cout << "cpu_waster process id: " << _getpid() << "\n";
    cout << "cpu_waster process id: " << this_thread::get_id() << "\n";
    cout << "Hardware concurrency: " << thread::hardware_concurrency() << "\n";

    // create 2 threads, give cpu_waster as parameter
    thread thread1(cpu_waster);
    thread thread2(cpu_waster);

    while (true)
    {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "running ...\n";
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
