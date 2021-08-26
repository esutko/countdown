#ifndef PARSING_HEADER_INCLUDED
#define PARSING_HEADER_INCLUDED

#include <string>

bool valid_integer(std::string::const_iterator, std::string::const_iterator);
bool valid_date(std::string::const_iterator, std::string::const_iterator);
bool valid_name(std::string::const_iterator, std::string::const_iterator);
bool valid_line(const std::string &);

std::string extract_name(std::string::const_iterator &);
int extract_number(std::string::const_iterator &);

void parse_line(const std::string &, std::string &, int &, int &, int &);

#endif