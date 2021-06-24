#include <deque>
#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

vector<int> maxInWindows(const vector<int>& num, unsigned int size) {
	vector<int> maxInWindows;
	if (num.size() >= size && size >= 1) {
		deque<int> index;
		for (int i = 0; i < size; i++) {
			while (!index.empty() && num[i] >= num[index.back()])
				index.pop_back();
			index.push_back(i);
		}

		for (int i = size; i < num.size(); i++) {
			maxInWindows.push_back(num[index.front()]);
			while (!index.empty() && num[i] >= num[index.back()])
				index.pop_back();
			if (!index.empty() && index.front() <= (i - size))
				index.pop_front();
			index.push_back(i);
		}
		maxInWindows.push_back(num[index.front()]);
	}
	return maxInWindows;
}

void Test(const char* testName, const vector<int>& num, int size, const vector<int>& expected) {
	cout << testName << " Begins:" << endl;
	vector<int> result = maxInWindows(num, size);
	vector<int>::const_iterator iterResult = result.begin();
	vector<int>::const_iterator iterExpected = expected.begin();
	while (iterResult < result.end() && iterExpected < expected.end()) {
		if (*iterResult != *iterExpected) {
			break;
		}
		++iterResult;
		++iterExpected;
	}

	if (iterResult == result.end() && iterExpected == expected.end())
		cout << "Passed" << endl;
	else
		cout << "Not Passed" << endl;
	cout << testName << "End" << endl;
}

void Test1() {
	const vector<int> num = { 1,2,3,4,5,6,7,8 };
	int size = 2;
	const vector<int> expected = { 2,3,4,5,6,7,8 };
	Test("Test1 ", num, size, expected);
}

void Test2() {
	const vector<int> num = { -1,-2,-3,4,5,7,8,1 };
	int size = 3;
	const vector<int> expected = { -1,4,5,7,8,8};
	Test("Test2", num, size, expected);
}
