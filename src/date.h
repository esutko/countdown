#ifndef DATE_HEADER_INCLUDED
#define DATE_HEADER_INCLUDED

#include <iostream>

class Date {
public:
	Date();
	Date(int, int, int);

	int get_year() const;
	int get_month() const;
	int get_day() const;
	int get_total_days() const;

	int operator-(const Date &) const;

	bool operator==(const Date &) const;
	bool operator!=(const Date &) const;
	bool operator<(const Date &) const;
	bool operator<=(const Date &) const;
	bool operator>(const Date &) const;
	bool operator>=(const Date &) const;
private:
	int year;
	int month;
	int day;
	int total_days;
};

std::ostream &operator<<(std::ostream &, Date);

bool is_leap_year(int);
int compute_total_days(int, int, int);

#endif
