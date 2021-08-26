#include <iostream>
#include <iomanip>

#include <vector>
#include <string>
#include <algorithm>

#include "arguments.h"
#include "auto_correct.h"
#include "datafile.h"
#include "date.h"
#include "events_data.h"
#include "mode_input.h"
#include "slice.h"

using namespace std;

const Date today;

void output_time_until_event(const Event &e, size_t padding) {
	int diff = e.date - today;

	cout << left << setw(padding + 4);
	cout << e.name + ":";
	if (diff  > 0) {
		cout << diff  << " days";
	} else {
		cout << "was on " << e.date;
	}
	cout << "\n";
}

void do_countdown(const Slice<Event> &events) {
	auto start = find_if(
		events.begin(), events.end(),
		[](Event e){return e.date - today >= -14;}
	);
	size_t max_length = max_element(
		start,
		events.end(),
		[](Event x, Event y){return x.name.size() < y.name.size();}
	)->name.size();

	for (auto iter = start; iter != events.end(); iter++)
		output_time_until_event(*iter, max_length);
}

void list_events(const Slice<Event> &events) {
	for (Event e : events)
		cout << e << "\n";
}

void update_events(EventsData &data, const Options &opts, const string &name_input, Date date_input) {
	string name = name_input;
	if (!opts.no_prompt)
			name = auto_correct(data.events(), name_input);
	
	data.update_event(name, date_input);

	write_events(data, opts.filename);
}

void remove_event(EventsData &data, const Options &opts, const string &name_input) {
	string name = name_input;
	if (!opts.no_prompt)
		name = auto_correct(data.events(), name_input);

	if (!data.remove_event(name)) 
		cerr << "Couldn't find event" << name_input << " in file " << opts.filename << "\n";

	write_events(data, opts.filename);
}

void clean_events(EventsData &data, const Options &opts, int days) {
	data.clean_events(today, days);

	write_events(data, opts.filename);
}

void usage_information() {
	cout << "Usage: countdown [OPTION]... [MODE]" << "\n";
	cout << "\n";
	cout << "countdown keeps track of events and displays the number of days until events." << "\n";
	cout << "When no mode is given countdown will show the days until known events and" << "\n";
	cout << "the date of any events in the last two weeks." << "\n";
	cout << "\n";
	cout << "List of Modes:";
	cout << "\n";
	cout << "  countdown             the default mode, displays days until upcoming events." << "\n";
	cout << "  list                  lists ALL known events and their dates." << "\n";
	cout << "  update [NAME] [DATE]  updates the event NAME or creates an event NAME." << "\n";
	cout << "  remove [NAME]         removes the event specified by NAME." << "\n";
	cout << "  clean  [DAYS]         removes events that happened more than DAYS days ago." << "\n";
	cout << "  help                  displays usage information" << "\n";
	cout << "\n";
	cout << "NAME should consist of letters, numbers, and spaces." << "\n";
	cout << "DATE should consist of digits seperated by dashes and be in the form" << "\n"; 
	cout << "year-month-day." << "\n";
	cout << "\n";
	cout << "The options are:" << "\n";
	cout << "  -h --help       displays usage information" << "\n";
	cout << "  -f --file=PATH  uses PATH as the events file" << "\n";
	cout << "  -n --no-prompt  disables auto correct and prompts" << "\n";
	cout << "\n";
}

int main(int argc, char *argv[]) {	
	try {
		auto [input, opts] = parse_args(argc, argv);

		EventsData data;
		data = get_events(opts.filename);
		data.sort_events();

		switch (input.get_mode()) {
			case Mode::countdown : do_countdown(data.events()); break;
			case Mode::list      : list_events(data.events()); break;
			case Mode::update    : update_events(data, opts, input.get_name_input(), input.get_date_input()); break;
			case Mode::remove    : remove_event(data, opts, input.get_name_input()); break;
			case Mode::clean     : clean_events(data, opts, input.get_days_input()); break;
			case Mode::help      : usage_information(); break;
		}
	}
	catch (...) {
		return 1;
	}
	
	return 0;
}