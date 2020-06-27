#pragma once

#include <string>	
#include <iostream>

using namespace std;

class C {
public:
	C() = default;
	C(C const&) {
		cout << "copy constructor" << endl;
	}
	C(C&&) {
		cout << "move constructor" << endl;
	}

	template<typename T>
	C(T&&) {
		cout << "template constructor" << endl;
	}
};

void TestCase() {
	C x;
	C x2{ x };
	C x3{ move(x) };
	C const c;
	C x4(c);
	C x5{move(c)};
}