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
         int_sort_std = new std::map<int, int>;
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

TEST_F(Test_Vector, Constructor_fill) {
	{
		std::vector<int> ctnr_std(5);
		ft::Vector<int> ctnr_ft(5);

		std::cout << "----- CONSTRUCTOR (fill) -----" << std::endl;
		compare_content(ctnr_std, ctnr_ft);

		EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
		EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
	}
	{
		std::vector<std::string> ctnr_std(2, "test");
		ft::Vector<std::string> ctnr_ft(2, "test");

		std::cout << "----- CONSTRUCTOR (fill) -----" << std::endl;
		compare_content(ctnr_std, ctnr_ft);

		EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
		EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
	}
}
