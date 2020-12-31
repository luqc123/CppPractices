#pragma once
#include "stl_header.h"

namespace priority_queue_test {
	void testcase() {
		using namespace std;
		int ia[9] = { 0,1,2,3,4,8,5,3,5 };
		priority_queue<int> ipq(ia, ia + 9);
		cout << "priority_queue.size()= " << ipq.size() << endl;
		//priority_queue have no iterator 
		//can not use for(auto i : ipq)
		for (int i = 0; i < ipq.size(); ++i) {
			cout << ipq.top() << " ";
		}
		cout << endl;

		while (!ipq.empty()) {
			cout << ipq.top() << " ";
			ipq.pop();
		}
		cout << endl;
	}
}
