#include <fstream>

#include <string>
#include <vector>

#include <cstring>
#include <cstdlib>

#include "events_data.h"
#include "parsing.h"

#include "datafile.h"

using namespace std;

string get_default_filename() {
	const static string filename = getenv("HOME") + "/.local/share/countdown_data"s;
	return filename;
}

template <typename fstream>
fstream open_datafile(const string &filename) {
	fstream fs{filename};

	if (!fs) {
		const auto e = errno;
		cerr << "countdown" << ": cant't open file: " << filename << " to read: "<< strerror(e) << "\n";
		throw runtime_error("bad file");
	}

	return fs;
}

EventsData get_events(const string &filename) {
	EventsData events;
	auto in = open_datafile<ifstream>(filename);
	string line;

	while (getline(in, line)) {
		if (line.empty())
			continue;
		
		string name;
		int year, month, day;
		try {
			parse_line(line, name, year, month, day);
		}
		catch (...) {
			cerr << "in file " << filename << "\n";
			throw;
		}
		events.add_event(Event {name, Date {year, month, day}});
	}

	return events;
}

void write_events(EventsData &data, const string &filename) {
	auto out = open_datafile<ofstream>(filename);

	for (Event e : data.events())
		out << e << "\n";
}
