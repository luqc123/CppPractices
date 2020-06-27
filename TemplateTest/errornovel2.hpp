#pragma once

#include <string>
#include <unordered_set>

class Customer {
private:
	std::string name;
public:
	Customer(const std::string& s) : name(s) {}
	std::string getName() const {
		return name;
	}
};
