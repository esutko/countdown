#ifndef TEST_HEADER_INCLUDED
#define TEST_HEADER_INCLUDED

#include <iostream>

#include <string>
#include <vector>

#include <utility>

class Test {
public:
	Test() = delete;
	Test(const Test &) = default;
	Test &operator=(const Test &) = default;
	~Test();
	
	Test(const std::string &);

	void description(const std::string &);
	
	void assert(bool b);

	template <typename T>
	void assertEq(const T &obj1, const T &obj2) {
		bool equal = obj1 == obj2;
		assert(equal);
		if (!equal) {
			std::cerr << "Expected \"" << obj1 << "\"\n";
			std::cerr << "Got      \"" << obj2 << "\"\n";
		}
	}
private:
	std::string name;
	std::string msg;
	bool success = true;
	int attempted = 0;
	int passed = 0;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
	for (size_t idx = 0; idx < v.size(); idx++) {
		out << v[idx];
		if (idx != v.size() - 1) out << ",";
	}

	return out;
}

template <typename T, typename U>
std::ostream &operator<<(std::ostream &out, const std::pair<T, U> &p) {
	return out << "(" << p.first << ", " << p.second << ")";  
}
#endif
