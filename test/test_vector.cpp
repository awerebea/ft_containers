/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:05:54 by awerebea          #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <vector>
#include "all_test_utils.hpp"
#include "Vector.hpp"

class Test_Vector : public ::testing::Test {
protected:
	void SetUp() {
		int_sort_std = new std::vector<int>;
		for (int i = 0; i < 5; ++i) {
			int_sort_std->push_back(i + 1);
		}
		int_sort_ft = new ft::Vector<int>;
		for (int i = 0; i < 5; ++i) {
			int_sort_ft->push_back(i + 1);
		}
		int unsort_int_array[] = { 8, 0, 6, 9, 7, 33, 11, 22 };
		int_unsort_std = new std::vector<int>;
		for (int i = 0; i < 6; ++i) {
			int_unsort_std->push_back(unsort_int_array[i]);
		}
		int_unsort_ft = new ft::Vector<int>;
		for (int i = 0; i < 6; ++i) {
			int_unsort_ft->push_back(unsort_int_array[i]);
		}
	}
	void TearDown() {
		delete int_sort_std;
		delete int_sort_ft;

		delete int_unsort_std;
		delete int_unsort_ft;
	}
	std::vector<int> * int_sort_std;
	ft::Vector<int> * int_sort_ft;

	std::vector<int> * int_unsort_std;
	ft::Vector<int> * int_unsort_ft;
};

TEST_F(Test_Vector, Constructor_default) {
	std::vector<int> cnt_std;
	ft::Vector<int> cnt_ft;
	std::cout << "----- CONSTRUCTOR (default) -----" << std::endl;
	compare_size(cnt_std, cnt_ft);

	EXPECT_EQ(cnt_std.size(), cnt_ft.size());
}

TEST_F(Test_Vector, Constructor_fill) {
	{
		std::vector<int> cnt_std(5);
		ft::Vector<int> cnt_ft(5);

		std::cout << "----- CONSTRUCTOR (fill) -----" << std::endl;
		compare_content(cnt_std, cnt_ft);

		EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
		EXPECT_EQ(cnt_std.size(), cnt_ft.size());
	}
	{
		std::vector<std::string> cnt_std(2, "test");
		ft::Vector<std::string> cnt_ft(2, "test");

		std::cout << "----- CONSTRUCTOR (fill) -----" << std::endl;
		compare_content(cnt_std, cnt_ft);

		EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
		EXPECT_EQ(cnt_std.size(), cnt_ft.size());
	}
}

TEST_F(Test_Vector, Constructor_range) {
	std::vector<int>	cnt_std_cpy(++(*int_sort_std).begin(),
									--(*int_sort_std).end());
	ft::Vector<int>	cnt_ft_cpy(++(*int_sort_ft).begin(),
								--(*int_sort_ft).end());

	std::cout << "----- CONSTRUCTOR (range) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " original");
	compare_content(cnt_std_cpy, cnt_ft_cpy, " ranged");
	EXPECT_EQ(*cnt_std_cpy.begin(), *cnt_ft_cpy.begin());
	EXPECT_EQ(*(--cnt_std_cpy.end()), *(--cnt_ft_cpy.end()));
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(cnt_std_cpy.size(), cnt_ft_cpy.size());
	EXPECT_EQ(cnt_std_cpy.capacity(), cnt_ft_cpy.capacity());
}

TEST_F(Test_Vector, Constructor_cpy) {
	std::vector<int>	cnt_std_cpy(*int_unsort_std);
	ft::Vector<int>		cnt_ft_cpy(*int_unsort_ft);

	std::cout << "----- CONSTRUCTOR (copy) -----" << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, " original");
	compare_content(cnt_std_cpy, cnt_ft_cpy, " copy");
	EXPECT_EQ(*cnt_std_cpy.begin(), *cnt_ft_cpy.begin());
	EXPECT_EQ(*(--cnt_std_cpy.end()), *(--cnt_ft_cpy.end()));
	EXPECT_EQ(int_unsort_std->size(), cnt_std_cpy.size());
	EXPECT_EQ(int_unsort_ft->size(), cnt_ft_cpy.size());
}

TEST_F(Test_Vector, Destructor) {
	std::vector<int>*	cnt_std = new std::vector<int>(5, 5);
	ft::Vector<int>*	cnt_ft = new ft::Vector<int>(5, 5);

	std::cout << "----- DESTRUCTOR -----" << std::endl;
	delete(cnt_std);
	delete(cnt_ft);
}

