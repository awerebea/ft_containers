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
		int unsort_int_arr[] = { 8, 0, 6, 9, 7, 33, 44, 11, 22 };
		int_unsort_std = new std::vector<int>;
		for (int i = 0; i < 9; ++i) {
			int_unsort_std->push_back(unsort_int_arr[i]);
		}
		int_unsort_ft = new ft::Vector<int>;
		for (int i = 0; i < 9; ++i) {
			int_unsort_ft->push_back(unsort_int_arr[i]);
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

TEST_F(Test_Vector, Constructor_Default) {
	std::vector<int> ctnr_std;
	ft::Vector<int> ctnr_ft;
	std::cout << "----- CONSTRUCTOR (default) -----" << std::endl;
	compare_size(ctnr_std, ctnr_ft);

	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
}

TEST_F(Test_Vector, Constructor_Fill) {
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

TEST_F(Test_Vector, Constructor_Range) {
	std::vector<int>	ctnr_std_cpy(++(*int_sort_std).begin(),
									--(*int_sort_std).end());
	ft::Vector<int>	ctnr_ft_cpy(++(*int_sort_ft).begin(),
								--(*int_sort_ft).end());

	std::cout << "----- CONSTRUCTOR (range) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " original");
	compare_content(ctnr_std_cpy, ctnr_ft_cpy, " ranged");
	EXPECT_EQ(*ctnr_std_cpy.begin(), *ctnr_ft_cpy.begin());
	EXPECT_EQ(*(--ctnr_std_cpy.end()), *(--ctnr_ft_cpy.end()));
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(ctnr_std_cpy.size(), ctnr_ft_cpy.size());
	EXPECT_EQ(ctnr_std_cpy.capacity(), ctnr_ft_cpy.capacity());
}

TEST_F(Test_Vector, Constructor_Copy) {
	std::vector<int>	ctnr_std_cpy(*int_unsort_std);
	ft::Vector<int>		ctnr_ft_cpy(*int_unsort_ft);

	std::cout << "----- CONSTRUCTOR (copy) -----" << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, " original");
	compare_content(ctnr_std_cpy, ctnr_ft_cpy, " copy");
	EXPECT_EQ(*ctnr_std_cpy.begin(), *ctnr_ft_cpy.begin());
	EXPECT_EQ(*(--ctnr_std_cpy.end()), *(--ctnr_ft_cpy.end()));
	EXPECT_EQ(int_unsort_std->size(), ctnr_std_cpy.size());
	EXPECT_EQ(int_unsort_ft->size(), ctnr_ft_cpy.size());
}

TEST_F(Test_Vector, Destructor) {
	std::vector<int>*	ctnr_std = new std::vector<int>(5, 5);
	ft::Vector<int>*	ctnr_ft = new ft::Vector<int>(5, 5);

	std::cout << "----- DESTRUCTOR -----" << std::endl;
	delete(ctnr_std);
	delete(ctnr_ft);
}

TEST_F(Test_Vector, Operator_Assign) {
	std::vector<int>	ctnr_std_cpy;
	ft::Vector<int>		ctnr_ft_cpy;

	ctnr_std_cpy = *int_sort_std;
	ctnr_ft_cpy = *int_sort_ft;

	std::cout << "----- OPERATOR =  -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	compare_capacity(*int_sort_std, *int_sort_ft);
	std::cout << std::endl;
	compare_content(ctnr_std_cpy, ctnr_ft_cpy, " copy");
	compare_size(ctnr_std_cpy, ctnr_ft_cpy, " copy");
	compare_capacity(ctnr_std_cpy, ctnr_ft_cpy, " copy");

	EXPECT_EQ(*ctnr_std_cpy.begin(), *ctnr_ft_cpy.begin());
	EXPECT_EQ(*(--ctnr_std_cpy.end()), *(--ctnr_ft_cpy.end()));
	EXPECT_EQ(int_sort_std->size(), ctnr_std_cpy.size());
	EXPECT_EQ(int_sort_ft->size(), ctnr_ft_cpy.size());
	EXPECT_EQ(ctnr_std_cpy.capacity(), ctnr_ft_cpy.capacity());
}

TEST_F(Test_Vector, Iterators_Begin) {
	std::cout << "----- ITERATOR BEGIN -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_iterators(int_sort_std->begin(), int_sort_ft->begin(), "   begin");
	compare_iterators(++int_sort_std->begin(), ++int_sort_ft->begin(),
			" ++begin");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*(++int_sort_std->begin()), *(++int_sort_ft->begin()));
}

