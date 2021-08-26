#include <iostream>

#include <ctime>
#include <cmath>

#include "date.h"

using namespace std;

Date::Date() {
	time_t t = time(nullptr);
	auto now = localtime(&t);
	
	year = now->tm_year + 1900;
	month = now->tm_mon + 1;
	day = now->tm_mday;

	total_days = compute_total_days(year, month, day);
}

Date::Date(int y, int m, int d) {
	year = y;
	month = m;
	day = d;

	total_days = compute_total_days(year, month, day);
}

int Date::get_year() const {
	return year;
}

int Date::get_month() const {
	return month;
}

int Date::get_day() const {
	return day;
}

int Date::get_total_days() const {
	return total_days;
}

int Date::operator-(const Date &other) const {
	return total_days - other.total_days;
}

bool Date::operator==(const Date &other) const {
	return total_days == other.total_days;
}

bool Date::operator!=(const Date &other) const {
	return !(*this == other);
}

bool Date::operator<(const Date &other) const {
	return total_days < other.total_days;
}

bool Date::operator<=(const Date &other) const {
	return *this < other || *this == other;
}

bool Date::operator>(const Date &other) const {
	return !(*this <= other);
}

bool Date::operator>=(const Date &other) const {
	return !(*this < other);
}

ostream &operator<<(ostream &out, Date d) {
	return out << d.get_year() << "-" << d.get_month() << "-" << d.get_day();
}

bool is_leap_year(int year) {
	if (year % 400 == 0)
		return true;
	if (year % 100 == 0)
		return false;
	if (year % 4 == 0)
		return true;
	return false;
}

int compute_total_days(int year, int month, int day) {
	constexpr int month_lengths[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int total_days = 0;

	int last_year = year - 1;
	total_days = last_year * 365;
	total_days += floor(last_year/4) - floor(last_year/100) + floor(last_year/400);

	for (int i = 1; i < month; ++i)
		total_days += month_lengths[i];
	if (is_leap_year(year) && month > 2)
		++total_days;

	total_days += day;

	return total_days;
}
