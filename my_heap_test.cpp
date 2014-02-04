#include <algorithm>
using std::make_heap;
using std::pop_heap;
using std::push_heap;
#include <vector>
using std::vector;

#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "my_heap.h"


bool has_same_elements(const vector<int> &_v1, const vector<int> &_v2)
{
	vector<int> v1(_v1);
	vector<int> v2(_v2);
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	return v1 == v2;
}

bool is_heapified(const vector<int> &heap)
{
	vector<int> tmp(heap);
	make_heap(tmp.begin(), tmp.end());

	return heap == tmp;
}

void manual_unit_test_replace_heap(void)
{
	vector<int> v({5, 10, 15, 20, 30});
	make_heap(v.begin(), v.end());
	assert(has_same_elements({5, 10, 15, 20, 30}, v) && is_heapified(v));

	// Do replace_heap() w. data > current-max (i.e. 30)
	v.push_back(0); // Extra space for replace_heap & pushpop_heap
	replace_heap(v.begin(), v.end(), 35);
	v.pop_back();
	assert(has_same_elements({5, 10, 15, 20, 35}, v) && is_heapified(v));

	// Do replace_heap() w. data > new-max (i.e., 20)
	v.push_back(0); // Extra space for replace_heap & pushpop_heap
	replace_heap(v.begin(), v.end(), 21);
	v.pop_back();
	assert(has_same_elements({5, 10, 15, 20, 21}, v) && is_heapified(v));

	// Do replace_heap() w. data would go all the way down to the right subtree
	v.push_back(0); // Extra space for replace_heap & pushpop_heap
	replace_heap(v.begin(), v.end(), 14);
	v.pop_back();
	assert(has_same_elements({5, 10, 14, 15, 20}, v) && is_heapified(v));

	// Do replace_heap() w. data would go all the way down to the left subtree
	v.push_back(0); // Extra space for replace_heap & pushpop_heap
	replace_heap(v.begin(), v.end(), 8);
	v.pop_back();
	assert(has_same_elements({5, 8, 10, 14, 15}, v) && is_heapified(v));
}

void manual_unit_test_pushpop_heap(void)
{
	vector<int> v({5, 10, 15, 20, 30});
	make_heap(v.begin(), v.end());
	assert(has_same_elements({5, 10, 15, 20, 30}, v) && is_heapified(v));

	// Do pushpop_heap() w. data > current-max (i.e. 30)
	v.push_back(0); // Extra space for replace_heap & pushpop_heap
	pushpop_heap(v.begin(), v.end(), 35);
	v.pop_back();
	assert(has_same_elements({5, 10, 15, 20, 30}, v) && is_heapified(v));

	// Do pushpop_heap() w. data replace only the current-max
	v.push_back(0); // Extra space for replace_heap & pushpop_heap
	pushpop_heap(v.begin(), v.end(), 21);
	v.pop_back();
	assert(has_same_elements({5, 10, 15, 20, 21}, v) && is_heapified(v));

	// Do pushpop_heap() w. data would go all the way down to the right subtree
	v.push_back(0); // Extra space for replace_heap & pushpop_heap
	pushpop_heap(v.begin(), v.end(), 14);
	v.pop_back();
	assert(has_same_elements({5, 10, 14, 15, 20}, v) && is_heapified(v));

	// Do pushpop_heap() w. data would go all the way down to the left subtree
	v.push_back(0); // Extra space for replace_heap & pushpop_heap
	pushpop_heap(v.begin(), v.end(), 8);
	v.pop_back();
	assert(has_same_elements({5, 8, 10, 14, 15}, v) && is_heapified(v));
}

void manual_unit_tests(void)
{
	manual_unit_test_replace_heap();
	manual_unit_test_pushpop_heap();
}

void random_test(const int HEAP_SIZE = 10)
{
	const int NUM_TEST = 1000;

	// Initialize a heap with some amount of entries
	vector<int> v;
	for (auto size = 0; size < HEAP_SIZE; ++size) {
		v.push_back(random());
	}
	make_heap(v.begin(), v.end());

	vector<int> expected_results(v);

	for (auto num_test_case = NUM_TEST; num_test_case; --num_test_case) {
		int data = random();
		v.push_back(0); // Extra space for replace_heap & pushpop_heap
		if (random() % 2) { // Do replace_heap()
			replace_heap(v.begin(), v.end(), data);

			pop_heap(expected_results.begin(), expected_results.end());
			expected_results.back() = data;
			push_heap(expected_results.begin(), expected_results.end());
		}
		else { // Do pushpop_heap()
			pushpop_heap(v.begin(), v.end(), data);

			expected_results.push_back(data);
			push_heap(expected_results.begin(), expected_results.end());
			pop_heap(expected_results.begin(), expected_results.end());
			expected_results.pop_back();
		}
		v.pop_back();

		assert(has_same_elements(v, expected_results));
		assert(is_heapified(v));
	}
}

void random_unit_tests(void)
{
	srandom(time(NULL));

	const int NUM_TEST = 128;
	for (auto num_test_case = NUM_TEST; num_test_case; --num_test_case) {
		random_test(NUM_TEST);
	}
}

int main(int argc, char **argv)
{
	manual_unit_tests();
	random_unit_tests();
	return 0;
}