TEST_F(Test_Vector, Iterators_End) {
	std::cout << "----- ITERATOR END -----" << std::endl;
	std::vector<int>::iterator it_std = --int_sort_std->end();
	ft::Vector<int>::iterator it_ft = --int_sort_ft->end();
	compare_content(*int_sort_std, *int_sort_ft);
	compare_iterators(it_std, it_ft, "    --end");
	compare_iterators(--it_std, --it_ft, " --(--end)");
	EXPECT_EQ(*(--int_sort_std->end()), *(--int_sort_ft->end()));
	EXPECT_EQ(*(--it_std), *(--it_ft));
}

TEST_F(Test_Vector, Iterators_Rbegin) {
	std::cout << "----- ITERATOR RBEGIN -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_iterators(int_sort_std->rbegin(), int_sort_ft->rbegin(),
			"   rbegin");
	compare_iterators(++int_sort_std->rbegin(), ++int_sort_ft->rbegin(),
			" ++rbegin");
	EXPECT_EQ(*int_sort_std->rbegin(), *int_sort_ft->rbegin());
	EXPECT_EQ(*(++int_sort_std->rbegin()), *(++int_sort_ft->rbegin()));
}

TEST_F(Test_Vector, Iterators_Rend) {
	std::cout << "----- ITERATOR REND -----" << std::endl;
	std::vector<int>::reverse_iterator it_std = --int_sort_std->rend();
	ft::Vector<int>::reverse_iterator it_ft = --int_sort_ft->rend();
	compare_content(*int_sort_std, *int_sort_ft);
	compare_iterators(it_std, it_ft, "    --rend");
	compare_iterators(--it_std, --it_ft, " --(--rend)");
	EXPECT_EQ(*(--int_sort_std->rend()), *(--int_sort_ft->rend()));
	EXPECT_EQ(*(--it_std), *(--it_ft));
}

