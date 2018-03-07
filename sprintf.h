#pragma once
#ifndef MAXY_STRINGS_SPRINTF
#define MAXY_STRINGS_SPRINTF

#include <string>
#include <sstream>
#include <iomanip>
#include <type_traits>
#include "strings.h"

namespace maxy
{
	namespace strings
	{
		/**
		* "Type-safe" Sprintf
		*/
		template<typename... Ts>
		std::string sprintf (const char * format, Ts... args)
		{
			std::ostringstream out;
			maxy::strings::osprintf (out, format, args...);
			return out.str ();
		}
		template<typename... Ts>
		std::string sprintf (const std::string format, Ts... args)
		{
			std::ostringstream out;
			maxy::strings::osprintf (out, format.c_str (), args...);
			return out.str ();
		}

		/**
		* Specialization for the degenerate case
		*/
		template<typename T = void>
		std::string sprintf (const char * format)
		{
			return format;
		}
		template<typename T = void>
		std::string sprintf (const std::string format)
		{
			return format;
		}

		/**
		* Helper class for output of individual data args
		*/
		struct printf_format
		{
			int width;
			int precision;
			bool plus;
			bool minus;
			bool base;
			char type;
			char fill;

			// Default constructor
			printf_format () :
				width{0},
				precision{6},
				type{'s'},
				fill{' '},
				plus{false},
				minus{false},
				base{false}
			{
			};

			// Decode a %X format string
			size_t decode (const char * format)
			{
				const char * start = format;

				// probably specifiers
				while (*format)
				{
					if (*format == '0') fill = '0';
					else if (*format == ' ') fill = ' ';
					else if (*format == '+') plus = true;
					else if (*format == '-') minus = true;
					else if (*format == '#') base = true;
					else break;
					format++;
				}

				// probably width
				if (*format >= '1' && *format <= '9')
				{
					width = std::stoi (format);
					while (*format >= '0' && *format <= '9') format++;
				}

				// probably precision
				if (*format == '.')
				{
					format++;
					if (*format >= '0' && *format <= '9')
					{
						precision = std::stoi (format);
						while (*format >= '0' && *format <= '9') format++;
					}
				}

				type = *format;
				return format - start + 1;
			}

			void prepare_stream (std::ostringstream & os) const
			{
				os << std::setw (width) << std::setprecision (precision) << std::setfill (fill);
				if (plus) os << std::showpos;
				if (minus) os << std::left;
				if (base) os << std::showbase;
				if (type == 'O' || type == 'X' || type == 'E') os << std::uppercase;
			}

			template<typename T>
			typename std::enable_if<std::is_convertible<typename T, long long>::value && std::is_convertible<typename T, long double>::value, size_t>::type
				output (std::ostream & out, T arg)
			{
				std::ostringstream os;
				prepare_stream (os);

				switch (type)
				{
					case 'd': os << std::dec << (long long) arg; break;
					case 'u': os << std::dec << (unsigned long long) arg; break;
					case 'x': case 'X': os << std::hex << std::internal << (unsigned long long) arg; break;
					case 'o': case 'O': os << std::oct << (unsigned long long) arg; break;
					case 'f': case 'F': os << std::dec << std::fixed << (long double) arg; break;
					case 'e': case 'E': os << std::dec << std::scientific << (long double) arg; break;
						// note that 's' can be used to "printf" any user-defined object
					case 's':
					default:  os << arg; break;
				}
				out << os.str ();
				return os.str ().size ();
			}

			template<typename T>
			typename std::enable_if<std::is_convertible<typename T, long long>::value && !std::is_convertible<typename T, long double>::value, size_t>::type
				output (std::ostream & out, T arg)
			{
				std::ostringstream os;
				prepare_stream (os);

				switch (type)
				{
					case 'd': os << std::dec << (long long) arg; break;
					case 'u': os << std::dec << (unsigned long long) arg; break;
					case 'x': case 'X': os << std::hex << std::internal << (unsigned long long) arg; break;
					case 'o': case 'O': os << std::oct << (unsigned long long) arg; break;
						// note that 's' can be used to "printf" any user-defined object
					case 's':
					default:  os << arg; break;
				}
				out << os.str ();
				return os.str ().size ();
			}

			template<typename T>
			typename std::enable_if<!std::is_convertible<typename T, long long>::value, size_t>::type
				output (std::ostream & out, T arg)
			{
				std::ostringstream os;
				prepare_stream (os);
				os << arg;
				out << os.str ();
				return os.str ().size ();
			}

			size_t output (std::ostream & out, std::wstring arg)
			{
				return output (out, maxy::strings::wchartoutf8 (arg));
			}

			size_t output (std::ostream & out, const wchar_t * arg)
			{
				return output (out, maxy::strings::wchartoutf8 (std::wstring{arg}));
			}
		};

		/**
		* This version accepts std::string as format string
		*/
		template<typename... Ts>
		size_t osprintf (std::ostream & out, const std::string format, Ts... args)
		{
			return maxy::strings::osprintf (out, format.c_str (), args...);
		}

		/**
		* Print to a stream
		*/
		template<typename T, typename... Ts>
		size_t osprintf (std::ostream & out, const char * format, T arg, Ts... args)
		{
			size_t count{0};
			while (*format)
			{
				if (*format != '%')
				{
					out << *format++;
					count++;
				}
				else
				{
					format++;
					if (*format == '%')
					{
						out << '%';
						format++;
						count++;
						continue;
					}
					maxy::strings::printf_format f{};
					format += f.decode (format);
					return count + f.output (out, arg) + maxy::strings::osprintf (out, format, args...);
				}
			}
			return count;
		}

		/**
		* Print and append to existing string - (kinda) specialization for no data arguments.
		* Beware, this will just emit any format specifiers as is
		*/
		inline size_t osprintf (std::ostream & out, const char * format)
		{
			std::string x{format};
			out << x;
			return x.size ();
		}
	}
}

#endif // MAXY_STRINGS_SPRINTF
