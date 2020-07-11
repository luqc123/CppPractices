#pragma once 
#include <iostream>	
#include <string>

template<int M,int K,int S>
struct Unit {
	enum { m = M, kg = K, s = S };
};

using M = Unit<1, 0, 0>;     //m
using Kg = Unit<0, 1, 0>;    //kg
using S = Unit<0, 0, 1>;     //s
using MpS = Unit<1, 0, -1>;  //m/s
using MpS2 = Unit<1, 0, -2>; //m/s*s

template<typename U1,typename U2>
struct Uplus {
	using type = Unit<U1::m + U2::m, U1::kg + U2::kg, U1::s + U2::s>;
};

template<typename U1,typename U2>
using Unit_Plus = typename Uplus<U1, U2>::type;

template<typename U1,typename U2>
struct Uminus {
	using type = Unit<U1::m - U2::m, U1::kg - U2::kg, U1::s - U2::s>;
};

template<typename U1,typename U2>
using Unit_Minus = typename Uminus<U1, U2>::type;

template<typename U>
struct Quantity {
	double val;
	explicit Quantity(double d):val(d){}
};

template<typename U>
Quantity<U> operator-(Quantity<U> q1, Quantity<U> q2) {
	return Quantity<U>{q1.val - q2.val};
}
template<typename U>
Quantity<U> operator+(Quantity<U> q1, Quantity<U> q2) {
	return Quantity<U>{q1.val + q2.val};
}
template<typename U>
Quantity<U> operator+(Quantity<U> q1, double d) {
	return Quantity<U>{q1.val + d};
}
template<typename U>
Quantity<U> operator+(double d, Quantity<U> q1) {
	return Quantity<U>{q1.val + d};
}

template<typename U1,typename U2>
Quantity<Unit_Plus<U1, U2>> operator*(Quantity<U1> q1, Quantity<U2> q2) {
	return Quantity<Unit_Plus<U1, U2>>{q1.val* q2.val};
}
template<typename U1,typename U2>
Quantity<Unit_Minus<U1, U2>> operator/(Quantity<U1> q1, Quantity<U2> q2) {
	return Quantity<Unit_Minus<U1, U2>>{q1.val / q2.val};
}

//iteral constant
Quantity<M> operator"" m(long double d) { return Quantity<M>{static_cast<double>(d)}; }
std::string operator"" s(const char* p, size_t n) {
	return std::string{ p,n };
}

void TestCase() {
	Quantity<M> x{ 10.5 };
	Quantity<S> y{ 2 };
	//Quantity<MpS> s = 7;
	"hello"s;
}
