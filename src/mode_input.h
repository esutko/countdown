#ifndef INPUT_CONTIANER_HEADER_INCLUDED
#define INPUT_CONTIANER_HEADER_INCLUDED

#include <string>

#include <memory>
#include <exception>

#include "date.h"

/* Options contians data that should have a default value and ModeInput contians data dependent on the mode.
   In other words Options contians data that always has a value and ModeInput contians data that many not.
   The exception to this is ModeInput's mode, which must always have a value.
   A mode can be thought of as a promise that ModeInput will contain some correspodning data. */

class no_such_value : std::exception {
public:
	no_such_value() = default;
};

enum class Mode {countdown, list, update, remove, clean, help};

class ModeInput {
public:
	ModeInput() = default;
	~ModeInput() = default;

	ModeInput(const ModeInput &);
	ModeInput &operator=(const ModeInput &);
	
	ModeInput(ModeInput &&) = default;
	ModeInput &operator=(ModeInput &&) = default;

	void set_mode(Mode);
	void set_name_input(const std::string &);
	void set_date_input(const Date &);
	void set_days_input(int);

	Mode get_mode();
	std::string get_name_input();
	Date get_date_input();
	int get_days_input();
private:
	Mode mode = Mode::countdown;
	std::unique_ptr<std::string> name_input {nullptr};
	std::unique_ptr<Date> date_input {nullptr};
	std::unique_ptr<int> days_input {nullptr};
};

#endif