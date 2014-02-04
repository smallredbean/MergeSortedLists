#ifndef __MY_HEAP_H__
#define __MY_HEAP_H__

#include <algorithm>
#include <functional>

/* replace_heap() and pushpop_heap() in this file invovles optimization tricks
 * for saving runtime.
 *
 * For example, replace_heap() is equivalent to pop_heap() then push_heap(),
 * which takes two O(log N):
 * One for pop_heap():
 *	1. replace head of the heap with the last element
 *	2. heapify from the top
 * And the other for push_heap():
 *	1. given the new data is the last element, heapify from the bottom
 *
 * In fact, replace_heap() can be done as follows using one O(log N):
 * 1. replace head of the heap with the new data
 * 2. heapify from the top
 *
 * Similar trick applies to pushpop_heap().
 *
 * This implementation is motivated by Python's
 * heapq.heapreplace() and heapq.heappushpop().
 */




/* replace_heap(): pop_heap() first, then push_heap()
 *
 * The original heap (excluding `data`) must be at from `first` to `last-2`,
 * and `last-1` must be available for temporary use.
 *
 * Heapification is based on `comp`. In general,
 * std::less<>() for max-heap and std::greater<>() for min-heap.
 */
template <class RandomAccessIterator, class T, class Compare>
void replace_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	const T &data,
	const Compare &comp)
{
	if (last - first <= 1) {
		return;
	}

	*(last - 1) = data;
	std::pop_heap(first, last, comp);
}
template <class RandomAccessIterator, class T>
void replace_heap(RandomAccessIterator first, RandomAccessIterator last, const T &data)
{
	replace_heap(first, last, data, std::less<T>());
}

/* pushpop_heap(): push_heap() first, then pop_heap()
 *
 * The original heap (excluding `data`) must be at from `first` to `last-2`,
 * and `last-1` must be available for temporary use.
 *
 * Heapification is based on `comp`. In generatl,
 * std::less<>() for max-heap and std::greater<>() for min-heap.
 */
template <class RandomAccessIterator, class T, class Compare>
void pushpop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	const T &data,
	const Compare &comp)
{
	if (last - first <= 1) {
		return;
	}
	if (comp(*first, data)) {
		 return;
	}

	replace_heap(first, last, data, comp);
}
template <class RandomAccessIterator, class T>
void pushpop_heap(RandomAccessIterator first, RandomAccessIterator last, const T &data)
{
	pushpop_heap(first, last, data, std::less<T>());
}
#endif
