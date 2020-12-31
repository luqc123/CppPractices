#pragma once

#include <functional>	
#include <string>
#include <iostream>

void printString(std::string const& s) {
	std::cout << s << "\n";
}
//void printString(std::string s) {
//	std::cout << "string" << "\n";
//	std::cout << s << "\n";
//}

template<typename T>
void printT(T arg) {
	printString(arg);
}

void testcase() {
	std::string s = "hello";
	printT(s); //print s passed by value
	printT(std::cref(s)); //print s passed as if by reference

}
