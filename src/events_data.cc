#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

#include <utility>

#include "date.h"
#include "slice.h"

#include "events_data.h"

using namespace std;

EventsData::EventsData(const vector<Event> &ve) : event_vec(ve) {}

Slice<Event> EventsData::events() const {
	return Slice<Event> {event_vec};
}

const vector<Event>::iterator EventsData::find_event(const string &name) {
	auto elem = find_if(
		event_vec.begin(), event_vec.end(),
		[&name](Event &e){return e.name == name;}
	);
	return elem;
}

void EventsData::add_event(const Event &event) {
	event_vec.push_back(event);
}

void EventsData::update_event(const std::string &name, Date &date) {
	auto elem = find_event(name);

	if (elem == event_vec.end()) {
		add_event(Event {name, date});
	} else {
		(*elem).date = date;
	}
}

bool EventsData::remove_event(const std::string &name) {
	auto elem = find_event(name);

	if (elem == event_vec.end())
		return false;
	
	event_vec.erase(elem);
	
	return true;
}

void EventsData::clean_events(const Date &today, int days) {
	auto start = find_if(
		event_vec.begin(), event_vec.end(),
		[today, days](Event e){return today - e.date < days;}
	);

	event_vec = vector<Event> {start, event_vec.end()};
}

void EventsData::sort_events() {
	sort(event_vec.begin(), event_vec.end(), [](Event x, Event y){return x.date < y.date;});
}

ostream &operator<<(ostream &out, const Event &s) {
	out << s.name << ": " << s.date;
	return out;
}
