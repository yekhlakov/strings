#include <iostream>
#include "sprintf.h"
#include "ustring.h"

std::string gets ()
{
	return "ururu";
}

int main ()
{
	std::cout << maxy::strings::sprintf ("floats = %f %f %f %f\n", int{-1324}, double{5.4}, char{'a'}, 0xfefe0000fefe)
		  << maxy::strings::sprintf ("floats = %3.4f %3.4f %3.4f %3.4f\n", int{-1234}, double{5.4321094}, char{'a'}, 0xfefe0000fefe)
		  << maxy::strings::sprintf ("width = 5: %5.0f %5.1f %5.2f %5.3f\n", double{1234.5678}, double{1234.5678}, double{1234.5678}, double{1234.5678})
		  << maxy::strings::sprintf ("ality = %4.4d %4.4o %4.4x %#07.4d %#07.4O %#07.4X\n", int{1234}, int{1234}, int{1234}, int{1234}, int{1234}, int{1234})
		  << maxy::strings::sprintf ("formats = %05d %+5d %0-5d\n", int{123}, int{123}, int{123})
		  << maxy::strings::sprintf ("broken formats = %@# %04") << "\n"
		  << maxy::strings::sprintf ("more broken formats %1.3% %") << "\n";

	const char cc[] = "Test1";
	char c[] = "Test2";
	std::string s{"Test3"};
	std::wstring ws{L"TestWS"};
	std::cout << maxy::strings::sprintf ("strings = %s %s %s %s\n", cc, c, s, ws);

	int r = 666;
	maxy::strings::osprintf (std::cout, "osprintf: INT = %d, S1 = %s, GS=%s\n", r, s, gets ());


	maxy::strings::ustring us{u8"ЙЦУQWE"};

	std::cout << "unicode string = " << us << "\n"
		  << "size() = " << us.size() << "\n"
		  << "char_size() = " << us.char_size() << "\n"
		  << "s[3] = " << int{us[3]} << ", s(3) " << us(3) << "\n";

	std::cout << "byte iteration: ";
	for (auto bi : us) std::cout << "(" << bi << ") ";
	std::cout << "\n";

	std::cout << "char iteration: ";
	for (auto ci = us.char_begin (); ci != us.char_end (); ci++) std::cout << "(" << *ci << ") ";
	std::cout << "\n";

	auto us2 = us;

	us.erase (2, 3);
	us2.char_erase (2, 3);

	std::cout << "byte erase(2,3)" << us << "\n"
		  << "char erase(2,3)" << us2 << "\n";
}