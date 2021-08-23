#ifndef ADD_TWO_NUMBERS_HPP
#define ADD_TWO_NUMBERS_HPP
/*
* leetcode 2 两数相加
*/

using namespace std;

namespace array_algorithm {
	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}
	};

	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* result = new ListNode(-1);
		ListNode* current = result;
		int addition = 0;

		while (l1 != nullptr && l2 != nullptr) {
			ListNode* node = new ListNode(0);
			current->next = node;
			int sum = l1->val + l2->val + addition;
			addition = sum / 10;
			node->val = sum % 10;

			l1 = l1->next;
			l2 = l2->next;
			current = current->next;
		}
		while (l1 != nullptr) {
			ListNode* node = new ListNode(0);
			current->next = node;
			int sum = l1->val + addition;
			addition = sum / 10;
			node->val = sum % 10;

			l1 = l1->next;
			current = current->next;
		}
		while (l2 != nullptr) {
			ListNode* node = new ListNode(0);
			current->next = node;
			int sum = l2->val + addition;
			addition = sum / 10;
			node->val = sum % 10;

			l2 = l2->next;
			current = current->next;
		}
		if (addition == 1) {
			ListNode* node = new ListNode(1);
			current->next = node;
		}
		return result->next;
	}

	void addTwoNumbersCase1() {
		ListNode* l1 = new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9))));
		ListNode* l2 = new ListNode(9, new ListNode(9, new ListNode(9)));

		auto result = addTwoNumbers(l1, l2);
	}
}
#endif