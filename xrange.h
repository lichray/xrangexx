/*-
 * Copyright (c) 2013 Zhihao Yuan.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _XRANGE_H
#define _XRANGE_H 1

#include <iterator>
#include <type_traits>

namespace stdex {

namespace detail {

template <typename Int>
struct xrange_iter
{
	static_assert(std::is_integral<Int>(), "integral expected");

	using value_type = Int;
	using difference_type = decltype(Int() - Int());
	using pointer = void;
	using reference = Int;
	using iterator_category = std::random_access_iterator_tag;

	constexpr explicit xrange_iter(Int n) noexcept
		: n_(n)
	{}

	constexpr reference operator*() const noexcept
	{
		return n_;
	}

	constexpr reference operator[](difference_type n) const noexcept
	{
		return n_ + n;
	}

	xrange_iter& operator++() noexcept
	{
		++n_;
		return *this;
	}

	xrange_iter& operator--() noexcept
	{
		--n_;
		return *this;
	}

	xrange_iter operator++(int) noexcept
	{
		xrange_iter tmp(*this);
		++(*this);
		return tmp;
	}

	xrange_iter operator--(int) noexcept
	{
		xrange_iter tmp(*this);
		--(*this);
		return tmp;
	}

	xrange_iter& operator+=(difference_type n) noexcept
	{
		n_ += n;
		return *this;
	}

	friend inline
	xrange_iter operator+ (xrange_iter x, difference_type n) noexcept
	{
		x += n;
		return x;
	}

	friend inline
	xrange_iter operator+ (difference_type n, xrange_iter x) noexcept
	{
		return x + n;
	}

	xrange_iter& operator-=(difference_type n) noexcept
	{
		n_ -= n;
		return *this;
	}

	friend inline
	xrange_iter operator- (xrange_iter x, difference_type n) noexcept
	{
		x -= n;
		return x;
	}

	friend inline
	bool operator==(xrange_iter const& x, xrange_iter const& y) noexcept
	{
		return x.n_ == y.n_;
	}

	friend inline
	bool operator!=(xrange_iter const& x, xrange_iter const& y) noexcept
	{
		return !(x == y);
	}

	friend inline
	bool operator< (xrange_iter const& x, xrange_iter const& y) noexcept
	{
		return x.n_ < y.n_;
	}

	friend inline
	bool operator> (xrange_iter const& x, xrange_iter const& y) noexcept
	{
		return y < x;
	}

	friend inline
	bool operator>=(xrange_iter const& x, xrange_iter const& y) noexcept
	{
		return !(x < y);
	}

	friend inline
	bool operator<=(xrange_iter const& x, xrange_iter const& y) noexcept
	{
		return !(x > y);
	}

	friend inline
	difference_type operator-(xrange_iter const& x, xrange_iter const& y)
		noexcept
	{
		return x.n_ - y.n_;
	}

private:
	Int n_;
};

template <typename Iter>
struct xrange_t
{
	constexpr xrange_t(Iter first, Iter last)
		: first_(first), last_(last)
	{}

	friend inline Iter begin(xrange_t const& c)
	{
		return c.first_;
	}

	friend inline Iter end(xrange_t const& c)
	{
		return c.last_;
	}

private:
	Iter first_, last_;
};

}

template <typename Iter>
inline auto make_reverse_iterator(Iter it)
	-> std::reverse_iterator<Iter>
{
	return std::reverse_iterator<Iter>(it);
}

template <typename Int>
constexpr auto xrange(Int b)
	-> detail::xrange_t<detail::xrange_iter<Int>>
	// precondition: 0 <= b
{
	return { detail::xrange_iter<Int>(Int()),
	         detail::xrange_iter<Int>(b) };
}

template <typename Int>
constexpr auto xrange(Int a, Int b)
	-> detail::xrange_t<detail::xrange_iter<Int>>
	// precondition: a <= b
{
	return { detail::xrange_iter<Int>(a),
	         detail::xrange_iter<Int>(b) };
}

template <typename Int>
constexpr auto rxrange(Int b)
	-> detail::xrange_t<std::reverse_iterator<detail::xrange_iter<Int>>>
	// precondition: 0 <= b
{
	return { make_reverse_iterator(detail::xrange_iter<Int>(b)),
	         make_reverse_iterator(detail::xrange_iter<Int>(Int())) };
}

template <typename Int>
constexpr auto rxrange(Int a, Int b)
	-> detail::xrange_t<std::reverse_iterator<detail::xrange_iter<Int>>>
	// precondition: a <= b
{
	return { make_reverse_iterator(detail::xrange_iter<Int>(b)),
	         make_reverse_iterator(detail::xrange_iter<Int>(a)) };
}

}

#endif