TEST_F(Test_Vector, Operator_assign) {
	std::vector<int>	cnt_std_cpy;
	ft::Vector<int>		cnt_ft_cpy;

	cnt_std_cpy = *int_sort_std;
	cnt_ft_cpy = *int_sort_ft;

	std::cout << "----- OPERATOR =  -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	compare_capacity(*int_sort_std, *int_sort_ft);
	std::cout << std::endl;
	compare_content(cnt_std_cpy, cnt_ft_cpy, " copy");
	compare_size(cnt_std_cpy, cnt_ft_cpy, " copy");
	compare_capacity(cnt_std_cpy, cnt_ft_cpy, " copy");

	EXPECT_EQ(*cnt_std_cpy.begin(), *cnt_ft_cpy.begin());
	EXPECT_EQ(*(--cnt_std_cpy.end()), *(--cnt_ft_cpy.end()));
	EXPECT_EQ(int_sort_std->size(), cnt_std_cpy.size());
	EXPECT_EQ(int_sort_ft->size(), cnt_ft_cpy.size());
	EXPECT_EQ(cnt_std_cpy.capacity(), cnt_ft_cpy.capacity());
}

TEST_F(Test_Vector, Capacity_empty) {
	std::cout << "----- EMPTY -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	compare_capacity(*int_sort_std, *int_sort_ft);
	std::cout << "std empty: " << std::boolalpha << int_sort_std->empty()
		<< std::endl;
	std::cout << " ft empty: " << std::boolalpha << int_sort_ft->empty()
		<< std::endl;

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
	EXPECT_EQ(int_sort_std->empty(), int_sort_ft->empty());

	std::cout << std::endl;
	std::cout << "Clear containers" << std::endl;
	int_sort_std->clear();
	int_sort_ft->clear();

	compare_content(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	compare_capacity(*int_sort_std, *int_sort_ft);
	std::cout << "std empty: " << std::boolalpha << int_sort_std->empty()
		<< std::endl;
	std::cout << " ft empty: " << std::boolalpha << int_sort_ft->empty()
		<< std::endl;

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
	EXPECT_EQ(int_sort_std->empty(), int_sort_ft->empty());
}

TEST_F(Test_Vector, Capacity_reserve) {
	std::cout << "----- RESERVE -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	compare_capacity(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());

	std::cout << std::endl;
	std::cout << "Reserve 2" << std::endl;
	int_sort_std->reserve(2);
	int_sort_ft->reserve(2);

	compare_content(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	compare_capacity(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());

	std::cout << std::endl;
	std::cout << "Reserve 15" << std::endl;
	int_sort_std->reserve(15);
	int_sort_ft->reserve(15);

	compare_content(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	compare_capacity(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
}

TEST_F(Test_Vector, Modifiers_assign_range) {
	std::cout << "----- ASSIGN (range) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " original");

	std::vector<int>	cnt_std_second;
	ft::Vector<int>		cnt_ft_second;

	std::cout << std::endl;
	compare_size(cnt_std_second, cnt_ft_second, "_second before");
	compare_capacity(cnt_std_second, cnt_ft_second, "_second before");

	std::cout << std::endl;
	std::cout << "Assign by range [++begin(), --end()) from original"
		<< std::endl;

	cnt_std_second.assign(++int_sort_std->begin(), --int_sort_std->end());
	cnt_ft_second.assign(++int_sort_ft->begin(), --int_sort_ft->end());

	compare_content(cnt_std_second, cnt_ft_second, " assigned");
	compare_size(cnt_std_second, cnt_ft_second, "_second after");
	compare_capacity(cnt_std_second, cnt_ft_second, "_second after");

	EXPECT_EQ(*cnt_std_second.begin(), *cnt_ft_second.begin());
	EXPECT_EQ(cnt_std_second.size(), cnt_ft_second.size());
	EXPECT_EQ(cnt_std_second.capacity(), cnt_ft_second.capacity());
}

TEST_F(Test_Vector, Modifiers_assign_fill) {
	std::cout << "----- ASSIGN (fill) -----" << std::endl;
	std::vector<int>	cnt_std;
	ft::Vector<int>		cnt_ft;
	compare_size(cnt_std, cnt_ft, " before");
	compare_capacity(cnt_std, cnt_ft, " before");

	std::cout << std::endl;
	std::cout << "Assign fill" << std::endl;

	cnt_std.assign(5, 7);
	cnt_ft.assign(5, 7);

	compare_content(cnt_std, cnt_ft, " assigned");
	compare_size(cnt_std, cnt_ft, " after");
	compare_capacity(cnt_std, cnt_ft, " after");

	EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
	EXPECT_EQ(cnt_std.size(), cnt_ft.size());
	EXPECT_EQ(cnt_std.capacity(), cnt_ft.capacity());
}

TEST_F(Test_Vector, Modifiers_insert_single_element) {
	{
		std::cout << "----- INSERT (single element) -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, " before");
		compare_size(*int_sort_std, *int_sort_ft, " before");
		compare_capacity(*int_sort_std, *int_sort_ft, " before");
		EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
		EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
		EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());

		std::cout << std::endl;
		std::cout << "Insert '8' before ++begin() element" << std::endl;

		int_sort_std->insert(++int_sort_std->begin(), 8);
		int_sort_ft->insert(++int_sort_ft->begin(), 8);

		compare_content(*int_sort_std, *int_sort_ft, " after");
		compare_size(*int_sort_std, *int_sort_ft, " after");
		compare_capacity(*int_sort_std, *int_sort_ft, " after");
		EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
		EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
		EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
	}
	{
		std::cout << "----- INSERT (single element) -----" << std::endl;
		std::vector<int>	cnt_std;
		ft::Vector<int>		cnt_ft;
		compare_size(cnt_std, cnt_ft, " before");
		compare_capacity(cnt_std, cnt_ft, " before");
		EXPECT_EQ(cnt_std.size(), cnt_ft.size());
		EXPECT_EQ(cnt_std.capacity(), cnt_ft.capacity());

		std::cout << std::endl;
		std::cout << "Insert '8' before end() element" << std::endl;

		cnt_std.insert(cnt_std.begin(), 8);
		cnt_ft.insert(cnt_ft.begin(), 8);

		compare_content(cnt_std, cnt_ft, " after");
		compare_size(cnt_std, cnt_ft, " after");
		compare_capacity(cnt_std, cnt_ft, " after");
		EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
		EXPECT_EQ(cnt_std.size(), cnt_ft.size());
		EXPECT_EQ(cnt_std.capacity(), cnt_ft.capacity());
	}
}

TEST_F(Test_Vector, Modifiers_insert_fill) {
	std::cout << "----- INSERT (fill) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	compare_capacity(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());

	std::cout << std::endl;
	std::cout << "Insert '8' 4 times before ++begin() element" << std::endl;

	int_sort_std->insert(++int_sort_std->begin(), 4, 8);
	int_sort_ft->insert(++int_sort_ft->begin(), 4, 8);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	compare_capacity(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
}

TEST_F(Test_Vector, Modifiers_insert_range) {
	{
		std::cout << "----- INSERT (range) -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first before");
		compare_size(*int_sort_std, *int_sort_ft, "_first before");
		compare_capacity(*int_sort_std, *int_sort_ft, "_first before");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");
		EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
		EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
		EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());

		std::cout << std::endl;
		std::cout << "Insert to first before ++begin() element "
			<< "from second range [++begin(), --end())" << std::endl;

		int_sort_std->insert(++int_sort_std->begin(),
				++int_unsort_std->begin(), --int_unsort_std->end());
		int_sort_ft->insert(++int_sort_ft->begin(),
				++int_unsort_ft->begin(), --int_unsort_ft->end());

		compare_content(*int_sort_std, *int_sort_ft, "_first after");
		compare_size(*int_sort_std, *int_sort_ft, "_first after");
		compare_capacity(*int_sort_std, *int_sort_ft, "_first after");
		EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
		EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
		EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
	}
	{
		std::cout << "----- INSERT (range) -----" << std::endl;
		std::vector<int>	cnt_std(8, 7);
		ft::Vector<int>		cnt_ft(8, 7);
		compare_content(cnt_std, cnt_ft, "_first before");
		compare_size(cnt_std, cnt_ft, "_first before");
		compare_capacity(cnt_std, cnt_ft, "_first before");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");
		EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
		EXPECT_EQ(cnt_std.size(), cnt_ft.size());
		EXPECT_EQ(cnt_std.capacity(), cnt_ft.capacity());

		std::cout << std::endl;
		std::cout << "Insert to first before ++begin() element "
			<< "from second range [++begin(), --end())" << std::endl;

		cnt_std.insert(++cnt_std.begin(),
						++int_unsort_std->begin(), --int_unsort_std->end());
		cnt_ft.insert(++cnt_ft.begin(),
						++int_unsort_ft->begin(), --int_unsort_ft->end());

		compare_content(cnt_std, cnt_ft, "_first after");
		compare_size(cnt_std, cnt_ft, "_first after");
		compare_capacity(cnt_std, cnt_ft, "_first after");
		EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
		EXPECT_EQ(cnt_std.size(), cnt_ft.size());
		EXPECT_EQ(cnt_std.capacity(), cnt_ft.capacity());
	}
}
