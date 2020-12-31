#pragma once

#include <string>
#include <map>
#include <algorithm>	

void testcase() {
	std::map<std::string, double> coll;
	//error
	//auto pos = std::find_if(coll.begin(), coll.end(),
//		[](std::string const& s) {
//			return s != "";
//		});

	auto pos = std::find_if(coll.begin(), coll.end(),
		[](std::pair<std::string,double> const& p) {
			return p.first != "";
		});
}