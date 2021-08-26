#ifndef SHOW_HEADER_INCLUDED
#define SHOW_HEADER_INCLUDED

#include <iostream>

#include <string>
#include <vector>

#include <utility>

#include "date.h"
#include "slice.h"

struct Event {
	std::string name;
	Date date;
};

class EventsData {
public:
	EventsData() = default;
	EventsData(const std::vector<Event> &);

	EventsData(const EventsData &) = default;
	EventsData(EventsData &&) = default;

	EventsData &operator=(const EventsData &) = default;
	EventsData &operator=(EventsData &&) = default;

	~EventsData() = default;

	Slice<Event> events() const;

	const std::vector<Event>::iterator find_event(const std::string &);

	void add_event(const Event &);
	void update_event(const std::string &, Date &);
	bool remove_event(const std::string &);

	void clean_events(const Date &, int);

	void sort_events();

private:
	std::vector<Event> event_vec;
};

std::ostream &operator<<(std::ostream &, const Event &);

#endif