#include <deque>
#include <iostream>
#include <exception>

using namespace std;

template<typename T>
class QueueWithMax {
public:
	QueueWithMax();
	T max() const;
	void push_back(T);
	void pop_front();
	bool empty() const;
private:
	struct InternalData {
		T number;
		int index;
	};
	deque<InternalData> internalQueue;
	deque<InternalData> internalMaxQueue;
	int currentIndex;
};

template<typename T>
QueueWithMax<T>::QueueWithMax(): currentIndex(0)  {
}

template<typename T>
void QueueWithMax<T>::push_back(T value) {
	InternalData internalData = { value,currentIndex };
	internalQueue.push_back(internalData);
	while (!internalMaxQueue.empty() && value >= internalMaxQueue.back().number)
		internalMaxQueue.pop_back();
	internalMaxQueue.push_back(internalData);
	++currentIndex;
}

template<typename T>
void QueueWithMax<T>::pop_front() {
	if (!empty()) {
		if (internalQueue.front().index == internalMaxQueue.front().index)
			internalMaxQueue.pop_front();
		internalQueue.pop_front();
	}
	else {
		throw std::exception("Queue is empty");
	}
}

template<typename T>
bool QueueWithMax<T>::empty() const {
	return internalQueue.empty();
}

template<typename T>
T QueueWithMax<T>::max() const {
	if (!empty()) {
		return internalMaxQueue.front().number;
	}
	throw std::exception("Queue is empty");
}

void Test(const char* name, QueueWithMax<int> queueWithMax, int expectedMax) {
	cout << name << " Begins:" << endl;
	if (!queueWithMax.empty()) {
		if (queueWithMax.max() == expectedMax)
			cout << "Passed" << endl;
		else
			cout << "Not Passed" << endl;
		cout << name << " End" << endl;
	}
	else {
		throw std::exception("Queue is empty");
	}
}

void Test1() {
	QueueWithMax<int> queue;
	queue.push_back(2);
	//{2}
	Test("Test1", queue, 2);
	queue.push_back(3);
	//{2,3}
	Test("Test2", queue, 3);
	queue.push_back(4);
	//{2,3,4}
	Test("Test3", queue, 4);
	queue.push_back(2);
	//{2,3,4,2}
	Test("Test4", queue, 4);
	queue.push_back(2);
	//{2,3,4,2,2}
	Test("Test5", queue, 4);
	queue.pop_front();
	//{3,4,2,2}
	Test("Test6", queue, 4);
	queue.pop_front();
	//{4,2,2}
	Test("Test7", queue, 4);
	queue.pop_front();
	//{2,2}
	Test("Test8", queue, 2);
	queue.push_back(6);
	//{2,2,6}
	Test("Test8", queue, 6);
	//{2,2,6,5}
	queue.push_back(5);
	Test("Test9", queue, 6);
	queue.pop_front();
	queue.pop_front();
	queue.pop_front();
	//{5}
	Test("Test10", queue, 5);
}

