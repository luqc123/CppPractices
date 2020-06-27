#pragma once

#include <iostream>	
#include <vector>
#include <array>

using namespace std;

namespace tree {
	void TestCase1() {
		array<int, 10> a10 = { 1,2,3,4,5,6,7,8,9,10 };
		array<int, 10> b10 = { 1,2,3,4,5,6,7,8,9,10 };
		//error
		//a10.at(11) = 11;
		//a10[11] = 11;
	}

	void f(int n) {
		if (n == 0)
			return;
		cout << "before print n:" << n <<  endl;
		f(n - 1);
		cout << "after print n:" << n <<  endl;
	}

	void TestCase2() {
		f(4);
	}
}