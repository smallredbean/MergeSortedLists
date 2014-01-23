#ifndef __MY_HEAP_H__
#define __MY_HEAP_H__

#include <algorithm>
#include <functional>


/* replace_heap(): pop_heap() first, then push_heap()
 *
 * The original heap (excluding `data`) must be at from `first` to `last-2`,
 * and `last-1` must be available for temporary use.
 *
 * Heapification is based on `comp`. In generatl,
 * std::less<>() for max-heap and std::greater<>() for min-heap.
 */
template <class RandomAccessIterator, class T, class Compare>
void replace_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	T data,
	Compare comp)
{
	if(last-first<=1)
		return;

	*(last-1) = data;
	std::pop_heap(first, last, comp);
}
template <class RandomAccessIterator, class T>
void replace_heap(RandomAccessIterator first, RandomAccessIterator last, T data)
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
	T data,
	Compare comp)
{
	if(last-first<=1)
		return;
	if(comp(*first, data))
		 return;

	replace_heap(first, last, data, comp);
}
template <class RandomAccessIterator, class T>
void pushpop_heap(RandomAccessIterator first, RandomAccessIterator last, T data)
{
	pushpop_heap(first, last, data, std::less<T>());
}
#endif
