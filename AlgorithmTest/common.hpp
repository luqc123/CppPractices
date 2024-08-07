#include <random>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <tuple>
#include <string>
#include <memory>
#include <iostream>



using namespace std;


namespace common {
	/*
	print container's elements
	*/
	template<typename T>
	void PrintContainers(T& t)
	{
		for (auto elem : t)
			cout << elem << " ";
		cout << endl;
	}

	/*
	generate number int between min and max
	*/
	void GenerateNInts(vector<int>& nvec, int number, int min, int max)
	{
		default_random_engine dre;
		uniform_int_distribution<int> di(min, max);
		for (int i = 0; i < number; i++)
			nvec.push_back(di(dre));
	}

	/*
	generate number int between min and max
	*/
	template<typename Type, int T>
	void GenerateNInts(array<Type, T>& arr, int min, int max)
	{
		assert(T > 0);
		default_random_engine dre(1);
		uniform_int_distribution<int> di(min, max);
		for (int i = 0; i < T; i++)
			arr.at(i) = di(dre);
	}

	/*
	* check vector is distinct or not
	*/
	bool IsDistinct(vector<int>& ivec)
	{
		set<int> coll;
		for (auto i : ivec)
			coll.insert(i);
		if (coll.size() == ivec.size())
			return true;
		else
			return false;
	}

	int gcd(int m, int n) {
		int rem = 0;
		while (n != 0)
		{
			rem = m % n;
			m = n;
			n = rem;
		}
		return m;
	}

	long pow(long x, int n) {
		if (n == 0)
			return 1;
		if (n == 1)
			return x;
		if (n % 2 == 0)
			return pow(x * x, n / 2);
		else
			return pow(x * x, n / 2) * x;
	}

	double probRealPrime(int n) {
		int rel = 0, tot = 0;
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++) {
				tot++;
				if (gcd(i, j) == 1)
					rel++;
			}
		return (double)rel / tot;
	}
}

