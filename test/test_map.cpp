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
		for (int i = 0; i < 5; ++i) {
			int_sort_std->insert(std::make_pair(i + 1, i + 1));
		}
		int_sort_ft = new ft::Map<int, int>;
		for (int i = 0; i < 5; ++i) {
			int_sort_ft->insert(std::make_pair(i + 1, i + 1));
		}
		int unsort_int_arr[] = { 8, 0, 6, 9, 7, 33, 44, 11, 22 };
		int_unsort_std = new std::map<int, int>;
		for (int i = 0; i < 9; ++i) {
			int_unsort_std->insert(std::make_pair(i + 1, unsort_int_arr[i]));
		}
		int_unsort_ft = new ft::Map<int, int>;
		for (int i = 0; i < 9; ++i) {
			int_unsort_ft->insert(std::make_pair(i + 1, unsort_int_arr[i]));
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

TEST_F(Test_Map, Constructor_default) {
	std::map<int, int> ctnr_std;
	ft::Map<int, int> ctnr_ft;
	std::cout << "----- CONSTRUCTOR (default) -----" << std::endl;
	compare_size(ctnr_std, ctnr_ft);
	 EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
}

TEST_F(Test_Map, Constructor_range) {
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

TEST_F(Test_Map, Constructor_copy) {
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

TEST_F(Test_Map, Operator_assign) {
	std::map<int, int>	ctnr_std_cpy;
	ft::Map<int, int>		ctnr_ft_cpy;

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




TEST_F(Test_Map, Modifiers_erase_position) {
	std::cout << "----- ERASE (position) -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	int_sort_std->erase(int_sort_std->begin());
	int_sort_ft->erase(int_sort_ft->begin());

	std::cout << std::endl;
	std::cout << "Erase begin() element" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_Map, Modifiers_erase_key) {
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

TEST_F(Test_Map, Modifiers_erase_range) {
	std::cout << "----- ERASE (range) -----" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	int_sort_std->erase(++int_sort_std->begin(), --int_sort_std->end());
	int_sort_ft->erase(++int_sort_ft->begin(), --int_sort_ft->end());

	std::cout << std::endl;
	std::cout << "Erase range [++begin(), --end())" << std::endl;
	compare_content_pair(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_Map, Modifiers_clear) {
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

