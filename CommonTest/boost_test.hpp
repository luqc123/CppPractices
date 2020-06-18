#pragma once 
#include "stl_header.h"

namespace boost_test {
#include <boost/bind.hpp>
	using namespace boost;

	int f(int a, int b) { return a + b; }
	int g(int a, int b, int c) { return a + b + c; }

	typedef decltype(&f) f_type;
	typedef decltype(&g) g_type;

	void case1() {
		std::cout << bind(f, 1, 2)() << std::endl;
		std::cout << bind(g, 1, 2, 3)() << std::endl;
	}
}