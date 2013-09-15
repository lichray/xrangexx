#include "xrange.h"
#include <iostream>

using stdex::xrange;
using stdex::rxrange;

int main()
{
	for (auto i : xrange(5))
		std::cout << i << ' ';
	std::cout << std::endl;

	for (auto i : rxrange(5))
		std::cout << i << ' ';
	std::cout << std::endl;

	for (auto i : xrange('a', 'g'))
		std::cout << i << ' ';
	std::cout << std::endl;

	for (auto i : rxrange('a', 'g'))
		std::cout << i << ' ';
	std::cout << std::endl;

	constexpr auto r = xrange(3UL, 8UL);
	for (auto i : r)
		std::cout << i << ' ';
	std::cout << std::endl;

	auto r1 = xrange('A', 'Z');
	auto len = std::distance(begin(r1), end(r1));
	std::cout << len << std::endl;
}
