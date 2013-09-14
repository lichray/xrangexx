#include "xrange.h"
#include <iostream>

using stdex::xrange;
using stdex::rxrange;

int main()
{
	for (auto i : xrange(5))
		std::cout << i << ' ';
	std::cout << std::endl;

	for (auto i : rxrange(-5))
		std::cout << i << ' ';
	std::cout << std::endl;

	for (auto i : xrange('a', 'g'))
		std::cout << i << ' ';
	std::cout << std::endl;

	for (auto i : rxrange('g', 'a'))
		std::cout << i << ' ';
	std::cout << std::endl;

	constexpr auto r = xrange(3UL, 8UL);
	for (auto i : r)
		std::cout << i << ' ';
	std::cout << std::endl;
}
