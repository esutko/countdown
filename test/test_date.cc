#include <sstream>

#include <string>

#include <filesystem>
#include <chrono>
#include <ctime>

#include "../src/date.h"
#include "lib/test.h"

#include "test_date.h"

using namespace std;
using namespace std::filesystem;
using namespace std::chrono;

void test_leap_years() {
	Test test{"leap years"};

	test.description("year is a multiple of 4");
	test.assert(is_leap_year(2020));

	test.description("year is not divisible by 4");
	test.assert(!is_leap_year(2001));

	test.description("year is a multiple of 100");
	test.assert(!is_leap_year(1900));

	test.description("year is a multiple of 400");
	test.assert(is_leap_year(2000));
}

void test_total_days() {
	Test test{"total days"};

	test.description("1-1-1 has one total day");
	test.assertEq(1, compute_total_days(1, 1, 1));

	test.description("1-12-31 has 365 total days");
	test.assertEq(365, compute_total_days(1, 12, 31));

	test.description("Feb 29th is handled properly");
	test.assertEq(compute_total_days(4, 3, 1), compute_total_days(4, 2, 29) + 1);

	test.description("General total days computation");
	int total_days = (365 * 13 + 1 + 1 + 1) + (31 + 28 + 31 + 30 + 31 + 30 + 31) + 19; // 4979
	test.assertEq(total_days, compute_total_days(14, 8, 19));

	test.description("Date total days method");
	Date d{14, 8, 19};
	test.assertEq(total_days, d.get_total_days());
}

void test_today() {
	Test test{"today"};
	Date today{};

	test.description("sanity check");
	string compiled = __DATE__;
	int year = stoi(compiled.substr(7));
	int day = stoi(compiled.substr(4,2));
	
	int month = 0;
	string mstr = compiled.substr(0, 3);
	string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	for (; month < 11 && mstr != months[month]; ++month);
	++month;

	test.assert(today >= Date{year, month, day});
}

void test_date_subtraction() {
	Test test{"date subtraction"};

	Date d1{2021, 6, 5};
	Date d2{2022, 2, 14};
	int diff = (30 - 5) + 31 + 31 + 30 + 31 + 30 + 31 + 31 + 14;
	test.assertEq(diff, d2 - d1);
}

void test_date_comparison() {
	Test test{"date comparison"};

	Date d{2022, 2, 14};

	Date lt{2021, 6, 5};
	Date eq{d};
	Date gt{2022, 6, 5};

	test.assert(!(d == lt));
	test.assert(d == eq);
	test.assert(!(d == gt));

	test.assert(d != lt);
	test.assert(!(d != eq));
	test.assert(d != gt);

	test.assert(!(d < lt));
	test.assert(!(d < eq));
	test.assert(d < gt);

	test.assert(!(d <= lt));
	test.assert(d <= eq);
	test.assert(d <= gt);

	test.assert(d > lt);
	test.assert(!(d > eq));
	test.assert(!(d > gt));

	test.assert(d >= lt);
	test.assert(d >= eq);
	test.assert(!(d >= gt));
}

void test_date_stream_insertion() {
	Test test{"date stream insertion"};
	
	ostringstream out1{};
	Date d1{2021, 6, 5};
	out1 << d1;
	test.assertEq("2021-6-5"s, out1.str());
}

void test_date() {
	test_leap_years();
	test_total_days();
	test_today();
	test_date_subtraction();
	test_date_comparison();
	test_date_stream_insertion();
}