TEST_F(Test_Vector, Capacity_Size) {
	std::cout << "----- SIZE -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Clear containers" << std::endl;
	int_sort_std->clear();
	int_sort_ft->clear();

	compare_content(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_Vector, Capacity_Max_size) {
	std::cout << "----- MAX SIZE -----" << std::endl;
	std::cout << "std max_size: " << int_sort_std->max_size() << std::endl;
	std::cout << " ft max_size: " << int_sort_ft->max_size() << std::endl;
	EXPECT_EQ(int_sort_std->max_size(), int_sort_ft->max_size());
}

TEST_F(Test_Vector, Capacity_Resize_reduce) {
	std::cout << "----- RESIZE (reduce) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	compare_capacity(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());

	std::cout << std::endl;
	std::cout << "Downsize to 2" << std::endl;
	int_sort_std->resize(2);
	int_sort_ft->resize(2);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	compare_capacity(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
}

TEST_F(Test_Vector, Capacity_Resize_incrase_default) {
	std::cout << "----- RESIZE (incrase default) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	compare_capacity(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());

	std::cout << std::endl;
	std::cout << "Upsize to 11 with default type value for new elements"
		<< std::endl;
	int_sort_std->resize(11);
	int_sort_ft->resize(11);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	compare_capacity(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
}

TEST_F(Test_Vector, Capacity_Resize_incrase_fill) {
	std::cout << "----- RESIZE (incrase fill) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	compare_capacity(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());

	std::cout << std::endl;
	std::cout << "Upsize to 10 with '7' value for new elements" << std::endl;
	int_sort_std->resize(10, 7);
	int_sort_ft->resize(10, 7);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	compare_capacity(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
}

TEST_F(Test_Vector, Capacity_Capacity) {
	std::cout << "----- CAPACITY -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_capacity(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());

	std::cout << std::endl;
	std::cout << "Create empty containers" << std::endl;
	std::vector<int>	ctnr_std;
	ft::Vector<int>		ctnr_ft;

	compare_content(ctnr_std, ctnr_ft);
	compare_capacity(ctnr_std, ctnr_ft);

	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
}

TEST_F(Test_Vector, Capacity_Empty) {
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

TEST_F(Test_Vector, Capacity_Reserve) {
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

TEST_F(Test_Vector, Element_access_Operator_square_braskets) {
	std::cout << "----- OPERATOR [] -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_elements((*int_sort_std)[1], (*int_sort_ft)[1], "[1]");
	compare_elements((*int_sort_std)[3], (*int_sort_ft)[3], "[3]");
	EXPECT_EQ((*int_sort_std)[1], (*int_sort_ft)[1]);
	EXPECT_EQ((*int_sort_std)[3], (*int_sort_ft)[3]);
}

TEST_F(Test_Vector, Element_access_At) {
	std::cout << "----- OPERATOR [] -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_elements(int_sort_std->at(4), int_sort_ft->at(4), "[4]");
	std::cout << "Try to access out-of-range element, at(17)" << std::endl;
	try { std::cout << "std: "; int_sort_std->at(17); }
	catch (const std::out_of_range& e) { std::cout << e.what() << std::endl; }
	try { std::cout << " ft: "; int_sort_ft->at(17); }
	catch (const std::out_of_range& e) { std::cout << e.what() << std::endl; }
	EXPECT_EQ(int_sort_std->at(4), int_sort_ft->at(4));
}

TEST_F(Test_Vector, Element_access_Front) {
	std::cout << "----- ELEMENT ACCESS FRONT -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_elements(int_sort_std->front(), int_sort_ft->front());
	EXPECT_EQ(int_sort_std->front(), int_sort_ft->front());
}

TEST_F(Test_Vector, Element_access_Back) {
	std::cout << "----- ELEMENT ACCESS BACK -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_elements(int_sort_std->back(), int_sort_ft->back());
	EXPECT_EQ(int_sort_std->back(), int_sort_ft->back());
}

TEST_F(Test_Vector, Modifiers_assign_Range) {
	std::cout << "----- ASSIGN (range) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " original");

	std::vector<int>	ctnr_std_second;
	ft::Vector<int>		ctnr_ft_second;

	std::cout << std::endl;
	compare_size(ctnr_std_second, ctnr_ft_second, "_second before");
	compare_capacity(ctnr_std_second, ctnr_ft_second, "_second before");

	std::cout << std::endl;
	std::cout << "Assign by range [++begin(), --end()) from original"
		<< std::endl;

	ctnr_std_second.assign(++int_sort_std->begin(), --int_sort_std->end());
	ctnr_ft_second.assign(++int_sort_ft->begin(), --int_sort_ft->end());

	compare_content(ctnr_std_second, ctnr_ft_second, " assigned");
	compare_size(ctnr_std_second, ctnr_ft_second, "_second after");
	compare_capacity(ctnr_std_second, ctnr_ft_second, "_second after");

	EXPECT_EQ(*ctnr_std_second.begin(), *ctnr_ft_second.begin());
	EXPECT_EQ(ctnr_std_second.size(), ctnr_ft_second.size());
	EXPECT_EQ(ctnr_std_second.capacity(), ctnr_ft_second.capacity());
}

TEST_F(Test_Vector, Modifiers_Assign_fill) {
	std::cout << "----- ASSIGN (fill) -----" << std::endl;
	std::vector<int>	ctnr_std;
	ft::Vector<int>		ctnr_ft;
	compare_size(ctnr_std, ctnr_ft, " before");
	compare_capacity(ctnr_std, ctnr_ft, " before");

	std::cout << std::endl;
	std::cout << "Assign fill" << std::endl;

	ctnr_std.assign(5, 7);
	ctnr_ft.assign(5, 7);

	compare_content(ctnr_std, ctnr_ft, " assigned");
	compare_size(ctnr_std, ctnr_ft, " after");
	compare_capacity(ctnr_std, ctnr_ft, " after");

	EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
	EXPECT_EQ(ctnr_std.capacity(), ctnr_ft.capacity());
}

TEST_F(Test_Vector, Modifiers_Push_back) {
	std::cout << "----- PUSH_BACK -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	compare_capacity(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());

	std::cout << std::endl;
	std::cout << "push_back(7)" << std::endl;

	int_sort_std->push_back(7);
	int_sort_ft->push_back(7);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	compare_capacity(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*(--int_sort_std->end()), *(--int_sort_ft->end()));
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
}

TEST_F(Test_Vector, Modifiers_Pop_back) {
	std::cout << "----- POP_BACK -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	compare_capacity(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());

	int_sort_std->pop_back();
	int_sort_ft->pop_back();

	std::cout << std::endl;
	std::cout << "pop_back" << std::endl;

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	compare_capacity(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*(--int_sort_std->end()), *(--int_sort_ft->end()));
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
}

TEST_F(Test_Vector, Modifiers_Insert_single_element) {
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
		std::vector<int>	ctnr_std;
		ft::Vector<int>		ctnr_ft;
		compare_size(ctnr_std, ctnr_ft, " before");
		compare_capacity(ctnr_std, ctnr_ft, " before");
		EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
		EXPECT_EQ(ctnr_std.capacity(), ctnr_ft.capacity());

		std::cout << std::endl;
		std::cout << "Insert '8' before end() element" << std::endl;

		ctnr_std.insert(ctnr_std.begin(), 8);
		ctnr_ft.insert(ctnr_ft.begin(), 8);

		compare_content(ctnr_std, ctnr_ft, " after");
		compare_size(ctnr_std, ctnr_ft, " after");
		compare_capacity(ctnr_std, ctnr_ft, " after");
		EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
		EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
		EXPECT_EQ(ctnr_std.capacity(), ctnr_ft.capacity());
	}
}

TEST_F(Test_Vector, Modifiers_Insert_fill) {
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

TEST_F(Test_Vector, Modifiers_Insert_range) {
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
		std::vector<int>	ctnr_std(8, 7);
		ft::Vector<int>		ctnr_ft(8, 7);
		compare_content(ctnr_std, ctnr_ft, "_first before");
		compare_size(ctnr_std, ctnr_ft, "_first before");
		compare_capacity(ctnr_std, ctnr_ft, "_first before");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");
		EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
		EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
		EXPECT_EQ(ctnr_std.capacity(), ctnr_ft.capacity());

		std::cout << std::endl;
		std::cout << "Insert to first before ++begin() element "
			<< "from second range [++begin(), --end())" << std::endl;

		ctnr_std.insert(++ctnr_std.begin(),
						++int_unsort_std->begin(), --int_unsort_std->end());
		ctnr_ft.insert(++ctnr_ft.begin(),
						++int_unsort_ft->begin(), --int_unsort_ft->end());

		compare_content(ctnr_std, ctnr_ft, "_first after");
		compare_size(ctnr_std, ctnr_ft, "_first after");
		compare_capacity(ctnr_std, ctnr_ft, "_first after");
		EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
		EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
		EXPECT_EQ(ctnr_std.capacity(), ctnr_ft.capacity());
	}
}

TEST_F(Test_Vector, Modifiers_Erase_position) {
	std::cout << "----- ERASE (position) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::vector<int>::iterator it_std;
	ft::Vector<int>::iterator it_ft;
	it_std = int_sort_std->erase(int_sort_std->begin());
	it_ft = int_sort_ft->erase(int_sort_ft->begin());

	std::cout << std::endl;
	std::cout << "Erase begin() element" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	std::cout << std::endl;
	std::cout << "Compare iterators" << std::endl;
	compare_iterators(it_std, it_ft);
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(*it_std, *it_ft);
}

TEST_F(Test_Vector, Modifiers_Erase_range) {
	std::cout << "----- ERASE (range) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::vector<int>::iterator it_std;
	ft::Vector<int>::iterator it_ft;
	it_std = int_sort_std->erase(++int_sort_std->begin(),
			--int_sort_std->end());
	it_ft = int_sort_ft->erase(++int_sort_ft->begin(), --int_sort_ft->end());

	std::cout << std::endl;
	std::cout << "Erase range [++begin(), --end())" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	std::cout << std::endl;
	std::cout << "Compare iterators" << std::endl;
	compare_iterators(it_std, it_ft);
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(*it_std, *it_ft);
}

TEST_F(Test_Vector, Modifiers_Swap) {
	std::cout << "----- SWAP -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, "_first before");
	compare_size(*int_sort_std, *int_sort_ft, "_first before");
	compare_capacity(*int_sort_std, *int_sort_ft, "_first before");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second before");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second before");
	compare_capacity(*int_unsort_std, *int_unsort_ft, "_second before");

	std::vector<int>::iterator it_std_first = ++int_sort_std->begin();
	std::vector<int>::iterator it_std_second = ++int_unsort_std->begin();
	ft::Vector<int>::iterator it_ft_first = ++int_sort_ft->begin();
	ft::Vector<int>::iterator it_ft_second = ++int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  before");
	compare_iterators(it_std_second, it_ft_second, "_second before");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
	EXPECT_EQ(int_unsort_std->capacity(), int_unsort_ft->capacity());

	std::cout << std::endl;
	std::cout << "Swap first and second objects" << std::endl;

	int_sort_std->swap(*int_unsort_std);
	int_sort_ft->swap(*int_unsort_ft);

	compare_content(*int_sort_std, *int_sort_ft, "_first after");
	compare_size(*int_sort_std, *int_sort_ft, "_first after");
	compare_capacity(*int_sort_std, *int_sort_ft, "_first after");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second after");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second after");
	compare_capacity(*int_unsort_std, *int_unsort_ft, "_second after");
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first after");
	compare_iterators(it_std_second, it_ft_second, "_second after");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
	EXPECT_EQ(int_unsort_std->capacity(), int_unsort_ft->capacity());
}

TEST_F(Test_Vector, Modifiers_Clear) {
	std::cout << "----- CLEAR -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	compare_capacity(*int_sort_std, *int_sort_ft, " before");

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());

	std::cout << std::endl;
	std::cout << "Clear containers" << std::endl;
	int_sort_std->clear();
	int_sort_ft->clear();

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	compare_capacity(*int_sort_std, *int_sort_ft, " after");

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
}

TEST_F(Test_Vector, Relational_operators_Equal) {
	{
		std::cout << "----- RELATIONAL OPERATORS == -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");

		std::cout << std::endl;
		std::cout << "std_first == std_second: " << std::boolalpha
			<< (*int_sort_std == *int_unsort_std) << std::endl;
		std::cout << " ft_first ==  ft_second: " << std::boolalpha
			<< (*int_sort_ft == *int_unsort_ft) << std::endl;

		EXPECT_EQ((*int_sort_std == *int_unsort_std), 0);
		EXPECT_EQ((*int_sort_ft == *int_unsort_ft), 0);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS == -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;

		std::vector<int>	ctnr_std_cpy(*int_sort_std);
		ft::Vector<int>	ctnr_ft_cpy(*int_sort_ft);

		compare_content(ctnr_std_cpy, ctnr_ft_cpy, "_second");

		std::cout << std::endl;
		std::cout << "std_first == std_second: " << std::boolalpha
			<< (*int_sort_std == ctnr_std_cpy) << std::endl;
		std::cout << " ft_first ==  ft_second: " << std::boolalpha
			<< (*int_sort_ft == ctnr_ft_cpy) << std::endl;

		EXPECT_EQ((*int_sort_std == ctnr_std_cpy), 1);
		EXPECT_EQ((*int_sort_ft == ctnr_ft_cpy), 1);
	}
}

TEST_F(Test_Vector, Relational_operators_Not_equal) {
	{
		std::cout << "----- RELATIONAL OPERATORS != -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");

		std::cout << std::endl;
		std::cout << "std_first != std_second: " << std::boolalpha
			<< (*int_sort_std != *int_unsort_std) << std::endl;
		std::cout << " ft_first !=  ft_second: " << std::boolalpha
			<< (*int_sort_ft != *int_unsort_ft) << std::endl;

		EXPECT_EQ((*int_sort_std != *int_unsort_std), 1);
		EXPECT_EQ((*int_sort_ft != *int_unsort_ft), 1);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS != -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;

		std::vector<int>	ctnr_std_cpy(*int_sort_std);
		ft::Vector<int>	ctnr_ft_cpy(*int_sort_ft);

		compare_content(ctnr_std_cpy, ctnr_ft_cpy, "_second");

		std::cout << std::endl;
		std::cout << "std_first != std_second: " << std::boolalpha
			<< (*int_sort_std != ctnr_std_cpy) << std::endl;
		std::cout << " ft_first !=  ft_second: " << std::boolalpha
			<< (*int_sort_ft != ctnr_ft_cpy) << std::endl;

		EXPECT_EQ((*int_sort_std != ctnr_std_cpy), 0);
		EXPECT_EQ((*int_sort_ft != ctnr_ft_cpy), 0);
	}
}

