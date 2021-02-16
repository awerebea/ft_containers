/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:24:45 by awerebea          #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <map>
#include "all_test_utils.hpp"
#include "Map.hpp"

class Test_Map : public ::testing::Test {
protected:
	void SetUp() {
		int_sort_std= new std::map<int, int>;
		for (int i = 0; i < 9; ) {
			int_sort_std->insert(std::make_pair(i + 1, i + 1));
			i += 1;
		}
		int_sort_ft = new ft::Map<int, int>;
		for (int i = 0; i < 9; ) {
			int_sort_ft->insert(std::make_pair(i + 1, i + 1));
			i += 1;
		}
		int unsort_int_arr[] = { 8, 0, 6, 9, 7, 33, 44, 11, 22 };
		int_unsort_std = new std::map<int, int>;
		for (int i = 0; i < 9; ++i) {
			int_unsort_std->insert(std::make_pair(unsort_int_arr[i],
										unsort_int_arr[i]));
		}
		int_unsort_ft = new ft::Map<int, int>;
		for (int i = 0; i < 9; ++i) {
			int_unsort_ft->insert(std::make_pair(unsort_int_arr[i],
										unsort_int_arr[i]));
		}
	}
	void TearDown() {
		delete int_sort_std;
		delete int_sort_ft;

		delete int_unsort_std;
		delete int_unsort_ft;
	}
	std::map<int, int> * int_sort_std;
	ft::Map<int, int> * int_sort_ft;

	std::map<int, int> * int_unsort_std;
	ft::Map<int, int> * int_unsort_ft;
};

TEST_F(Test_Map, Constructor_Default) {
	std::map<int, int> ctnr_std;
	ft::Map<int, int> ctnr_ft;
	std::cout << "----- CONSTRUCTOR (default) -----" << std::endl;
	compare_size(ctnr_std, ctnr_ft);
	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
}

TEST_F(Test_Map, Constructor_Range) {
	std::map<int, int>	ctnr_std_cpy(++(*int_sort_std).begin(),
			--(*int_sort_std).end());
	ft::Map<int, int>	ctnr_ft_cpy(++(*int_sort_ft).begin(),
			--(*int_sort_ft).end());

	std::cout << "----- CONSTRUCTOR (range) -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft, " original");
	compare_content_pair(ctnr_std_cpy, ctnr_ft_cpy, " ranged");
	EXPECT_EQ(*ctnr_std_cpy.begin(), *ctnr_ft_cpy.begin());
	EXPECT_EQ(*(--ctnr_std_cpy.end()), *(--ctnr_ft_cpy.end()));
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(ctnr_std_cpy.size(), ctnr_ft_cpy.size());
}

TEST_F(Test_Map, Constructor_Copy) {
	std::map<int, int>	ctnr_std_cpy(*int_unsort_std);
	ft::Map<int, int>	ctnr_ft_cpy(*int_unsort_ft);

	std::cout << "----- CONSTRUCTOR (copy) -----" << std::endl;
	compare_content_pair(*int_unsort_std, *int_unsort_ft, " original");
	compare_content_pair(ctnr_std_cpy, ctnr_ft_cpy, " copy");
	EXPECT_EQ(*ctnr_std_cpy.begin(), *ctnr_ft_cpy.begin());
	EXPECT_EQ(*(--ctnr_std_cpy.end()), *(--ctnr_ft_cpy.end()));
	EXPECT_EQ(int_unsort_std->size(), ctnr_std_cpy.size());
	EXPECT_EQ(int_unsort_ft->size(), ctnr_ft_cpy.size());
}

TEST_F(Test_Map, Destructor) {
	std::map<int, int>*	ctnr_std = new std::map<int, int>(*int_sort_std);
	ft::Map<int, int>*	ctnr_ft = new ft::Map<int, int>(*int_sort_ft);

	std::cout << "----- DESTRUCTOR -----" << std::endl;
	delete(ctnr_std);
	delete(ctnr_ft);
}

