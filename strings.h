#pragma once
#ifndef MAXY_STRINGS
#define MAXY_STRINGS
#include <string>
#include <sstream>

namespace maxy
{
	namespace strings
	{
		// Convert utf8 char string to wchar_t string
		std::wstring utf8towchar (const std::string & in);
		// Convert wchar_t string to utf8 char string
		std::string	wchartoutf8 (const std::wstring & in);
		// encode unicode character into utf8 and emit it to a stream
		void emit_char (std::ostream &os, int c);
		// Split a string in two using '=' as separator
		std::pair<std::string, std::string> eq_split (const std::string & in, char sep = '=');

		// Check if the string is a representation of an integer
		bool is_int (const std::string & s);
		// Check if the sting is a representation of a float
		bool is_float (const std::string & s);
		// Check if the string is a representation of a number
		bool is_numeric (const std::string & s);
	}
}

#endif //MAXY_STRINGS