TEST_F(Test_Vector, Relational_operators_Less) {
	{
		std::cout << "----- RELATIONAL OPERATORS < -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");

		std::cout << std::endl;
		std::cout << "std_first < std_second: " << std::boolalpha
			<< (*int_sort_std < *int_unsort_std) << std::endl;
		std::cout << " ft_first <  ft_second: " << std::boolalpha
			<< (*int_sort_ft < *int_unsort_ft) << std::endl;

		EXPECT_EQ((*int_sort_std < *int_unsort_std), 1);
		EXPECT_EQ((*int_sort_ft < *int_unsort_ft), 1);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS < -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;

		std::vector<int>	ctnr_std_cpy(*int_sort_std);
		ft::Vector<int>	ctnr_ft_cpy(*int_sort_ft);

		compare_content(ctnr_std_cpy, ctnr_ft_cpy, "_second");

		std::cout << std::endl;
		std::cout << "std_first < std_second: " << std::boolalpha
			<< (*int_sort_std < ctnr_std_cpy) << std::endl;
		std::cout << " ft_first <  ft_second: " << std::boolalpha
			<< (*int_sort_ft < ctnr_ft_cpy) << std::endl;

		EXPECT_EQ((*int_sort_std < ctnr_std_cpy), 0);
		EXPECT_EQ((*int_sort_ft < ctnr_ft_cpy), 0);
	}
}

