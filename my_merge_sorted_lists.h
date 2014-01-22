#include <algorithm>
#include <vector>

#include "my_heap.h"

/* Merge N sorted lists (denoted by its "begin" and "end" iterator) into
 * one sorted list (stored into `output_list`); `output_list` can be any data
 * structure given supporting "push_back()" function call.
 *
 * This merging involves heap sort and the heapification is based on `Compare`;
 * `Compare` is NOT for sorting. In general, for lists that are sorted using
 * std::less<>, `Compare` should be std::greater<>.
 *
 * The time complexity is O(M * logN) where M is the size of the
 * final sorted list.
 */
template <class Compare, class SortedListIterator, class OutputContainer>
void my_merge_sorted_lists(
	std::vector< std::pair<SortedListIterator, SortedListIterator> > sorted_lists_in_iterator_pair,
	OutputContainer &output_list)
{
	if(sorted_lists_in_iterator_pair.empty())
		return;

	typedef std::pair<SortedListIterator, SortedListIterator> SortedListInIteratorPair;
	auto compare_func = [](
		const SortedListInIteratorPair &p1,
		const SortedListInIteratorPair &p2
	){
		return Compare()(*(p1.first), *(p2.first));
   	};

	// Heap is used to track which sorted list has the next data
	// going into `output_list` in O(logN) of time
	auto &heap = sorted_lists_in_iterator_pair;
	auto heap_size = heap.size();
	heap.push_back(heap.front()); // Extra space for replace_heap/pushpop_heap

	auto heap_end = heap.end()-1;
	for(auto it=heap.begin(); it<heap_end; ++it)
		if(it->first>=it->second){ // Empty or invalid list
			*it = *(--heap_end); // Exclude it by copying one from the back
			--heap_size;
			--it; // So that the newly copied one would be checked
		}
	
	std::make_heap(heap.begin(), heap.begin()+heap_size, compare_func);

	while(heap_size>0){
		output_list.push_back(*(heap.front().first++));

		auto heap_begin = heap.begin();
		if(heap_begin->first==heap_begin->second)
			// The list has no more data, remove it from the heap
			pop_heap(heap_begin, heap_begin+(heap_size--), compare_func);
		else
			replace_heap(heap_begin, heap_begin+heap_size+1, *heap_begin, compare_func);
	}
}


template <class Compare, class SortedList, class SortedListsIterator, class OutputContainer>
void my_merge_sorted_lists(
	const SortedListsIterator sorted_lists_begin,
	const SortedListsIterator sorted_lists_end,
	OutputContainer &output_list)
{
	if(sorted_lists_begin==sorted_lists_end)
		return;

	typedef std::pair<
		typename SortedList::const_iterator,
   		typename SortedList::const_iterator
	> SortedListInIteratorPair;
	std::vector<SortedListInIteratorPair> inputs;

	for(auto it=sorted_lists_begin; it!=sorted_lists_end; ++it)
		inputs.push_back(
			SortedListInIteratorPair(it->begin(), it->end())
		);

	my_merge_sorted_lists<Compare>(inputs, output_list);
}
