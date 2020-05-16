#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

namespace smartptr {
	//basic use
	void TestCase1() {
		shared_ptr<string> pMike(new string("mike"));
		shared_ptr<string> pKaka(new string("kaka"));
		shared_ptr<string> pManPeng = make_shared<string>("ManPeng");
		//shared_ptr<string> pJohn = new string("John");
		shared_ptr<string> pJohn{ new string("John") };

		cout << "use_count:" << pMike.use_count() << endl;

		(*pMike)[0] = 'N';
		pKaka->replace(0, 1, "K");

		cout << "use_count:" << pMike.use_count() << endl;
		
		vector<shared_ptr<string>> whoMadeCoffee;
		whoMadeCoffee.push_back(pMike);
		whoMadeCoffee.push_back(pKaka);
		whoMadeCoffee.push_back(pMike);
		whoMadeCoffee.push_back(pKaka);
		whoMadeCoffee.push_back(pJohn);
		whoMadeCoffee.push_back(pManPeng);

		*pMike = "MikeMike";

		for (auto ptr : whoMadeCoffee)
			cout << *ptr << " ";
		cout << endl;

		cout << "use_count:" << whoMadeCoffee[0].use_count() << endl;
	}

    //basic deleter
	void TestCase2() {

		int times = 0;
		shared_ptr<string> pMike(new string("nico"), [&times](string* p) {
			cout << "delete " << ++times << "s " << *p << endl;
			delete p;
			});
		vector<shared_ptr<string>> whoMadeCoffee;
		whoMadeCoffee.push_back(pMike);
		whoMadeCoffee.push_back(pMike);
		whoMadeCoffee.push_back(pMike);
	}

    //multi deleter for shared_ptr unique_ptr
	void TestCase3() {
		shared_ptr<int> p(new int[10], [](int* p) {
			delete[] p;
			});
		shared_ptr<int[]> p1(new int[10]);
		unique_ptr<int[]> p2(new int[10]);
		unique_ptr<int, void(*)(int*)> p3(new int[10], [](int* p) {
			delete[] p;
			});
	}
	class FileDeleter {
	};
}
