#include <cstdio>
#include <string>
#include <iostream>

using namespace std; 

//Ìæ»»¿Õ¸ñÎªXXX
void ReplaceSpace(char string[],int length) {
	if (string == nullptr || length<=0) return;
	int spaceNum = 0;
	int noneSpaceNum = 0;
	char* pBegin = string;
	while (*pBegin != '\0') {
		if (*pBegin == ' ') {
			++spaceNum;
		}
		++noneSpaceNum;
		++pBegin;
	}
}