TEST_F(Test_Vector, Relational_operators_Less_or_equal) {
	{
		std::cout << "----- RELATIONAL OPERATORS <= -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");

		std::cout << std::endl;
		std::cout << "std_first <= std_second: " << std::boolalpha
			<< (*int_sort_std <= *int_unsort_std) << std::endl;
		std::cout << " ft_first <=  ft_second: " << std::boolalpha
			<< (*int_sort_ft <= *int_unsort_ft) << std::endl;

		EXPECT_EQ((*int_sort_std <= *int_unsort_std), 1);
		EXPECT_EQ((*int_sort_ft <= *int_unsort_ft), 1);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS <= -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;

		std::vector<int>	ctnr_std_cpy(*int_sort_std);
		ft::Vector<int>	ctnr_ft_cpy(*int_sort_ft);

		compare_content(ctnr_std_cpy, ctnr_ft_cpy, "_second");

		std::cout << std::endl;
		std::cout << "std_first <= std_second: " << std::boolalpha
			<< (*int_sort_std <= ctnr_std_cpy) << std::endl;
		std::cout << " ft_first <=  ft_second: " << std::boolalpha
			<< (*int_sort_ft <= ctnr_ft_cpy) << std::endl;

		EXPECT_EQ((*int_sort_std <= ctnr_std_cpy), 1);
		EXPECT_EQ((*int_sort_ft <= ctnr_ft_cpy), 1);
	}
}

