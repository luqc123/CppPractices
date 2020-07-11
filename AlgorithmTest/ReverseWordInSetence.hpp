#include "interview.hpp"
#include <string>
#include <cstdio>

using namespace std;

void ReverseString(char* pBegin,char* pEnd) {
	while (pBegin < pEnd) {
		char tmp = *pBegin;
		*pBegin = *pEnd;
		*pEnd = tmp;
		pBegin++;
		pEnd--;
	}
}

void ReverseSentence(char* sentence) {
	if (sentence == nullptr) return;
	char* pBegin = sentence;
	char* pEnd = pBegin;
	while (*pEnd != '\0')
		pEnd++;
	--pEnd;

 	ReverseString(pBegin, pEnd);
	pBegin = sentence;
	pEnd = pBegin;
	do {
		if (*pBegin == ' ') {
			++pBegin;
			++pEnd;
		}
		else {
			++pEnd;
		}
		if (*pEnd == ' ' || *pEnd == '\0') {
			ReverseString(pBegin, --pEnd);
			++pEnd;
			pBegin = pEnd;
		}
	} while (*pEnd != '\0');
}

void Test1() {
	char sentence[] = " hello world my name is ";
	cout << sentence << endl;
	ReverseSentence(sentence);
	cout << sentence << endl;
}

