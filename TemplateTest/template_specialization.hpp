#ifndef TEMPLATE_SPECIALIZATION_H
#define TEMPLATE_SPECIALIZATION_H

#include <iostream>
#include <vector>
using namespace std;

template<class T, class U>
class SmartPtr {
	void Fun() {}
};

template<class U>
class SmartPtr<std::vector<int>, U> {};

template<>
void SmartPtr<std::vector<char>, int>::Fun() {}

//error:member function can not partial specialization 
//template<class U>
//void SmartPtr<std::vector<char>,U>::Fun(){}

template<class T>
class Widget {
	void Fun() {}
};

template<>
void Widget<char>::Fun() {
	cout << "Widget<char>::Fun()" << endl;
}

#endif

