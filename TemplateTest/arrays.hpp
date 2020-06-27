#pragma once
#include <iostream>

template<typename T>
struct MyClass;

template<typename T,std::size_t SZ>
struct MyClass<T[SZ]> {
	static void print() {
		std::cout << "print for T[" << SZ << "]\n";
	}
};

template<typename T, std::size_t SZ> 
struct MyClass<T(&)[SZ]> {
	static void print() {
		std::cout << "print for T(&)[" << SZ << "]\n";
	}
};

template<typename T>
struct MyClass<T[]> {
	static void print() {
		std::cout << "print for T[]" << "\n";
	}
};

template<typename T>
struct MyClass<T(&)[]> {
	static void print() {
		std::cout << "print for T(&)[]" << "\n";
	}
};

template<typename T>
struct MyClass<T*> {
	static void print() {
		std::cout << "print for T*" << "\n";
	}
};

template<typename T1,typename T2,typename T3>
void foo(int a1[7],
	int a2[],
	int(&a3)[42],  //reference to array of known
	int(&x0)[],   //reference to array of unkown
	T1 x1,         //passing by value decays
	T2& x2, T3&& x3//passsing by reference
) {
	MyClass<decltype(a1)>::print(); //using MyClass<T*>
	MyClass<decltype(a2)>::print(); //using MyClass<T*>
	MyClass<decltype(a3)>::print(); //using MyClass<T(&)[SZ]>
	MyClass<decltype(x0)>::print(); //using MyClass<T(&)[]>
	MyClass<decltype(x1)>::print(); //using MyClass<T*>
	MyClass<decltype(x2)>::print(); //using MyClass<T(&)[]>
	MyClass<decltype(x3)>::print(); //using MyClass<T(&)[]>
}

void TestCase() {
	int a[42];
	MyClass<decltype(a)>::print();

	extern int x[];
	MyClass<decltype(x)>::print();
	foo(a, a, a, x, x, x, x);
}

int x[] = { 0,8,15 };
