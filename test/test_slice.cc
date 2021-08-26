#include <vector>

#include <exception>

#include "lib/test.h"
#include "../src/slice.h"

#include "test_slice.h"

using namespace std;

void test_slice_indexing() {
	Test test{"slice indexing"};
	
	vector<int> v{2, 3, 5, 7};
	Slice<int> s{v};

	test.description("front gives first element");
	test.assertEq(2, s.front());

	test.description("back gives last element");
	test.assertEq(7, s.back());

	test.description("index operator");
	test.assertEq(5, s[2]);

	test.description("index operator on a subsequence");
	Slice<int> s2{v.begin() + 1, v.end() - 1};
	test.assertEq(5, s2[1]);

	test.description("out of range error");
	bool caught = false;
	try {
		s[100];
	}
	catch (const out_of_range &e) {
		caught = true;
	}
	test.assert(caught);
}


void test_slice_size() {
	Test test{"slice size"};

	vector<int> v{2, 3, 5, 7};
	Slice<int> s{v};

	test.description("empty method");
	test.assert(!s.empty());

	test.description("empty on subsequence");
	Slice<int> s2{v.begin() + 2, v.end() - 2};
	test.assert(s2.empty());

	test.description("empty on weird subsequence");
	Slice<int> s3{v.begin() + 2, v.end() - 3};
	test.assert(s2.empty());

	test.description("size method");
	test.assertEq(4ul, s.size());
}


void test_slice_iteration() {
	Test test{"slice iteration"};

	vector<int> v{2, 3, 5, 7};
	Slice<int> s{v};
	auto start = s.begin();
	auto stop = s.end();

	test.description("begin points to first element");
	test.assertEq(2, *start);

	test.description("iterators traverse the whole slice");
	vector<int> results;
	for(auto iter = start; iter != stop; ++iter)
		results.push_back(*iter);
	test.assertEq(v, results);

	test.description("iterators traverse subsequence");
	Slice<int> s2{v.begin() + 1, v.end() - 1};
	results.clear();
	for(auto iter = s2.begin(); iter != s2.end(); ++iter)
		results.push_back(*iter);
	test.assertEq(vector<int> {3, 5}, results);

	test.description("range for support");
	results.clear();
	for (int i : s)
		results.push_back(i);
	test.assertEq(v, results);
}

void test_slice() {
	test_slice_indexing();
	test_slice_size();
	test_slice_iteration();

}
