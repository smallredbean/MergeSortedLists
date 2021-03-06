#ifndef __MY_DEBUG_TOOL_H__
#define __MY_DEBUG_TOOL_H__

#include <iostream>
using std::cout;
using std::endl;


template <class RandomAccessIterator>
void print_container(
	const RandomAccessIterator first,
	const RandomAccessIterator last)
{
	for (auto it = first; it != last; ++it) {
		cout << *it << ", ";
	}
	cout << endl;
}

template <class Container>
void print_container(const Container &c)
{
	print_container(c.cbegin(), c.cend());
}
#endif
