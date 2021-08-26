#include <string>

#include <memory>

#include "mode_input.h"

using namespace std;

ModeInput::ModeInput(const ModeInput &other) {
	*this = other;
}

ModeInput &ModeInput::operator=(const ModeInput &other) {
	if (this == &other)
		return *this;

	name_input.reset(nullptr);
	date_input.reset(nullptr);
	days_input.reset(nullptr);

	mode = other.mode;
	if (other.name_input)
		set_name_input(*other.name_input);
	if (other.date_input)
		set_date_input(*other.date_input);
	if (other.days_input)
		set_days_input(*other.days_input);

	return *this;
}

void ModeInput::set_mode(Mode m) {
	mode = m;
}

void ModeInput::set_name_input(const string &s) {
	name_input.reset(new string {s});
}

void ModeInput::set_date_input(const Date &d) {
	date_input.reset(new Date {d});
}

void ModeInput::set_days_input(int i) {
	days_input.reset(new int);
	*days_input = i;
}

Mode ModeInput::get_mode() {
	return mode;
}

string ModeInput::get_name_input() {
	if (!name_input) 
		throw no_such_value();
	return *name_input;
}

Date ModeInput::get_date_input() {
	if (!date_input) 
		throw no_such_value();
	return *date_input;
}

int ModeInput::get_days_input() {
	if (!days_input) 
		throw no_such_value();
	return *days_input;
}