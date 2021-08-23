/*
* Given two array X and Y. Find a pair of elements (xi, yi) such
that xi∈ X and yi∈ Y where xi+yi=value
*/
#include "..\CommonTest\stl_header.h"
#include "common.hpp"

//array 相关的算法题

using namespace std;

namespace algorithm_array
{
	void testcase()
	{
		array<int, 5> arr1 = { 1,5,3,2,4};
		sort(arr1.begin(), arr1.end(), greater());
		common::PrintContainers(arr1);

		vector<int> nums = {};
		common::GenerateNInts(nums, 10, 1, 100);
		sort(nums.begin(), nums.end());
		common::PrintContainers(nums);

		array<int, 10> arr2;
		common::GenerateNInts(arr2, 1, 100);
		sort(arr2.begin(), arr2.end(), less());
		common::PrintContainers(arr2);
		sort(arr2.data(), arr2.data() + arr2.size(), greater());
		common::PrintContainers(arr2);
	}

	template<int Size1,int Size2>
    pair<int, int> find_pairs(array<int, Size1> arr1, array<int, Size2> arr2, int sum)
	{
		assert(Size1 > 0 && Size2 > 0);
		map<int, bool> m1;
		map<int, bool> m2;
		for (auto& i : arr1)
			m1.insert(make_pair(i, true));
		for (auto i : arr2)
			m2.insert(make_pair(i, true));

		pair<int, int> result = make_pair(-1, -1);

		for (auto& i : arr1)
		{
			if (m1[i] && m2[sum - i])
			{
				result.first = i;
				result.second = sum - i;
				return result;
			}
		}
		return result;
	}

	void testcase1()
	{
		array<int, 10> arr1;
		array<int, 20> arr2;
		common::GenerateNInts(arr1, 1, 20);
		common::GenerateNInts(arr2, 1, 20);

		common::PrintContainers(arr1);
		common::PrintContainers(arr2);

		auto result = find_pairs(arr1, arr2, 20);

		if (result.first != -1 && result.second != -1)
			cout << result.first << " " << result.second << endl;
	}
}
