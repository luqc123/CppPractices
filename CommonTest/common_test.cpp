#include "stl_header.h"
#include "tuple_test.hpp"

using namespace std;
using namespace tuple_test;

int main()
{
	//testcase1();
	array<int, 10> arr1;
	cout << arr1[9] << endl;
	array<int, 10> arr2 = {};
	cout << arr2[9] << endl;
	array<int, 10> arr3(arr2);
	array<int, 11> arr4({ 0 });
	array<int, 11> arr5 = { 1,2,3 };


	array<int, 0> arr6;
	cout << arr6.size() << endl;
	cout << boolalpha << ((arr6.begin()) == (arr6.end())) << endl;
	//cout << boolalpha << (arr6.front() == arr6.back()) << endl;
	cout << arr6.data() << endl;
	array<int, 5> arr7({ 1,2,3,4,6 });
	arr7.fill(11);
	for (auto& i : arr7)
		cout << i << endl;

	try
	{
		arr7.at(10);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}
