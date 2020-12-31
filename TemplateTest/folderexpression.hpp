#pragma once 
#include <iostream>

template<class ... T>
decltype(auto) difference(T ... args) {
	return (... - args);
}

void testcase() {
	std::cout << difference(5, 2, 1) << "\n";
}