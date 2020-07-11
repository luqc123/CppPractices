#include <stdlib.h>
#include <cstdio>
#include <exception>
#include <vector>
#include <iostream>


namespace array {
	int RandomInRange(int min, int max) {
		int random = rand() % (max - min + 1) + min;
		return random;
	}

	void Swap(int* num1, int* num2) {
		int* tmp = num1;
		num1 = num2;
		num2 = tmp;
	}

	int Partition(int data[], int length, int start, int end) {
		if (data == nullptr || length <= 0 || start < 0 || end >= length) {
			throw new std::exception("Invalid Parameters");
		}

		int index = RandomInRange(start, end);
		Swap(&data[index], &data[end]);

		int small = start - 1;

		for (index = start; index < end; ++index) {
			//找到比data[end]小的数字
			if (data[index] < data[end])
			{
				++small;
				//small到index之间有比data[end]大的数字
				if (small != index) {
					Swap(&data[small], &data[index]);
				}
			}
		}
		//最后的key位置，最终key的左边元素比key小，key的右边元素比key大
		++small;
		Swap(&data[small], &data[end]);
	}
}

namespace binary_tree {
	struct BinaryTreeNode {
		int m_nValue;
		BinaryTreeNode* m_pLeft;
		BinaryTreeNode* m_pRight;
	};

	BinaryTreeNode* CreateBinaryTreeNode(int value) {
		BinaryTreeNode* pNode = new BinaryTreeNode();
		pNode->m_nValue = 0;
		pNode->m_pLeft = nullptr;
		pNode->m_pRight = nullptr;
		return pNode;
	}
	void ConnectTreeNodes(BinaryTreeNode* pParent, BinaryTreeNode* pLeft,BinaryTreeNode* pRight) {
		if (pParent != nullptr) {
			pParent->m_pLeft = pLeft;
			pParent->m_pRight = pRight;
		}
	}
	void PrintTreeNode(const BinaryTreeNode* pNode) {
		if (pNode != nullptr) {
			if (pNode->m_pLeft != nullptr)
				printf("value of its left child is: %d.\n", pNode->m_pLeft->m_nValue);
			else
				printf("left child is nullptr.\n");

			if (pNode->m_pRight != nullptr)
				printf("value of its right child is: %d.\n", pNode->m_pRight->m_nValue);
			else
				printf("right child is nullptr.\n");
		}
		else {
			printf("the node is nullptr.\n");
		}
		printf("\n");
	}

	//中序遍历
	void PrintTree(const BinaryTreeNode* pRoot) {
		PrintTreeNode(pRoot);
		if (pRoot != nullptr) {
			if (pRoot->m_pLeft != nullptr) {
				PrintTreeNode(pRoot->m_pLeft);
			}
			if (pRoot->m_pRight != nullptr) {
				PrintTreeNode(pRoot->m_pRight);
			}
		}
	}
	void DestroyTree(BinaryTreeNode* pRoot) {
		if (pRoot != nullptr) {
			BinaryTreeNode* pLeft = pRoot->m_pLeft;
			BinaryTreeNode* pRight = pRoot->m_pRight;
			
			delete pRoot;
			pRoot = nullptr;

			DestroyTree(pLeft);
			DestroyTree(pRight);
		}
	}
}

namespace list {
	struct ListNode {
		int m_nValue;
		ListNode* m_pNext;
	};

	ListNode* CreateListNode(int value) {
		ListNode* node = new ListNode();
		node->m_nValue = 0;
		node->m_pNext = nullptr;

		return node;
	}

	void ConnectionNodes(ListNode* pCurrent, ListNode* pNext) {
		if (pCurrent == nullptr) {
			printf("Error to connect two node\n");
			exit(1);
		}
		pCurrent->m_pNext = pNext;
	}
	void PrintListNode(ListNode* node) {
		if (node == nullptr) {
			printf("the node is nullptr\n");
		}
		else {
			printf("The key in node is %d\n", node->m_nValue);
		}
	}
	void PrintList(ListNode* pHead) {
		printf("PrintList starts.\n");
		ListNode* pNode = pHead;
		while (pNode != nullptr) {
			printf("%d\t", pNode->m_nValue);
			pNode = pNode->m_pNext;
		}
		printf("PrintList ends.\n");
	}
	void DestroyList(ListNode* pHead) {
		ListNode* pNode = pHead;
		while (pNode != nullptr) {
			pHead = pHead->m_pNext;
			delete pNode;
			pNode = pHead;
		}
	}
	void AddtoTail(ListNode** pHead, int value) {
		ListNode* pNew = new ListNode();
		pNew->m_nValue = value;
		pNew->m_pNext = nullptr;

		if (*pHead == nullptr)
		{
			*pHead = pNew;
		}
		else
		{
			ListNode* pNode = *pHead;
			while (pNode->m_pNext != nullptr)
				pNode = pNode->m_pNext;

			pNode->m_pNext = pNew;
		}
	}
	void RemoveNode(ListNode** pHead, int value) {
		if (pHead == nullptr || *pHead == nullptr)
			return;

		ListNode* pToBeDeleted = nullptr;
		if ((*pHead)->m_nValue == value)
		{
			pToBeDeleted = *pHead;
			*pHead = (*pHead)->m_pNext;
		}
		else
		{
			ListNode* pNode = *pHead;
			while (pNode->m_pNext != nullptr && pNode->m_pNext->m_nValue != value)
				pNode = pNode->m_pNext;

			if (pNode->m_pNext != nullptr && pNode->m_pNext->m_nValue == value)
			{
				pToBeDeleted = pNode->m_pNext;
				pNode->m_pNext = pNode->m_pNext->m_pNext;
			}
		}

		if (pToBeDeleted != nullptr)
		{
			delete pToBeDeleted;
			pToBeDeleted = nullptr;
		}
	}
}

namespace string_util {
	void Reverse(char* pBegin, char* pEnd) {
		if (pBegin == nullptr || pEnd == nullptr)
			return;
		while (pBegin < pEnd) {
			char* tmp = pBegin;
			pBegin = pEnd;
			pEnd = tmp;

			pBegin++;
			pEnd--;
		}
	}
}

namespace tree {
	struct TreeNode {
		int m_nValue;
		std::vector<TreeNode*> m_vChildren;
	};

	TreeNode* CreateTreeNode(int value) {
		TreeNode* pNode = new TreeNode();
		pNode->m_nValue = value;
		return pNode;
	}
	void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild) {
		if (pParent != nullptr) {
			pParent->m_vChildren.push_back(pChild);
		}
	}
}
