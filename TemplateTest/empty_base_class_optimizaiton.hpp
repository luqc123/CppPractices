#pragma once
#include <iostream>

namespace ebco {
	class Empty {
		typedef int Int;
	};

	class EmptyTwo : public Empty {};
	class EmptyThree : public EmptyTwo {};
	class NoEmpty : public Empty,public EmptyTwo {};

	void testcase() {
		std::cout << "sizeof(Empty):" << sizeof(Empty) << std::endl;
		std::cout << "sizeof(EmptyTwo):" << sizeof(EmptyTwo) << std::endl;
		std::cout << "sizeof(EmptyThree):" << sizeof(EmptyThree) << std::endl;
		std::cout << "sizeof(NoEmpty):" << sizeof(NoEmpty) << std::endl;
	}
}
