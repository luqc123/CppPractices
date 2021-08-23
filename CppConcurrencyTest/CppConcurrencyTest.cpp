//C++ Concurrency in Action Test

#include <iostream>
#include <thread>
#include <barrier>

using namespace std;

class work {
public:
	void operator()() {
		cout << "work" << endl;
	}
};

int main()
{
	thread t1([]() {
		cout << "hello concurrent world" << endl;
		});
	t1.join();
	thread t2(work{});
	t2.join();
}
