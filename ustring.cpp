#include "sprintf.h"
#include "ustring.h"

namespace maxy
{
	namespace strings
	{
		ustring::ustring (const std::string & in, size_t begin, size_t end)
		{
			begin = adjust_pointer (begin);
			end = adjust_pointer (end);
			std::string (in.c_str() + begin, end - begin);
		}

		size_t ustring::adjust_pointer (size_t byte_ptr) const
		{
			if (byte_ptr >= size ()) return size ();
			while (byte_ptr && ((*this)[byte_ptr] & 0xc0) == 0x80) byte_ptr--;
			return byte_ptr;
		}

		int ustring::decode_char (size_t byte_ptr) const
		{
			int p{(*this)[byte_ptr]};
			int o{0};
			int sz{0};

			if (p >= 0 && p < 128)
				return p;
			else if ((p & 0xe0) == 0xc0) // first byte of 2-byte sequence
				sz = 1;
			else if ((p & 0xf0) == 0xe0) // first byte of 3-byte sequence
				sz = 2;
			else if ((p & 0xf8) == 0xf0) // first byte of 4-byte sequence
				sz = 3;

			if (sz)
			{
				o = p & (0x7f >> sz);
				while (sz-- && byte_ptr < size ())
				{
					p = (*this)[++byte_ptr];
					if ((p & 0xc0) != 0x80)
					{
						o = 0;
						break;
					}
					o = (o << 6) | (p & 0x3f);
				}
			}
			return o;
		}

		int ustring::adjust_and_decode_char (size_t byte_ptr) const
		{
			if (byte_ptr >= size ()) return 0;
			return decode_char (adjust_pointer (byte_ptr));
		}

		size_t ustring::char_size () const
		{
			size_t sz{0}, byte_ptr{0};
			while (byte_ptr < size ())
			{
				if (((*this)[byte_ptr] & 0xc0) != 0x80) sz++;
				byte_ptr++;
			}
			return sz;
		}

		size_t ustring::next_char (size_t byte_ptr, size_t count) const
		{
			if (byte_ptr >= size ()) return size ();

			while (count--)
			{
				if (((*this)[byte_ptr] & 0xc0) != 0x80) byte_ptr++;
				while (byte_ptr < size () && ((*this)[byte_ptr] & 0xc0) == 0x80) byte_ptr++;
			}

			return byte_ptr;
		}

		size_t ustring::prev_char (size_t byte_ptr, size_t count) const
		{
			if (!byte_ptr) return 0;

			byte_ptr++;
			count++;
			while (byte_ptr && count--)
			{
				// skip the first byte
				byte_ptr--;

				// find the beginning of current character
				while (byte_ptr && ((*this)[byte_ptr] & 0xc0) == 0x80) byte_ptr--;
			}

			return byte_ptr;
		}

		void ustring::erase_chars (size_t char_ptr, size_t count)
		{
			auto byte_ptr = next_char (0, char_ptr);
			auto next = next_char (byte_ptr, count);
			erase (byte_ptr, next - byte_ptr);
		}

		int ustring::operator() (size_t char_ptr) const
		{
			auto byte_ptr = next_char (0, char_ptr);
			return decode_char (byte_ptr);
		}
	}
}
