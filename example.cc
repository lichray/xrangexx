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

	auto r = xrange(5UL);
	for (auto i : r)
		std::cout << i << ' ';
	std::cout << std::endl;

	auto r1 = xrange('A', 'Z');
	auto bg = begin(r1);
	auto ed = end(r1);
	auto len = std::distance(bg, ed);

	for (decltype(len) i = 0; i < len; i += 4)
		std::cout << bg[i] << ' ';
	std::cout << std::endl;

	auto it = bg;
	do
		std::cout << *it << ' ';
	while (*it++ != 'E');
	std::cout << std::endl;

	for (auto it = bg; it < ed; it = 4 + it)
		std::cout << *it << ' ';
	std::cout << std::endl;

	for (auto it = ed - 1; it >= bg; it = it - 4)
		std::cout << *it << ' ';
	std::cout << std::endl;
}
