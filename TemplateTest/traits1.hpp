#pragma once 

#include <type_traits>	
#include <iostream>

namespace traits1 {

	void testcase() {
		using namespace std;
		int i = 4;
		add_const<int>::type c = i; //c is int const
		add_const_t<int> c14 = i; //since c++14
		static_assert(is_const<decltype(c)>::value, "c should be const");

		cout << boolalpha << endl;
		cout << is_same<decltype(c), int const>::value << endl;
		cout << is_same_v<decltype(c), const int> << endl;
		if (is_same<decltype(c), int const>{}) {
			cout << "same" << endl;
		}
	}
}