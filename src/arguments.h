#ifndef ARGUMENTS_HEADER_INCLUDED
#define ARGUMENTS_HEADER_INCLUDED

#include <string>

#include <utility>

#include "mode_input.h"

struct Options {
	bool no_prompt;
	std::string filename;
};

std::pair<ModeInput, Options> parse_args(int, char *[]);

#endif