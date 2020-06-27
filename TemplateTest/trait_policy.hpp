#pragma once
#include <iostream>	

namespace trait_policy {
	template <typename T>
	inline T accum1(T const* beg, T const* end) {
		T total = T();
		while (beg != end) {
			total += *beg;
			++beg;
		}
		return total;
	}

	template<typename T>
	class AccumulateTraits;

	template<>
	class AccumulateTraits<char> {
	public:
		typedef int Acct;
		static Acct const zero = 0;
	};

	template<>
	class AccumulateTraits<short> {
	public:
		typedef int Acct;
		static Acct const zero = 0;
	};

	template<>
	class AccumulateTraits<int> {
	public:
		typedef long Acct;
		static Acct const zero = 0;
	};

	template<>
	class AccumulateTraits<unsigned int> {
	public:
		typedef unsigned long Acct;
		static Acct const zero = 0;
	};

	template<>
	class AccumulateTraits<float> {
	public:
		typedef double Acct;
		static Acct const zero;
	};

	typename AccumulateTraits<float>::Acct const AccumulateTraits<float>::zero = 0.0;

	template<typename T>
	inline 
		typename AccumulateTraits<T>::Acct accum2(T const* beg,
			T const* end) {
		typedef typename AccumulateTraits<T>::Acct AcctT;
		AcctT total = AccumulateTraits<T>::zero;
		while (beg != end) {
			total += *beg;
			beg++;
		}
		return total;
	}
}
