#pragma once
#include <type_traits>	
#include <iostream>	

void TestCase() {
	using namespace std;
	cout << boolalpha;

	using MyType = int;
	cout << is_const<MyType>::value << endl;
	using VT = is_const<MyType>::value_type;
	using T = is_const<MyType>::type;

	cout << is_same_v<VT, bool> << endl;
	cout << is_same<T, integral_constant<bool, false>>::value
		<< endl;

}
