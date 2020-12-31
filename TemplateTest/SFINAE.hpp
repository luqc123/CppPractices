#pragma once 
#include <iostream>
using namespace std;

template<int I> struct X {};
template<template<class T> class> struct Z{};
template<class T>
void f(typename T::Y*) {}
template<class T>
void g(X<T::N>*) {}
template<class T>
void h(Z<T::template TT>*){}
struct A {};
struct B { int Y; };	
struct C { typedef int N; };
struct D { typedef int TT; };
struct B1 { typedef int Y; };
struct C1 { static const int N = 0; };
struct D1 {
template <typename T>
struct TT {}; 
};
template<class T,T> struct S{};
//template<class T> int ff(S<T, T()>*);
struct XX {};
template<class T, T*> int fff(int);
struct Y { Y(XX) {}; };
template<class T>
auto ffff(T t1, T t2)->decltype(t1 + t2){}
XX ffff(Y, Y){
	return XX();
}
void testcase() {
	//f<A>(0);
	//f<B>(0);
	//g<C>(0);
	//h<D>(0);
	f<B1>(0);
	g<C1>(0);
	h<D1>(0);
	//ff<X>(0);
	//fff<int, 1>(0);
	XX x1, x2;
	XX x3 = ffff(x1, x2);
 }

void test(...) {
	cout << "catch all overload called.\n";
}
template<class C,class F>
auto test(C c, F f) ->decltype((void)(c.*f)()) {
	cout << "reference overload called\n";
}
template<class C,class F>
auto test(C c, F f) ->decltype((void)(c->*f)()) {
	cout << "pointer overload called\n";
}

struct Test { void f() {}; };

void testcase2() {
	Test t;
	test(t, &Test::f);
	test(&t, &Test::f);
	test(32, 1111);
}


