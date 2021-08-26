#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

#include <cctype>
#include <stdexcept>

#include "parsing.h"

using namespace std;

bool valid_integer(string::const_iterator start, string::const_iterator stop) {
	if (*start == '+' || *start == '-')
		++start;
	return all_of(
		start, stop,
		[](char c){return isdigit(c);}
	);
}

bool valid_date(string::const_iterator start, string::const_iterator stop) {
	vector<int> lengths = {0};
	for (auto iter = start; iter != stop; ++iter) {
		if (isdigit(*iter)) {
			++lengths.back();
		} else if (*iter == '-') {
			lengths.push_back(0);
		} else {
			return false;
		}
	}

	if (lengths.size() != 3)
		return false;

	bool found_digits = 0 < lengths[0] && 0 < lengths[1] && 0 < lengths[2];
	bool correct_lengths = lengths[0] <= 4 && lengths[1] <= 2 && lengths[2] <= 2;

	return found_digits && correct_lengths;
}

bool valid_name(string::const_iterator start, string::const_iterator stop) {
	return all_of(
		start, stop,
		[](char c){return isalnum(c) || isspace(c);}
	);
}

bool valid_line(const string &line) {
	auto name_end = find(line.begin(), line.end() , ':');
	auto date_begin = find_if(
		name_end, line.end(),
		[](char c){return isdigit(c);}
	);
	return name_end != line.end() && valid_name(line.begin(), name_end) && valid_date(date_begin, line.end());
}

int extract_number(string::const_iterator &iter) {
	for (; isspace(*iter) || *iter == ':' || *iter == '-'; ++iter);

	string number;
	for(; isdigit(*iter); ++iter)
		number += *iter;

	return stoi(number);
}

string extract_name(string::const_iterator &iter) {
	string name;
	for (; isalnum(*iter) || isspace(*iter); ++iter)
		name += *iter;

	return name;
}

// the old regex
//([\w\s]+):\s*(\d{1,4})-(\d{1,2})-(\d{1,2})

void parse_line(const string &line, string &name, int &year, int &month, int &day) {
	if (!valid_line(line)) {
		cerr << "countdown" << ": bad line \"" << line << "\"\n";
		throw runtime_error("bad line");
	}

	auto iter = line.begin();
	name = extract_name(iter);
	year = extract_number(iter);
	month = extract_number(iter);
	day = extract_number(iter);
}