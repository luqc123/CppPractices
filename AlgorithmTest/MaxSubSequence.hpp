#pragma once
#include <vector>

namespace common {
	int maxSubSum1(const std::vector<int>& a) {
		int maxSum = 0;
		for(int i=0;i<a.size();i++)
			for (int j = i; j < a.size(); j++) {
				int thisSum = 0;
				for (int k = i; k <= j; k++)
					thisSum += a[k];

				if (thisSum > maxSum)
					maxSum = thisSum;
			}
		return maxSum;
	}

	int maxSubSum2(const std::vector<int>& a) {
		int maxSum = 0;
		for (int i = 0; i < a.size(); i++) {
			int thisSum = 0;
			for (int j = i; j < a.size(); j++)
			{
				thisSum += a[j];
				if (thisSum > maxSum)
					maxSum = thisSum;
			}
		}
		return maxSum;
	}

	int maxMultiSum(const std::vector<int>& a) {
		int maxSum = 1,
	}

	int maxSubSum4(const std::vector<int>& a) {
		int maxSum = 0, thisSum = 0;
		for (int i = 0; i < a.size(); i++)
		{
			thisSum += a[i];
			if (thisSum > maxSum)
				maxSum = thisSum;
			else if (thisSum < 0)
				thisSum = 0;
		}
		return maxSum;
	}



	int max3(int elem1, int elem2, int elem3) {
		int maxElem = 0;
		if (elem1 < elem2)
		{
			if (elem2 < elem3)
				maxElem = elem3;
			maxElem = elem2;
			return maxElem;
		}
		if (elem1 < elem3)
			maxElem = elem3;
		maxElem = elem1;
		return maxElem;
	}

	int maxSumRec(const std::vector<int>& a, int left, int right) {
		//base case
		if (left == right)
		{
			if (a[left] > 0)
				return a[left];
			else
				return 0;
		}

		int center = (left + right) / 2;
		int maxLeftSum = maxSumRec(a, left, center);
		int maxRightSum = maxSumRec(a, center + 1, right);

		int maxLeftBorderSum = 0, leftBorderSum= 0;
		for (int i = center; i >= left; i--)
		{
			leftBorderSum += a[i];
			if (leftBorderSum > maxLeftBorderSum)
				maxLeftBorderSum = leftBorderSum;
		}

		int maxRightBorderSum = 0, rightBorderSum = 0;
		for (int i = center + 1; i <= right; i++)
		{
			rightBorderSum += a[i];
			if (rightBorderSum > maxRightBorderSum)
				maxRightBorderSum = rightBorderSum;
		}

		return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
	}


}
