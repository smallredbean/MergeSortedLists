#ifndef __MY_N_WAY_MERGE_H__
#define __MY_N_WAY_MERGE_H__

#include <algorithm>
#include <vector>

#include "my_heap.h"

/* Merge N sorted lists (denoted by its "begin" and "end" iterators) into
 * one sorted list (stored into `output_list`); `output_list` can be any data
 * structure given supporting "push_back()" function call.
 *
 * Using begin/end iterators for merging allows the input sorted lists remain
 * (the contents won't be altered after merging).
 *
 * This merging involves heap sort and the heapification is based on `Compare`;
 * `Compare` is NOT for sorting. In general, for lists that are sorted using
 * std::less<>, `Compare` should be std::greater<>.
 *
 * The time complexity is O(M * logN) where M is the size of the
 * final sorted list.
 */

template <class Compare, class SortedListInIteratorPair>
class CompareFunction{
private:
	Compare comp;

public:
	bool operator()(const SortedListInIteratorPair &p1, const SortedListInIteratorPair &p2) const
	{
		return comp(*(p1.first), *(p2.first));
	}
};


template <class Compare, class SortedListIterator, class OutputContainer>
void my_n_way_merge(
	std::vector< std::pair<SortedListIterator, SortedListIterator> > sorted_lists_in_iterator_pair,
	OutputContainer &output_list)
{
	if (sorted_lists_in_iterator_pair.empty()) {
		return;
	}

	typedef std::pair<SortedListIterator, SortedListIterator> SortedListInIteratorPair;
	auto compare_func = CompareFunction<Compare, SortedListInIteratorPair>();

	// Heap is used to track which sorted list has the next data
	// going into `output_list` in O(logN) of time
	auto &heap = sorted_lists_in_iterator_pair;
	auto heap_size = heap.size();
	heap.push_back(heap.front()); // Extra space for replace_heap/pushpop_heap

	// Initial check on lists
	auto heap_end = heap.end() - 1;
	for (auto it = heap.begin(); it < heap_end; ++it) {
		if (it->first >= it->second) { // Empty or invalid list, Remove It:
			// 1. Replace it with the last one & update the end pointer
			// The following line of code is equivalent to (optimization trick!)
			//	 *it = *(heap_end - 1);
			//	 heap_end -= 1;
			*it = *(--heap_end);
			// 2. Update relevant variables
			--heap_size;
			// 3. Recheck this newly copied list in the next iteration
			--it;
		}
	}

	// Make a heap
	std::make_heap(heap.begin(), heap.begin() + heap_size, compare_func);

	// Iterate through until all lists are merged in
	while (heap_size > 0) {
		// The next element to output_list is pointed by heap.front().first
		output_list.push_back(*(heap.front().first));
		// Then, the list heap.front() "pushes"* its next element to the heap by
		// moving its begin iterator to the next element.
		++heap.front().first;

		auto heap_begin = heap.begin();
		if (heap_begin->first == heap_begin->second) {
			// The list has no more data, remove it from the heap
			std::pop_heap(heap_begin, heap_begin + heap_size, compare_func);
			--heap_size;
		}
		else {
			// Pop old (ignore it) and push new (the above *); new data at heap.front()
			replace_heap(heap_begin, heap_begin + heap_size + 1, *heap_begin, compare_func);
		}
	}
}


template <class Compare, class SortedList, class SortedListsIterator, class OutputContainer>
void my_n_way_merge(
	const SortedListsIterator sorted_lists_begin,
	const SortedListsIterator sorted_lists_end,
	OutputContainer &output_list)
{
	if (sorted_lists_begin == sorted_lists_end) {
		return;
	}

	typedef std::pair<
		typename SortedList::const_iterator,
		typename SortedList::const_iterator
	> SortedListInIteratorPair;
	std::vector<SortedListInIteratorPair> inputs;

	for (auto it = sorted_lists_begin; it != sorted_lists_end; ++it) {
		inputs.push_back(
			SortedListInIteratorPair(it->cbegin(), it->cend())
		);
	}

	my_n_way_merge<Compare>(inputs, output_list);
}
#endif
