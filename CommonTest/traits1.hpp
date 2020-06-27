#pragma once 
#include <iostream>
#include <type_traits>	
#include <typeinfo>

using namespace std;

void TestCase() {
	typedef std::conditional<true, int, double>::type Type1;
	typedef std::conditional<false, int, double>::type Type2;

	typedef std::conditional<sizeof(int) >= sizeof(double), int, double>::type Type3;

	std::cout << typeid(Type1).name() << "\n";
	std::cout << typeid(Type2).name() << "\n";
	std::cout << typeid(Type3).name() << "\n";
}

void TestCase2() {
	cout << boolalpha << is_pointer<int*>::value << endl;
}

struct X {
	void operator()(int x) {
		cout << "X" << " " << x << endl;
	}
};
struct Y {
	void operator()(int x) {
		cout << "Y" << " " << x << endl;
	}
};

void TestCase3() {
	conditional_t<(sizeof(int) > 4), X, Y>{}(7);
	conditional<(sizeof(int) > 4), X, Y>::type{}(6);
	X{}(7);
	conditional < (is_polymorphic<X>{}), X, Y > ::type{}(7);
}

class Nil {};

template<int I, typename T1=Nil,typename T2=Nil,typename T3=Nil,typename T4=Nil>
struct Select;

template<int I, typename T1=Nil,typename T2=Nil,typename T3=Nil,typename T4=Nil>
using select = typename Select<I, T1, T2, T3, T4>::type;

template<typename T1,typename T2,typename T3,typename T4>
struct Select<0, T1, T2, T3, T4> { using type = T1; };
template<typename T1,typename T2,typename T3,typename T4>
struct Select<1, T1, T2, T3, T4> { using type = T2; };
template<typename T1,typename T2,typename T3,typename T4>
struct Select<2, T1, T2, T3, T4> { using type = T3; };
template<typename T1,typename T2,typename T3,typename T4>
struct Select<3, T1, T2, T3, T4> { using type = T4; };

namespace variant {
	template<unsigned N,typename ... Cases>
	struct select;
	template<unsigned N,typename T,typename ... Cases>
	struct select<N,T,Cases...>:select<N-1,Cases...>{};
	template<typename T,typename ... Cases>
	struct select<0, T, Cases...> {
		using type = T;
	};
}

constexpr int fac(int i) {
	return (i < 2) ? 1 : i*fac(i - 1);
}

void TestCase4() {
	constexpr int x = fac(6);
	cout << x << endl;
}
