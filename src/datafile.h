#ifndef DATAFILE_HEADER_INCLUDED
#define DATAFILE_HEADER_INCLUDED

#include <string>

#include "events_data.h"

std::string get_default_filename();

template <typename fstream>
fstream open_datafile(const std::string &);

EventsData get_events(const std::string &);

void write_events(EventsData &, const std::string &);
#endif