TEST_F(Test_Map, Operator_Assign) {
	std::map<int, int>	ctnr_std_cpy;
	ft::Map<int, int>	ctnr_ft_cpy;

	ctnr_std_cpy = *int_sort_std;
	ctnr_ft_cpy = *int_sort_ft;

	std::cout << "----- OPERATOR =  -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	std::cout << std::endl;
	compare_content_pair(ctnr_std_cpy, ctnr_ft_cpy, " copy");
	compare_size(ctnr_std_cpy, ctnr_ft_cpy, " copy");

	EXPECT_EQ(*ctnr_std_cpy.begin(), *ctnr_ft_cpy.begin());
	EXPECT_EQ(*(--ctnr_std_cpy.end()), *(--ctnr_ft_cpy.end()));
	EXPECT_EQ(int_sort_std->size(), ctnr_std_cpy.size());
	EXPECT_EQ(int_sort_ft->size(), ctnr_ft_cpy.size());
}

TEST_F(Test_Map, Iterators_Begin) {
	std::cout << "----- ITERATOR BEGIN -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);
	compare_iterators_pair(int_sort_std->begin(), int_sort_ft->begin(),
			"   begin");
	compare_iterators_pair(++int_sort_std->begin(), ++int_sort_ft->begin(),
			" ++begin");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*(++int_sort_std->begin()), *(++int_sort_ft->begin()));
}

TEST_F(Test_Map, Iterators_End) {
	std::cout << "----- ITERATOR END -----" << std::endl;
	std::map<int, int>::iterator it_std = --int_sort_std->end();
	ft::Map<int, int>::iterator it_ft = --int_sort_ft->end();
	compare_content_pair(*int_sort_std, *int_sort_ft);
	compare_iterators_pair(it_std, it_ft, "    --end");
	compare_iterators_pair(--it_std, --it_ft, " --(--end)");
	EXPECT_EQ(*(--int_sort_std->end()), *(--int_sort_ft->end()));
	EXPECT_EQ(*(--it_std), *(--it_ft));
}

TEST_F(Test_Map, Iterators_Rbegin) {
	std::cout << "----- ITERATOR RBEGIN -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);
	compare_iterators_pair(int_sort_std->rbegin(), int_sort_ft->rbegin(),
			"   rbegin");
	compare_iterators_pair(++int_sort_std->rbegin(), ++int_sort_ft->rbegin(),
			" ++rbegin");
	EXPECT_EQ(*int_sort_std->rbegin(), *int_sort_ft->rbegin());
	EXPECT_EQ(*(++int_sort_std->rbegin()), *(++int_sort_ft->rbegin()));
}

TEST_F(Test_Map, Iterators_Rend) {
	std::cout << "----- ITERATOR REND -----" << std::endl;
	std::map<int, int>::reverse_iterator it_std = --int_sort_std->rend();
	ft::Map<int, int>::reverse_iterator it_ft = --int_sort_ft->rend();
	compare_content_pair(*int_sort_std, *int_sort_ft);
	compare_iterators_pair(it_std, it_ft, "    --rend");
	compare_iterators_pair(--it_std, --it_ft, " --(--rend)");
	EXPECT_EQ(*(--int_sort_std->rend()), *(--int_sort_ft->rend()));
	EXPECT_EQ(it_std->first, it_ft->first);
	EXPECT_EQ(it_std->second, it_ft->second);
}

TEST_F(Test_Map, Capacity_Empty) {
	std::cout << "----- EMPTY -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	std::cout << "std empty: " << std::boolalpha << int_sort_std->empty()
		<< std::endl;
	std::cout << " ft empty: " << std::boolalpha << int_sort_ft->empty()
		<< std::endl;

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->empty(), int_sort_ft->empty());

	std::cout << std::endl;
	std::cout << "Clear containers" << std::endl;
	int_sort_std->clear();
	int_sort_ft->clear();

	compare_content_pair(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	std::cout << "std empty: " << std::boolalpha << int_sort_std->empty()
		<< std::endl;
	std::cout << " ft empty: " << std::boolalpha << int_sort_ft->empty()
		<< std::endl;

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->empty(), int_sort_ft->empty());
}

