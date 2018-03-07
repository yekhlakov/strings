#pragma once
#ifndef MAXY_STRINGS
#define MAXY_STRINGS
#include <string>
#include <sstream>

namespace maxy
{
	namespace strings
	{
		std::wstring utf8towchar (const std::string & in);
		std::string	wchartoutf8 (const std::wstring & in);
		void emit_char (std::ostringstream &os, int c);
		std::pair<std::string, std::string> eq_split (const std::string & in);
	}
}

#endif //MAXY_STRINGS