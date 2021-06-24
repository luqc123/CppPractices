#pragma once

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

namespace time_test {

#ifdef __cplusplus
	extern "C" {
#endif

		void testcase() {
			char buf[32];
			clock_t tc = clock();
			struct tm ts1;
			time_t tt1, tt2;
			static const char* dstr = "Sun Dec 2 06:55:15 1979\n";

			tt1 = time(&tt2);
			assert(tt1 == tt2);

			ts1.tm_sec = 15;
			ts1.tm_min = 55;
			ts1.tm_hour = 6;
			ts1.tm_mday = 2;
			ts1.tm_mon = 11;
			ts1.tm_year = 79;
			ts1.tm_isdst = -1;
			tt1 = mktime(&ts1);

			assert(ts1.tm_wday == 0);
			assert(ts1.tm_yday == 335);
		}

#ifdef __cplusplus
	}
#endif 
}