#pragma once 
#include <iostream>

using namespace std;

namespace duo {

	template<typename A, typename B>
	class Duo {
	private:
		typedef A T1;
		typedef B T2;
		T1 t1;
		T2 t2;
	public:
		enum { N = 2 };
	public:
		Duo() : t1(), t2() {}
		Duo(T1 const& t1, T2 const& t2) : t1(t1), t2(t2) {}
		template<typename U1, typename U2>
		Duo(Duo<U1, U2> const& duo) : t1(duo.one()), t2(duo.two()) {}
		template<typename U1, typename U2>
		Duo<T1, T2>& operator=(Duo<U1, U2> const& d) {
			t1 = d.t1;
			t2 = d.t2;
			return *this;
		}
		T1& one() { return t1; }
		const T1& one() const { return t1; }
		T2& two() { return t2; }
		const T2& two() const { return t2; }
	};

	template<typename T1, typename T2>
	Duo<T1, T2> make_duo(const T1& t1, const T2& t2) {
		return Duo<T1, T2>(t1, t2);
	}

	template<typename T1, typename T2, typename U1, typename U2>
	inline bool operator==(const Duo<T1, T2>& d1, const Duo<U1, U2>& d2) {
		return (d1.one() == d2.one()) && (d2.two() == d2.two());
	}
	template<typename T1, typename T2, typename U1, typename U2>
	inline bool operator != (const Duo<T1, T2>& d1, const Duo<U1, U2>& d2) {
		return !(d1 == d2);
	}

	template<typename A, typename B, typename C>
	class Duo<A, Duo<B, C>> {
	private:
		typedef A T1;
		typedef Duo<B, C> T2;
		T1 t1;
		T2 t2;
	public:
		enum { N = 1 + Duo<B, C>::N };
	public:
		Duo() : t1(), t2() {}
		Duo(T1 const& t1, T2 const& t2) : t1(t1), t2(t2) {}
		template<typename U1, typename U2>
		Duo(Duo<U1, U2> const& duo) : t1(duo.one()), t2(duo.two()) {}
		template<typename U1, typename U2>
		Duo<T1, T2>& operator=(Duo<U1, U2> const& d) {
			t1 = d.t1;
			t2 = d.t2;
			return *this;
		}
		T1& one() { return t1; }
		const T1& one() const { return t1; }
		T2& two() { return t2; }
		const T2& two() const { return t2; }
	};

	template<typename A>
	class Duo<A, void> {
	public:
		typedef A T1;
		typedef void T2;
		enum { N = 1 };
	private:
		T1 t1;
	public:
		Duo() :t1() {}
		Duo(T1 const& t1) : t1(t1) {}
		T1& const one() const { return t1; }
		T1& one() { return t1; }
		void two() {}
		void two() const {}
	};

	void testcase1() {
		//Duo<int, int> d1 = make_duo(1, 2);
		//Duo<long, long> d2 = make_duo(1, 2);
		//Duo<long, long> d3(d2);
		//Duo<long, long> d4(d1);
		//cout << boolalpha << (d1 == d2) << endl;
		//cout << boolalpha << (d3 == d4) << endl;
		//cout << d1.one() << endl;
		//cout << d1.two() << endl;
	}
}