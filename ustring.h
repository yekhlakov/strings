#pragma once
#ifndef MAXY_STRINGS_USTRING
#define MAXY_STRINGS_USTRING
#include <string>

/**
 *
 *	UTF-8 String
 *
 */
namespace maxy
{
	namespace strings
	{
		class ustring : public std::string
		{
			public:
			// default constructor, destructor and assignment
			ustring () = default;
			~ustring () = default;
			ustring (const ustring & in) = default;
			// copy constructor
			ustring (const std::string & in) : std::string{in} {}
			// move constructor
			ustring (ustring && in) : std::string{in} {}
			// move constructor
			ustring (std::string && in) : std::string{in} {}
			// special constructor
			ustring (const std::string & in, size_t begin, size_t end);

			// shift pointer if necessary for it to point to the beginning of a character
			size_t adjust_pointer (size_t byte_ptr) const;
			// decode utf-8 character sequence starting from the given pointer
			int decode_char (size_t byte_ptr) const;
			// adjust pointer and decode (pointer may point inside the sequence)
			int adjust_and_decode_char (size_t byte_ptr) const;
			// get pointer to the next utf-8 character
			size_t next_char (size_t byte_ptr, size_t count = 1) const;
			// get pointer to the previous utf-8 character
			size_t prev_char (size_t byte_ptr, size_t count = 1) const;

			// erase given number of utf-8 characters starting from the given one
			void erase_chars (size_t char_ptr, size_t count = 1);

			// size of string in utf-8 characters
			size_t char_size () const;

			// get a utf-8 character
			// this is slow so using iterator is better
			int operator() (size_t char_ptr) const;

			// get iterator
			class char_iterator
			{
				ustring & str;
				size_t char_ptr;
				size_t byte_ptr;
				
				public:
				
				char_iterator (ustring & s, size_t cp = 0, size_t bp = 0) : str{s}, char_ptr{cp}, byte_ptr{bp} {};

				char_iterator & operator++()
				{
					if (byte_ptr >= str.size ()) return *this;
					char_ptr++;
					byte_ptr = str.next_char (byte_ptr);
					return *this;
				}

				char_iterator & operator--()
				{
					if (!byte_ptr) return *this;
					char_ptr--;
					byte_ptr = str.prev_char (byte_ptr);
					return *this;
				}

				int operator*()
				{
					return str.decode_char (byte_ptr);
				}
			};

			char_iterator char_begin ()
			{
				return char_iterator{*this};
			}

			char_iterator char_end ()
			{
				return char_iterator{*this, char_size(), size()}; 
			}

		};
	}
}

#endif // MAXY_STRINGS_USTRING