TEST_F(Test_Map, Capacity_Size) {
	std::cout << "----- SIZE -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Clear containers" << std::endl;
	int_sort_std->clear();
	int_sort_ft->clear();

	compare_content_pair(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_Map, Capacity_Max_size) {
	std::cout << "----- MAX SIZE -----" << std::endl;
	std::cout << "std max_size: " << int_sort_std->max_size() << std::endl;
	std::cout << " ft max_size: " << int_sort_ft->max_size() << std::endl;
	EXPECT_EQ(int_sort_std->max_size(), int_sort_ft->max_size());
}

TEST_F(Test_Map, Element_access_Operator_square_braskets) {
	std::cout << "----- OPERATOR [] -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	std::cout << std::endl;
	std::cout << "Query for existing elements:" << std::endl;
	compare_elements((*int_sort_std)[1], (*int_sort_ft)[1], "[1]");
	compare_elements((*int_sort_std)[3], (*int_sort_ft)[3], "[3]");
	std::cout << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	EXPECT_EQ((*int_sort_std)[1], (*int_sort_ft)[1]);
	EXPECT_EQ((*int_sort_std)[3], (*int_sort_ft)[3]);
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Query for non-existent element [4]:" << std::endl;
	compare_elements((*int_sort_std)[4], (*int_sort_ft)[4], "[4]");
	std::cout << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	EXPECT_EQ((*int_sort_std)[4], (*int_sort_ft)[4]);
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Query non-existent element [6] with value assignment:"
		<< std::endl;
	compare_elements((*int_sort_std)[6] = 6, (*int_sort_ft)[6] = 6, "[4]");
	std::cout << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	EXPECT_EQ((*int_sort_std)[6], (*int_sort_ft)[6]);
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_Map, Modifiers_Insert_single_element) {
	std::cout << "----- INSERT (single element) -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::boolalpha << std::endl;
	std::cout << "Insert '77 (77)'" << std::endl;

	std::pair<std::map<int, int>::iterator, bool> ret_std;
	ret_std = int_sort_std->insert(std::make_pair(77, 77));
	std::pair<ft::Map<int, int>::iterator, bool> ret_ft;
	ret_ft = int_sort_ft->insert(std::make_pair(77, 77));

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_iterators_pair(ret_std.first, ret_ft.first);
	std::cout << "Element was inserted:" << std::endl;
	compare_elements(ret_std.second, ret_ft.second, " result");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(ret_std.first->first, ret_ft.first->first);
	EXPECT_EQ(ret_std.first->second, ret_ft.first->second);
	EXPECT_EQ(ret_std.second, ret_ft.second);

	std::cout << std::boolalpha << std::endl;
	std::cout << "Insert '-100 (-100)'" << std::endl;

	ret_std = int_sort_std->insert(std::make_pair(-100, -100));
	ret_ft = int_sort_ft->insert(std::make_pair(-100, -100));

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_iterators_pair(ret_std.first, ret_ft.first);
	std::cout << "Element was inserted:" << std::endl;
	compare_elements(ret_std.second, ret_ft.second, " result");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(ret_std.first->first, ret_ft.first->first);
	EXPECT_EQ(ret_std.first->second, ret_ft.first->second);
	EXPECT_EQ(ret_std.second, ret_ft.second);

	std::cout << std::boolalpha << std::endl;
	std::cout << "Insert '0 (0)'" << std::endl;

	ret_std = int_sort_std->insert(std::make_pair(0, 0));
	ret_ft = int_sort_ft->insert(std::make_pair(0, 0));

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_iterators_pair(ret_std.first, ret_ft.first);
	std::cout << "Element was inserted:" << std::endl;
	compare_elements(ret_std.second, ret_ft.second, " result");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(ret_std.first->first, ret_ft.first->first);
	EXPECT_EQ(ret_std.first->second, ret_ft.first->second);
	EXPECT_EQ(ret_std.second, ret_ft.second);

	std::cout << std::boolalpha << std::endl;
	std::cout << "Insert '5 (888)' (duplicate!)" << std::endl;

	ret_std = int_sort_std->insert(std::make_pair(5, 888));
	ret_ft = int_sort_ft->insert(std::make_pair(5, 888));

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_iterators_pair(ret_std.first, ret_ft.first);
	std::cout << "Element was inserted:" << std::endl;
	compare_elements(ret_std.second, ret_ft.second, " result");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(ret_std.first->first, ret_ft.first->first);
	EXPECT_EQ(ret_std.first->second, ret_ft.first->second);
	EXPECT_EQ(ret_std.second, ret_ft.second);
}

TEST_F(Test_Map, Modifiers_Insert_hint) {
	std::cout << "----- INSERT (hint) -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::boolalpha << std::endl;
	std::cout << "Insert '77 (77)'" << std::endl;

	std::map<int, int>::iterator ret_std;
	ret_std = int_sort_std->insert(int_sort_std->begin(),
								std::make_pair(77, 77));
	ft::Map<int, int>::iterator ret_ft;
	ret_ft = int_sort_ft->insert(int_sort_ft->begin(),
							std::make_pair(77, 77));

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_iterators_pair(ret_std, ret_ft);
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(ret_std->first, ret_ft->first);
	EXPECT_EQ(ret_std->second, ret_ft->second);

	std::cout << std::boolalpha << std::endl;
	std::cout << "Insert '-100 (-100)'" << std::endl;

	ret_std = int_sort_std->insert(int_sort_std->begin(),
			std::make_pair(-100, -100));
	ret_ft = int_sort_ft->insert(int_sort_ft->begin(),
			std::make_pair(-100, -100));

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_iterators_pair(ret_std, ret_ft);
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(ret_std->first, ret_ft->first);
	EXPECT_EQ(ret_std->second, ret_ft->second);

	std::cout << std::boolalpha << std::endl;
	std::cout << "Insert '0 (0)'" << std::endl;

	ret_std = int_sort_std->insert(int_sort_std->begin(), std::make_pair(0, 0));
	ret_ft = int_sort_ft->insert(int_sort_ft->begin(), std::make_pair(0, 0));

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_iterators_pair(ret_std, ret_ft);
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(ret_std->first, ret_ft->first);
	EXPECT_EQ(ret_std->second, ret_ft->second);

	std::cout << std::boolalpha << std::endl;
	std::cout << "Insert '3 (888)' (duplicate!)" << std::endl;

	ret_std = int_sort_std->insert(int_sort_std->begin(),
			std::make_pair(3, 888));
	ret_ft = int_sort_ft->insert(int_sort_ft->begin(), std::make_pair(3, 888));

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_iterators_pair(ret_std, ret_ft);
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(ret_std->first, ret_ft->first);
	EXPECT_EQ(ret_std->second, ret_ft->second);
}

TEST_F(Test_Map, Modifiers_Insert_range) {
	std::cout << "----- INSERT (range) -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft, "_first before");
	compare_size(*int_sort_std, *int_sort_ft, "_first before");
	std::cout << std::endl;
	compare_content_pair(*int_unsort_std, *int_unsort_ft, "_second");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Insert to first " << "from second range [++begin(), --end())"
		<< std::endl;

	int_sort_std->insert(++int_unsort_std->begin(), --int_unsort_std->end());
	int_sort_ft->insert( ++int_unsort_ft->begin(), --int_unsort_ft->end());

	compare_content_pair(*int_sort_std, *int_sort_ft, "_first after");
	compare_size(*int_sort_std, *int_sort_ft, "_first after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_Map, Modifiers_Erase_position) {
	std::cout << "----- ERASE (position) -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Erase begin() element" << std::endl;

	int_sort_std->erase(int_sort_std->begin());
	int_sort_ft->erase(int_sort_ft->begin());

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(int_sort_std->begin()->first,
			int_sort_ft->begin()->first);
	EXPECT_EQ(int_sort_std->begin()->second,
			int_sort_ft->begin()->second);
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;

	std::map<int, int>::iterator it_std_first = --int_sort_std->end();
	ft::Map<int, int>::iterator it_ft_first = --int_sort_ft->end();

	std::map<int, int>::iterator it_std_second = it_std_first;
	ft::Map<int, int>::iterator it_ft_second = it_ft_first;

	--it_std_second;
	--it_ft_second;

	compare_iterators_pair(it_std_first, it_ft_first, " --end()  before");

	std::cout << std::endl;
	std::cout << "Erase --(--end())" << std::endl;

	int_sort_std->erase(it_std_second);
	int_sort_ft->erase(it_ft_second);

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");

	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	compare_iterators_pair(it_std_first, it_ft_first, " --end() after");

	EXPECT_EQ((--int_sort_std->end())->first,
			(--int_sort_ft->end())->first);
	EXPECT_EQ((--int_sort_std->end())->second,
			(--int_sort_ft->end())->second);
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_Map, Modifiers_Erase_key) {
	std::cout << "----- ERASE (key) -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Erase element with key '3'" << std::endl;

	size_t ret_std = int_sort_std->erase(3);
	size_t ret_ft = int_sort_ft->erase(3);

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_elements(ret_std, ret_ft, " result");
	compare_size(*int_sort_std, *int_sort_ft, " after");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(ret_std, ret_ft);

	std::cout << std::endl;
	std::cout << "Erase element with key '42'" << std::endl;

	ret_std = int_sort_std->erase(42);
	ret_ft = int_sort_ft->erase(42);

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_elements(ret_std, ret_ft, " result");
	compare_size(*int_sort_std, *int_sort_ft, " after");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(ret_std, ret_ft);
}

TEST_F(Test_Map, Modifiers_Erase_range) {
	std::cout << "----- ERASE (range) -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::map<int, int>::iterator it_std_first = ++int_sort_std->begin();
	std::map<int, int>::iterator it_std_second = --int_sort_std->end();
	ft::Map<int, int>::iterator it_ft_first = ++int_sort_ft->begin();
	ft::Map<int, int>::iterator it_ft_second = --int_sort_ft->end();

	// DEBUG
//	int_sort_ft->print();

	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	for (int i = 0; i < 3; i++) {
		++it_std_first;
		++it_ft_first;
		--it_std_second;
		--it_ft_second;
	}

//	for (int i = 0; i < 4; i++) {
//		++it_std_first;
//		++it_ft_first;
//	}
//	it_std_second = it_std_first;
//	it_ft_second = it_ft_first;
//	for (int i = 0; i < 3; i++) {
//		++it_std_second;
//		++it_ft_second;}

	compare_iterators_pair(it_std_first, it_ft_first, "_first");
	compare_iterators_pair(it_std_second, it_ft_second, "_second");

	std::cout << std::endl;
	std::cout << "Erase range" << std::endl;
	int_sort_std->erase(it_std_first, it_std_second);
	int_sort_ft->erase(it_ft_first, it_ft_second);

	// DEBUG
//	int_sort_ft->print();

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");

	std::cout << std::endl;
	std::cout << "Erase range [++begin(), --end())" << std::endl;
	int_sort_std->erase(++int_sort_std->begin(), --int_sort_std->end());
	int_sort_ft->erase(++int_sort_ft->begin(), --int_sort_ft->end());
	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_Map, Modifiers_Swap) {
	std::cout << "----- SWAP -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft, "_first before");
	compare_size(*int_sort_std, *int_sort_ft, "_first before");
	std::cout << std::endl;
	compare_content_pair(*int_unsort_std, *int_unsort_ft, "_second before");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second before");

	std::map<int, int>::iterator it_std_first = ++int_sort_std->begin();
	std::map<int, int>::iterator it_std_second = ++int_unsort_std->begin();
	ft::Map<int, int>::iterator it_ft_first = ++int_sort_ft->begin();
	ft::Map<int, int>::iterator it_ft_second = ++int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	compare_iterators_pair(it_std_first, it_ft_first, "_first  before");
	compare_iterators_pair(it_std_second, it_ft_second, "_second before");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());

	std::cout << std::endl;
	std::cout << "Swap first and second objects" << std::endl;

	int_sort_std->swap(*int_unsort_std);
	int_sort_ft->swap(*int_unsort_ft);

	compare_content_pair(*int_sort_std, *int_sort_ft, "_first after");
	compare_size(*int_sort_std, *int_sort_ft, "_first after");
	std::cout << std::endl;
	compare_content_pair(*int_unsort_std, *int_unsort_ft, "_second after");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second after");
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	compare_iterators_pair(it_std_first, it_ft_first, "_first after");
	compare_iterators_pair(it_std_second, it_ft_second, "_second after");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
}

TEST_F(Test_Map, Modifiers_Clear) {
std::cout << "----- CLEAR -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Clear containers" << std::endl;
	int_sort_std->clear();
	int_sort_ft->clear();

	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_Map, Observers_Key_compare) {
	std::cout << "----- KEY COMPARE -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);

	std::map<int,int>::key_compare mycomp_std = int_sort_std->key_comp();
	ft::Map<int,int>::key_compare mycomp_ft = int_sort_ft->key_comp();

	int highest_std = int_sort_std->rbegin()->first;
	int highest_ft = int_sort_ft->rbegin()->first;

	std::cout << std::endl;
	std::cout << "std:" << std::endl;
	std::map<int,int>::iterator it_std = int_sort_std->begin();
	do {
	std::cout << it_std->first << " => " << it_std->second << std::endl;
	} while (mycomp_std((*it_std++).first, highest_std));
	std::cout << std::endl;

	std::cout << "ft:" << std::endl;
	ft::Map<int,int>::iterator it_ft = int_sort_ft->begin();
	do {
	std::cout << it_ft->first << " => " << it_ft->second << std::endl;
	} while (mycomp_ft((*it_ft++).first, highest_ft));
}

TEST_F(Test_Map, Observers_Value_compare) {
	std::cout << "----- VALUE COMPARE -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);

	std::pair<int, int> highest_std = *int_sort_std->rbegin();
	std::pair<int, int> highest_ft = *int_sort_ft->rbegin();

	std::cout << std::endl;
	std::cout << "std:" << std::endl;
	std::map<int,int>::iterator it_std = int_sort_std->begin();
	do {
		std::cout << it_std->first << " => " << it_std->second << std::endl;
	} while (int_sort_std->value_comp()(*it_std++, highest_std));
	std::cout << std::endl;

	std::cout << "ft:" << std::endl;
	ft::Map<int,int>::iterator it_ft = int_sort_ft->begin();
	do {
		std::cout << it_ft->first << " => " << it_ft->second << std::endl;
	} while (int_sort_ft->value_comp()(*it_ft++, highest_ft));
}

TEST_F(Test_Map, Operations_Find) {
	std::cout << "----- FIND -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);

	std::cout << std::endl;
	std::cout << "Find [3]" << std::endl;
	compare_iterators_pair(int_sort_std->find(3), int_sort_ft->find(3));
	std::cout << std::endl;
	std::cout << "Find [7]" << std::endl;
	compare_iterators_pair(int_sort_std->find(7), int_sort_ft->find(7));
	std::cout << std::endl;
	std::cout << "Find [42] (non-existent)" << std::endl;
	std::cout << "std find(42): "
		<< int_sort_std->lower_bound(42)->first << " ("
		<< int_sort_std->lower_bound(42)->second << "), end(): "
		<< int_sort_std->end()->first << " ("
		<< int_sort_std->end()->second << ")" << std::endl;
	std::cout << " ft find(42): "
		<< int_sort_std->lower_bound(42)->first << " ("
		<< int_sort_std->lower_bound(42)->second << "), end(): "
		<< int_sort_std->end()->first << " ("
		<< int_sort_std->end()->second << ")" << std::endl;

	std::cout << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->find(3)->first, int_sort_ft->find(3)->first);
	EXPECT_EQ(int_sort_std->find(3)->second, int_sort_ft->find(3)->second);
	EXPECT_EQ(int_sort_std->find(7)->first, int_sort_ft->find(7)->first);
	EXPECT_EQ(int_sort_std->find(7)->second, int_sort_ft->find(7)->second);
	EXPECT_EQ(int_sort_std->find(42)->first, int_sort_std->end()->first);
	EXPECT_EQ(int_sort_std->find(42)->second, int_sort_std->end()->second);
	EXPECT_EQ(int_sort_ft->find(42)->first, int_sort_ft->end()->first);
	EXPECT_EQ(int_sort_ft->find(42)->second, int_sort_ft->end()->second);
}

