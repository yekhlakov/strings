# strings

## ustring.h and ustring.cpp

A wrapper for std::string allowing easier utf-8 operation: indexing individual characters, character iterators etc.

## strings.h and strings.cpp

Unsorted string-related stuff. Most notably, converters from utf-8 to wchar_t and backwards.

## sprintf.h

(Almost) type-safe, template versions of sprintf and fprintf.
This now requires `traits.h` from https://github.com/yekhlakov/traits.git

## escape.h and escape.cpp

Easy escaping and unescaping of strings.
