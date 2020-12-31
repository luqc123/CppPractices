#pragma once
#include <stdio.h>

namespace c_language_test {
	void testcase() {
		int c;
		c = getchar();
		while (c != EOF) {
			putchar(c);
			c = getchar();
		}
	}

	//count lines in input
	void testcase2() {
		int c, nl;
		nl = 0;
		while (c = getchar() != EOF) {
			if (c == '\n')
				++nl;
		}
		printf("%d\n", nl);
	}
}
