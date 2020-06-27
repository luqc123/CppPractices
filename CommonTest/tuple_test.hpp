#pragma once 
#include <tuple>
#include <iostream>
using namespace std;

namespace tuple_test {
	void TestCase() {
		auto t = make_tuple<int, int, int>(1, 2, 3);
		cout << get<0>(t) << endl;
		cout << get<1>(t) << endl;
		cout << get<2>(t) << endl;
	}
}