TEST_F(Test_Map, Operations_Count) {
	std::cout << "----- COUNT -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);

	std::cout << std::endl;
	std::cout << "Count [3]" << std::endl;
	compare_elements(int_sort_std->count(3), int_sort_ft->count(3));
	std::cout << std::endl;
	std::cout << "Count [7]" << std::endl;
	compare_elements(int_sort_std->count(7), int_sort_ft->count(7));
	std::cout << std::endl;
	std::cout << "Count [42] (non-existent)" << std::endl;
	compare_elements(int_sort_std->count(42), int_sort_ft->count(42));

	std::cout << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->count(3), int_sort_ft->count(3));
	EXPECT_EQ(int_sort_std->count(42), int_sort_ft->count(42));
}

TEST_F(Test_Map, Operations_Lower_bound) {
	std::cout << "----- LOWER BOUND -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);

	std::cout << std::endl;
	std::cout << "Lower bound [3]" << std::endl;
	compare_iterators_pair(int_sort_std->lower_bound(3),
						int_sort_ft->lower_bound(3));
	std::cout << std::endl;
	std::cout << "Lower bound [4] (non-existent, middle value)" << std::endl;
	compare_iterators_pair(int_sort_std->lower_bound(4),
			int_sort_ft->lower_bound(4));
	std::cout << std::endl;
	std::cout << "Lower bound [42] (non-existent, upper then all others), "
		"compare with end()" << std::endl;
	std::cout << "std lower_bound(42): "
		<< int_sort_std->lower_bound(42)->first << " ("
		<< int_sort_std->lower_bound(42)->second << "), end(): "
		<< int_sort_std->end()->first << " ("
		<< int_sort_std->end()->second << ")" << std::endl;
	std::cout << " ft lower_bound(42): "
		<< int_sort_std->lower_bound(42)->first << " ("
		<< int_sort_std->lower_bound(42)->second << "), end(): "
		<< int_sort_std->end()->first << " ("
		<< int_sort_std->end()->second << ")" << std::endl;

	std::cout << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->lower_bound(3)->first,
				int_sort_ft->lower_bound(3)->first);
	EXPECT_EQ(int_sort_std->lower_bound(3)->second,
				int_sort_ft->lower_bound(3)->second);
	EXPECT_EQ(int_sort_std->lower_bound(4)->first,
				int_sort_ft->lower_bound(4)->first);
	EXPECT_EQ(int_sort_std->lower_bound(4)->second,
				int_sort_ft->lower_bound(4)->second);
	EXPECT_EQ(int_sort_std->lower_bound(42)->first,
				int_sort_std->end()->first);
	EXPECT_EQ(int_sort_std->lower_bound(42)->second,
				int_sort_std->end()->second);
	EXPECT_EQ(int_sort_ft->lower_bound(42)->first,
				int_sort_ft->end()->first);
	EXPECT_EQ(int_sort_ft->lower_bound(42)->second,
				int_sort_ft->end()->second);
}

