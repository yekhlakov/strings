#include <iostream>
#include "sprintf.h"

std::string gets ()
{
	return "ururu";
}

int main ()
{
	std::cout << maxy::strings::sprintf ("integers = %d %d %d %d\n", int{-1324}, double{5.4}, char{'a'}, unsigned long long{0xfefe0000fefe});
	std::cout << maxy::strings::sprintf ("floats = %f %f %f %f\n", int{-1324}, double{5.4}, char{'a'}, unsigned long long{0xfefe0000fefe});
	std::cout << maxy::strings::sprintf ("floats = %3.4f %3.4f %3.4f %3.4f\n", int{-1234}, double{5.4321094}, char{'a'}, unsigned long long{0xfefe0000fefe});
	std::cout << maxy::strings::sprintf ("width = 5: %5.0f %5.1f %5.2f %5.3f\n", double{1234.5678}, double{1234.5678}, double{1234.5678}, double{1234.5678});
	std::cout << maxy::strings::sprintf ("ality = %4.4d %4.4o %4.4x %#07.4d %#07.4O %#07.4X\n", int{1234}, int{1234}, int{1234}, int{1234}, int{1234}, int{1234});
	std::cout << maxy::strings::sprintf ("formats = %05d %+5d %0-5d\n", int{123}, int{123}, int{123});
	std::cout << maxy::strings::sprintf ("broken formats = %@# %04") << "\n";
	std::cout << maxy::strings::sprintf ("more broken formats %1.3% %") << "\n";

	const char cc[] = "Test1";
	char c[] = "Test2";
	std::string s{"Test3"};
	std::wstring ws{L"TestWS"};
	std::cout << maxy::strings::sprintf ("strings = %s %s %s %s", cc, c, s, ws);

	int r = 666;
	maxy::strings::osprintf (std::cout, "INT = %d, S1 = %s, GS=%s\n", r, s, gets ());
}