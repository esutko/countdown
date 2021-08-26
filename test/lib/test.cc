#include <iostream>
#include <ios>

#include <vector>
#include <string>

#include <utility>

#include "test.h"

using namespace std;

Test::Test(const string &n) : name(n) {
	cerr << boolalpha << "\033[1m" << "Test: " << name << "\033[0m\n";
}

Test::~Test() {
	if (!success) {
		cerr << "Test failed, " << passed << " out of " << attempted << " assertions passed." << "\n";
	}
}

void Test::description(const string &s) {
	msg = s;
}

void Test::assert(bool b) {
	attempted++;
	if (b) {
		passed++;
	} else {
		cerr << "Assertion #" << attempted << " failed" << "\n";
		if (!msg.empty())
			cerr << msg << "\n";
	}
	success = success && b;
	msg.clear();
}
