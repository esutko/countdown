#include <iostream>

#include <string>

#include <memory>
#include <exception>
#include <utility>
#include <cstdlib>
#include <getopt.h>

#include "datafile.h"
#include "mode_input.h"
#include "parsing.h"

#include "arguments.h"

using namespace std;

void invalid_mode(const string &mode_str) {
	cerr << "\"" << mode_str << "\" is not a valid mode" << "\n"
		 << "Try countdown --help for more information." << "\n";
	throw runtime_error("invalid mode");
}

void too_few_arguments(const string &mode_str, int arg_count) {
	cerr << "for mode " << mode_str << "\n"
		 << "was expecting atleast " << arg_count << "arguments." << "\n"
		 << "Try countdown --help for more information." << "\n";
	throw runtime_error("too few argument");
 
}

void bad_integer_input(const string &int_str) {
	cerr << "\"" << int_str << "\" is not an integer." 
		 << "Try countdown --help for more information." << "\n";
	throw runtime_error("bad integer input");

}

void bad_name_input(const string &name_str) {
	cerr << "\"" << name_str << "\" is no a valid event name." << "\n"
		 << "An event name can only contian letters numbers and white space." << "\n"
		 << "Try countdown --help for more information." << "\n";
	throw runtime_error("bad name input");
}

void bad_date_input(const string &date_str) {
	cerr << "\"" << date_str << "\" is not a valid date" << "\n"
	     << "Dates should be in \"year-month-day\" format." << "\n"
	     << "Try countdown --help for more information." << "\n";
	throw runtime_error("bad date input");
}

void get_update_input(ModeInput &input, int argc, char *argv[], int data_start) {
	if (argc - data_start < 3)
		too_few_arguments("update", 2);

	string name;
	int year, month, day;

	for (int i = data_start + 1; i < argc - 1; ++i) {
		name += argv[i];
		if (i < argc - 2)
			name += " ";
	}

	if (!valid_name(name.begin(), name.end()))
		bad_name_input(name);

	input.set_name_input(name);

	const string date_string = argv[argc - 1];
	if (!valid_date(date_string.begin(), date_string.end()))
		bad_date_input(date_string);

	auto iter = date_string.begin();
	year = extract_number(iter);
	month = extract_number(iter);
	day = extract_number(iter);

	input.set_date_input(Date {year, month, day});
}


void get_remove_input(ModeInput &input, int argc, char *argv[], int data_start) {
	if (argc - data_start < 2)
		too_few_arguments("remove", 1);

	string name;
	for (int i = data_start + 1; i < argc; ++i) {
		name += argv[i];
		if (i < argc - 1)
			name += " ";
	}

	if (!valid_name(name.begin(), name.end()))
		bad_name_input(name);
	
	input.set_name_input(name);
}

void get_clean_input(ModeInput &input, int argc, char *argv[], int data_start) {
	if (argc - data_start < 2)
		too_few_arguments("clean", 1);

	string int_str = argv[data_start + 1];
	if (!valid_integer(int_str.begin(), int_str.end()))
		bad_integer_input(int_str);

	input.set_days_input(stoi(int_str));
}

pair<ModeInput, Options> parse_args(int argc, char *argv[]) {
	ModeInput input;
	Options options {false, get_default_filename()};

	const char *optstring = "hf:n";
	option optarr[] = {
		{"help", no_argument, nullptr, 'h'},
		{"file", required_argument, nullptr, 'f'},
		{"no-prompt", no_argument, nullptr, 'n'},
		{0, 0, 0, 0}
	};

	for (int c; (c = getopt_long(argc, argv, optstring, optarr, nullptr)) != -1; ) {
		switch (c) {
			case 'h': input.set_mode(Mode::help);; break;
			case 'f': options.filename = optarg; break;
			case 'n': options.no_prompt = true; break;
		}
	}

	int data_start = optind;

	if (data_start < argc) {
		string mode_arg = argv[data_start];
		if (mode_arg == "countdown") {
			input.set_mode(Mode::countdown);
		} else if (mode_arg == "list") {
			input.set_mode(Mode::list);
		} else if (mode_arg == "update") {
			input.set_mode(Mode::update);
			get_update_input(input, argc, argv, data_start);
		} else if (mode_arg == "remove") {
			input.set_mode(Mode::remove);
			get_remove_input(input, argc, argv, data_start);
		} else if (mode_arg == "clean") {
			input.set_mode(Mode::clean);
			get_clean_input(input, argc, argv, data_start);
		} else if (mode_arg == "help") {
			input.set_mode(Mode::help);
		} else {
			invalid_mode(mode_arg);
		}
	}

	return pair{input, options};
}
