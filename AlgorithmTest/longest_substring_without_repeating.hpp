#include <string>
#include <unordered_map>
/*
*
* leetcode3
* https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/
*/

using namespace std;

namespace array_algorithm {
	int lengthOfLongestString(string s) {
		if (s.length() == 0) return 0;
		if (s.length() == 1) return 1;

		unordered_map<char, int> hashTable;
		int maxLength = 0;
		int currentLength = 0;
		int startIndex = 0;

		for (int i = 0; i < s.length(); i++) {
			if (hashTable.find(s[i]) == hashTable.end()) {
				currentLength++;
				hashTable[s[i]] = i;
			}
			else {
				if (currentLength > maxLength) {
					maxLength = currentLength;
				}
				//下边3行最关键
				startIndex = max(hashTable[s[i]], startIndex);
				currentLength = i - startIndex;
				hashTable[s[i]] = i;
			}
		}
		if (currentLength > maxLength) {
			maxLength = currentLength;
		}
		return maxLength;
	}
}