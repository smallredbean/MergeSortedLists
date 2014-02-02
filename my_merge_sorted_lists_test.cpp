#include <functional>
using std::greater;
using std::less;
#include <vector>
using std::vector;

#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "my_merge_sorted_lists.h"
#include "my_debug_util.h"


void manual_unit_test(
	const vector< vector<int> > &input_sorted_lists,
	const vector<int> &expected_results)
{
	vector<int> output;
	my_merge_sorted_lists< greater<int>, vector<int> >(
		input_sorted_lists.cbegin(),
		input_sorted_lists.cend(),
		output);
	assert(output == expected_results);
}

void manual_unit_tests(void)
{
	vector<int> v1({1, 9, 10, 11});
	vector<int> v2({3});
	vector<int> v3;
	vector<int> v4({2, 4, 12, 13});
	vector<int> v5({5, 6, 7, 8, 14, 15, 16, 17});
	vector<int> output;
	vector< vector<int> > sorted_lists;

	// A non-empty list w. more than one element
	sorted_lists.push_back(v1);
	manual_unit_test(sorted_lists, {1, 9, 10, 11});
	sorted_lists.clear();

	// A non-empty list w. one element
	sorted_lists.push_back(v2);
	manual_unit_test(sorted_lists, {3});
	sorted_lists.clear();

	// An empty list
	sorted_lists.push_back(v3);
	manual_unit_test(sorted_lists, {});
	sorted_lists.clear();

	// A non-empty + an empty
	sorted_lists.push_back(v1);
	sorted_lists.push_back(v3);
	manual_unit_test(sorted_lists, {1, 9, 10, 11});
	sorted_lists.clear();

	// An empty + A non-empty
	sorted_lists.push_back(v3);
	sorted_lists.push_back(v1);
	manual_unit_test(sorted_lists, {1, 9, 10, 11});
	sorted_lists.clear();

	// Two non-empty
	sorted_lists.push_back(v1);
	sorted_lists.push_back(v2);
	manual_unit_test(sorted_lists, {1, 3, 9, 10, 11});
	sorted_lists.clear();

	// Two empty
	sorted_lists.push_back(v3);
	sorted_lists.push_back(v3);
	manual_unit_test(sorted_lists, {});
	sorted_lists.clear();

	// An empty + a non-empty + An empty
	sorted_lists.push_back(v3);
	sorted_lists.push_back(v1);
	sorted_lists.push_back(v3);
	manual_unit_test(sorted_lists, {1, 9, 10, 11});
	sorted_lists.clear();

	// All 5 lists
	sorted_lists.push_back(v1);
	sorted_lists.push_back(v2);
	sorted_lists.push_back(v3);
	sorted_lists.push_back(v4);
	sorted_lists.push_back(v5);
	manual_unit_test(
		sorted_lists,
	   	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}
	);
	sorted_lists.clear();
}


void random_unit_tests(void)
{
	srandom(time(NULL));

	const int NUM_LIST = 50;
	const int MAX_LIST_SIZE = 10;
	const int NUM_TEST = 10;

	vector< vector<int> > sorted_lists(NUM_LIST);
	for (auto num_test_case = NUM_TEST; num_test_case; --num_test_case) {
		// Fill & sort lists
		for (auto it = sorted_lists.begin(); it != sorted_lists.end(); ++it) {
			for (auto size = random() % MAX_LIST_SIZE; size; --size) {
				it->push_back(random());
			}
			sort(it->begin(), it->end(), less<int>());
		}

		// Test merging k lists
		for (auto k = NUM_LIST; k; --k) {
			for (auto it = sorted_lists.begin(); it + k <= sorted_lists.end(); ++it) {
				vector<int> output;
				my_merge_sorted_lists< greater<int>, vector<int> >(it, it + k, output);
				
				vector<int> expected_results;
				for (auto it_list = it; it_list != it + k; ++it_list) {
					for (auto it_data = it_list->begin(); it_data != it_list->end(); ++it_data) {
						expected_results.push_back(*it_data);
					}
				}
				sort(expected_results.begin(), expected_results.end(), less<int>());

				assert(output == expected_results);
			}
		}
	}
}


int main(int argc, char **argv)
{
	manual_unit_tests();
	random_unit_tests();
	return 0;
}
