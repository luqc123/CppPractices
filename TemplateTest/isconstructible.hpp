#pragma once 

#include <iostream>	

class C {
public:
	C() {} //default constructor has no noexcept
	virtual ~C() = default; //makes C notrivial
};

void testcase() {
	using namespace std;
	cout << boolalpha <<  is_default_constructible_v<C> << "\n";
	cout << boolalpha << is_trivially_default_constructible_v<C> << endl;
	cout << boolalpha << is_nothrow_default_constructible_v<C> << endl;
	cout << boolalpha << is_copy_constructible_v<C> << endl;
	cout << boolalpha << is_trivially_copy_constructible_v<C> << endl;
	cout << is_nothrow_copy_constructible_v<C> << endl;
	cout << is_destructible_v<C> << endl;
	cout << is_trivially_destructible_v<C> << endl;
	cout << is_nothrow_destructible_v<C> << endl;
}