TEST_F(Test_Map, Operations_Upper_bound) {
	std::cout << "----- UPPER BOUND -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);

	std::cout << std::endl;
	std::cout << "Upper bound [3]" << std::endl;
	compare_iterators_pair(int_sort_std->upper_bound(3),
			int_sort_ft->upper_bound(3));
	std::cout << std::endl;
	std::cout << "Upper bound [4] (non-existent, middle value)" << std::endl;
	compare_iterators_pair(int_sort_std->upper_bound(4),
			int_sort_ft->upper_bound(4));
	std::cout << std::endl;
	std::cout << "Upper bound [42] (non-existent, upper then all others), "
		"compare with end()" << std::endl;
	std::cout << "std upper_bound(42): "
		<< int_sort_std->upper_bound(42)->first << " ("
		<< int_sort_std->upper_bound(42)->second << "), end(): "
		<< int_sort_std->end()->first << " ("
		<< int_sort_std->end()->second << ")" << std::endl;
	std::cout << " ft upper_bound(42): "
		<< int_sort_std->upper_bound(42)->first << " ("
		<< int_sort_std->upper_bound(42)->second << "), end(): "
		<< int_sort_std->end()->first << " ("
		<< int_sort_std->end()->second << ")" << std::endl;

	std::cout << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->upper_bound(3)->first,
				int_sort_ft->upper_bound(3)->first);
	EXPECT_EQ(int_sort_std->upper_bound(3)->second,
				int_sort_ft->upper_bound(3)->second);
	EXPECT_EQ(int_sort_std->upper_bound(4)->first,
				int_sort_ft->upper_bound(4)->first);
	EXPECT_EQ(int_sort_std->upper_bound(4)->second,
				int_sort_ft->upper_bound(4)->second);
	EXPECT_EQ(int_sort_std->upper_bound(42)->first,
				int_sort_std->end()->first);
	EXPECT_EQ(int_sort_std->upper_bound(42)->second,
				int_sort_std->end()->second);
	EXPECT_EQ(int_sort_ft->upper_bound(42)->first,
				int_sort_ft->end()->first);
	EXPECT_EQ(int_sort_ft->upper_bound(42)->second,
				int_sort_ft->end()->second);
}

