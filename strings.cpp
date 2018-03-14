#include <string>
#include <sstream>

namespace maxy
{
	namespace strings
	{
		void emit_char (std::ostringstream &os, int c)
		{
			if (c < 128)
				os << (char) c;
			else if (c < 0x800)
				// two bytes 110yyyyy	10xxxxxx
				// yyy yyxxxxxx
				os << (char) (((c & 0x7c0) >> 6) | 0xc0)
				   << (char) (((c & 0x03f)) | 0x80);
			else // if (c < 0x10000)
				 // three bytes 1110zzzz	10yyyyyy	10xxxxxx
				 // zzzzyyyy yyxxxxxx
				os << (char) (((c & 0xf000) >> 12) | 0xe0)
				   << (char) (((c & 0x0fc0) >> 6) | 0x80)
				   << (char) (((c & 0x003f)) | 0x80);
		}

		std::wstring utf8towchar (const std::string & in)
		{
			std::wostringstream os;

			for (size_t i = 0; i < in.size (); i++)
			{
				char p = in[i];
				wchar_t o;
				int size = 0;

				if (p >= 0 && p < 128)
					o = p;
				else if ((p & 0xe0) == 0xc0) // first byte of 2-byte sequence
					size = 1;
				else if ((p & 0xf0) == 0xe0) // first byte of 3-byte sequence
					size = 2;
				else if ((p & 0xf8) == 0xf0) // first byte of 4-byte sequence
					size = 3;

				if (size)
				{
					o = p & (0x7f >> size);
					while (size--)
					{
						p = in[++i];
						if ((p & 0xc0) != 0x80)
						{
							o = 0;
							break;
						}
						o = (o << 6) | (p & 0x3f);
					}
				}

				if (o) os << o;
			}

			return os.str ();
		}

		std::string wchartoutf8 (const std::wstring & in)
		{
			std::ostringstream os;
			for (auto c : in) emit_char (os, c);
			return os.str ();
		}

		std::pair<std::string, std::string> eq_split (const std::string & in)
		{
			auto ptr = in.find_first_of ('=');
			if (ptr == std::string::npos) return std::make_pair<> (in, std::string{});

			return std::make_pair<> 
			(
				std::string{in.cbegin (),in.cbegin () + ptr}, 
				std::string{in.cbegin () + ptr + 1, in.cend ()}
			);
		}
	}
}
