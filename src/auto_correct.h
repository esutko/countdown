#include <string>
#include <vector>
#include <set>

#include "events_data.h"
#include "slice.h"

std::set<std::string> get_words(const std::string &, bool=false);
double similar (const std::string &, const std::string &);

std::string auto_correct(const Slice<Event> &, const std::string &);