TEST_F(Test_Vector, Relational_operators_More) {
	{
		std::cout << "----- RELATIONAL OPERATORS > -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");

		std::cout << std::endl;
		std::cout << "std_first > std_second: " << std::boolalpha
			<< (*int_sort_std > *int_unsort_std) << std::endl;
		std::cout << " ft_first >  ft_second: " << std::boolalpha
			<< (*int_sort_ft > *int_unsort_ft) << std::endl;

		EXPECT_EQ((*int_sort_std > *int_unsort_std), 0);
		EXPECT_EQ((*int_sort_ft > *int_unsort_ft), 0);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS > -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;

		std::vector<int>	ctnr_std_cpy(*int_sort_std);
		ft::Vector<int>	ctnr_ft_cpy(*int_sort_ft);

		compare_content(ctnr_std_cpy, ctnr_ft_cpy, "_second");

		std::cout << std::endl;
		std::cout << "std_first > std_second: " << std::boolalpha
			<< (*int_sort_std > ctnr_std_cpy) << std::endl;
		std::cout << " ft_first >  ft_second: " << std::boolalpha
			<< (*int_sort_ft > ctnr_ft_cpy) << std::endl;

		EXPECT_EQ((*int_sort_std > ctnr_std_cpy), 0);
		EXPECT_EQ((*int_sort_ft > ctnr_ft_cpy), 0);
	}
}