TEST_F(Test_Map, Operations_Equal_range) {
	std::cout << "----- EQUAL RANGE -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);

	std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator>
		eq_range_std;
	std::pair<ft::Map<int, int>::iterator, ft::Map<int, int>::iterator>
		eq_range_ft;

	std::cout << std::endl;
	std::cout << "Equal range [3]" << std::endl;
	eq_range_std = int_sort_std->equal_range(3);
	eq_range_ft = int_sort_ft->equal_range(3);
	compare_iterators_pair(eq_range_std.first, eq_range_ft.first, " first");
	compare_iterators_pair(eq_range_std.second, eq_range_ft.second, " second");

	std::cout << std::endl;
	std::cout << "Equal range [4] (non-existent, middle value)" << std::endl;
	eq_range_std = int_sort_std->equal_range(4);
	eq_range_ft = int_sort_ft->equal_range(4);
	compare_iterators_pair(eq_range_std.first, eq_range_ft.first, " first");
	compare_iterators_pair(eq_range_std.second, eq_range_ft.second, " second");

	std::cout << std::endl;
	std::cout << "Equal range [42] (non-existent, upper then all others), "
		"compare with end()" << std::endl;
	eq_range_std = int_sort_std->equal_range(42);
	eq_range_ft = int_sort_ft->equal_range(42);
	std::cout << "std equal_range(42)->first: "
		<< eq_range_std.first->first << " ("
		<< eq_range_std.first->second << "), end(): "
		<< int_sort_std->end()->first << " ("
		<< int_sort_std->end()->second << ")" << std::endl;
	std::cout << "std equal_range(42)->second: "
		<< eq_range_std.second->first << " ("
		<< eq_range_std.second->second << "), end(): "
		<< int_sort_std->end()->first << " ("
		<< int_sort_std->end()->second << ")" << std::endl;
	std::cout << std::endl;
	std::cout << " ft equal_range(42)->first: "
		<< eq_range_ft.first->first << " ("
		<< eq_range_ft.first->second << "), end(): "
		<< int_sort_ft->end()->first << " ("
		<< int_sort_ft->end()->second << ")" << std::endl;
	std::cout << " ft equal_range(42)->second: "
		<< eq_range_ft.second->first << " ("
		<< eq_range_ft.second->second << "), end(): "
		<< int_sort_ft->end()->first << " ("
		<< int_sort_ft->end()->second << ")" << std::endl;

	std::cout << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->equal_range(3).first->first,
				int_sort_ft->equal_range(3).first->first);
	EXPECT_EQ(int_sort_std->equal_range(3).first->second,
				int_sort_ft->equal_range(3).first->second);
	EXPECT_EQ(int_sort_std->equal_range(3).second->first,
				int_sort_ft->equal_range(3).second->first);
	EXPECT_EQ(int_sort_std->equal_range(3).second->second,
				int_sort_ft->equal_range(3).second->second);
	EXPECT_EQ(int_sort_std->equal_range(4).first->first,
				int_sort_ft->equal_range(4).first->first);
	EXPECT_EQ(int_sort_std->equal_range(4).first->second,
				int_sort_ft->equal_range(4).first->second);
	EXPECT_EQ(int_sort_std->equal_range(4).second->first,
				int_sort_ft->equal_range(4).second->first);
	EXPECT_EQ(int_sort_std->equal_range(4).second->second,
				int_sort_ft->equal_range(4).second->second);
	EXPECT_EQ(int_sort_std->equal_range(42).first->first,
				int_sort_std->end()->first);
	EXPECT_EQ(int_sort_std->equal_range(42).first->second,
				int_sort_std->end()->second);
	EXPECT_EQ(int_sort_std->equal_range(42).second->first,
				int_sort_std->end()->first);
	EXPECT_EQ(int_sort_std->equal_range(42).second->second,
				int_sort_std->end()->second);
	EXPECT_EQ(int_sort_ft->equal_range(42).first->first,
				int_sort_ft->end()->first);
	EXPECT_EQ(int_sort_ft->equal_range(42).first->second,
				int_sort_ft->end()->second);
	EXPECT_EQ(int_sort_ft->equal_range(42).second->first,
				int_sort_ft->end()->first);
	EXPECT_EQ(int_sort_ft->equal_range(42).second->second,
				int_sort_ft->end()->second);
}