TEST_F(Test_Vector, Relational_operators_More_or_equal) {
	{
		std::cout << "----- RELATIONAL OPERATORS >= -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");

		std::cout << std::endl;
		std::cout << "std_first >= std_second: " << std::boolalpha
			<< (*int_sort_std > *int_unsort_std) << std::endl;
		std::cout << " ft_first >=  ft_second: " << std::boolalpha
			<< (*int_sort_ft > *int_unsort_ft) << std::endl;

		EXPECT_EQ((*int_sort_std >= *int_unsort_std), 0);
		EXPECT_EQ((*int_sort_ft >= *int_unsort_ft), 0);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS >= -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;

		std::vector<int>	ctnr_std_cpy(*int_sort_std);
		ft::Vector<int>	ctnr_ft_cpy(*int_sort_ft);

		compare_content(ctnr_std_cpy, ctnr_ft_cpy, "_second");

		std::cout << std::endl;
		std::cout << "std_first >= std_second: " << std::boolalpha
			<< (*int_sort_std >= ctnr_std_cpy) << std::endl;
		std::cout << " ft_first >=  ft_second: " << std::boolalpha
			<< (*int_sort_ft >= ctnr_ft_cpy) << std::endl;

		EXPECT_EQ((*int_sort_std >= ctnr_std_cpy), 1);
		EXPECT_EQ((*int_sort_ft >= ctnr_ft_cpy), 1);
	}
}

TEST_F(Test_Vector, Non_member_overload_Swap) {
	std::cout << "----- SWAP -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, "_first before");
	compare_size(*int_sort_std, *int_sort_ft, "_first before");
	compare_capacity(*int_sort_std, *int_sort_ft, "_first before");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second before");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second before");
	compare_capacity(*int_unsort_std, *int_unsort_ft, "_second before");

	std::vector<int>::iterator it_std_first = ++int_sort_std->begin();
	std::vector<int>::iterator it_std_second = ++int_unsort_std->begin();
	ft::Vector<int>::iterator it_ft_first = ++int_sort_ft->begin();
	ft::Vector<int>::iterator it_ft_second = ++int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  before");
	compare_iterators(it_std_second, it_ft_second, "_second before");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
	EXPECT_EQ(int_unsort_std->capacity(), int_unsort_ft->capacity());

	std::cout << std::endl;
	std::cout << "Swap first and second objects" << std::endl;

	swap(*int_sort_std, *int_unsort_std);
	swap(*int_sort_ft, *int_unsort_ft);

	compare_content(*int_sort_std, *int_sort_ft, "_first after");
	compare_size(*int_sort_std, *int_sort_ft, "_first after");
	compare_capacity(*int_sort_std, *int_sort_ft, "_first after");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second after");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second after");
	compare_capacity(*int_unsort_std, *int_unsort_ft, "_second after");
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first after");
	compare_iterators(it_std_second, it_ft_second, "_second after");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
	EXPECT_EQ(int_sort_std->capacity(), int_sort_ft->capacity());
	EXPECT_EQ(int_unsort_std->capacity(), int_unsort_ft->capacity());
}
