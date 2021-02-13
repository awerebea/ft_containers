/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:07:59 by awerebea          #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <list>
#include "all_test_utils.hpp"
#include "List.hpp"

class Test_List : public ::testing::Test {
protected:
	void SetUp() {
		int_sort_std = new std::list<int>;
		for (int i = 0; i < 5; ++i) {
			int_sort_std->push_back(i + 1);
		}
		int_sort_ft = new ft::List<int>;
		for (int i = 0; i < 5; ++i) {
			int_sort_ft->push_back(i + 1);
		}
		int unsort_int_arr[] = { 8, 0, 6, 9, 7 };
		int_unsort_std = new std::list<int>;
		for (int i = 0; i < 5; ++i) {
			int_unsort_std->push_back(unsort_int_arr[i]);
		}
		int_unsort_ft = new ft::List<int>;
		for (int i = 0; i < 5; ++i) {
			int_unsort_ft->push_back(unsort_int_arr[i]);
		}
	}
	void TearDown() {
		delete int_sort_std;
		delete int_sort_ft;

		delete int_unsort_std;
		delete int_unsort_ft;
	}
	std::list<int> * int_sort_std;
	ft::List<int> * int_sort_ft;

	std::list<int> * int_unsort_std;
	ft::List<int> * int_unsort_ft;
};

TEST_F(Test_List, Constructor_Default) {
	std::list<int> ctnr_std;
	ft::List<int> ctnr_ft;
	std::cout << "----- CONSTRUCTOR (default) -----" << std::endl;
	compare_size(ctnr_std, ctnr_ft);

	EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
}

TEST_F(Test_List, Constructor_Fill) {
	{
		std::list<int> ctnr_std(2);
		ft::List<int> ctnr_ft(2);

		std::cout << "----- CONSTRUCTOR (fill) -----" << std::endl;
		compare_content(ctnr_std, ctnr_ft);

		EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
		EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
	}
	{
		std::list<std::string> ctnr_std(2, "test");
		ft::List<std::string> ctnr_ft(2, "test");

		std::cout << "----- CONSTRUCTOR (fill) -----" << std::endl;
		compare_content(ctnr_std, ctnr_ft);

		EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
		EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
	}
}

TEST_F(Test_List, Constructor_Range) {
	std::list<int>	ctnr_std_cpy(++(*int_sort_std).begin(),
			--(*int_sort_std).end());
	ft::List<int>	ctnr_ft_cpy(++(*int_sort_ft).begin(),
			--(*int_sort_ft).end());

	std::cout << "----- CONSTRUCTOR (range) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " original");
	compare_content(ctnr_std_cpy, ctnr_ft_cpy, " ranged");
	EXPECT_EQ(*ctnr_std_cpy.begin(), *ctnr_ft_cpy.begin());
	EXPECT_EQ(*(--ctnr_std_cpy.end()), *(--ctnr_ft_cpy.end()));
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(ctnr_std_cpy.size(), ctnr_ft_cpy.size());
}

TEST_F(Test_List, Constructor_Copy) {
	std::list<int>	ctnr_std_cpy(*int_unsort_std);
	ft::List<int>	ctnr_ft_cpy(*int_unsort_ft);

	std::cout << "----- CONSTRUCTOR (copy) -----" << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, " original");
	compare_content(ctnr_std_cpy, ctnr_ft_cpy, " copy");
	EXPECT_EQ(*ctnr_std_cpy.begin(), *ctnr_ft_cpy.begin());
	EXPECT_EQ(*(--ctnr_std_cpy.end()), *(--ctnr_ft_cpy.end()));
	EXPECT_EQ(int_unsort_std->size(), ctnr_std_cpy.size());
	EXPECT_EQ(int_unsort_ft->size(), ctnr_ft_cpy.size());
}

TEST_F(Test_List, Destructor) {
	std::list<int>	* ctnr_std = new std::list<int>(5, 5);
	ft::List<int>	* ctnr_ft = new ft::List<int>(5, 5);

	std::cout << "----- DESTRUCTOR -----" << std::endl;
	delete(ctnr_std);
	delete(ctnr_ft);
}

TEST_F(Test_List, Operator_Assign) {
	std::list<int>	ctnr_std_cpy;
	ft::List<int>	ctnr_ft_cpy;

	ctnr_std_cpy = *int_sort_std;
	ctnr_ft_cpy = *int_sort_ft;

	std::cout << "----- OPERATOR =  -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " original");
	compare_content(ctnr_std_cpy, ctnr_ft_cpy, " copy");
	EXPECT_EQ(*ctnr_std_cpy.begin(), *ctnr_ft_cpy.begin());
	EXPECT_EQ(*(--ctnr_std_cpy.end()), *(--ctnr_ft_cpy.end()));
	EXPECT_EQ(int_sort_std->size(), ctnr_std_cpy.size());
	EXPECT_EQ(int_sort_ft->size(), ctnr_ft_cpy.size());
}

TEST_F(Test_List, Iterators_Begin) {
	std::cout << "----- ITERATOR BEGIN -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_iterators(int_sort_std->begin(), int_sort_ft->begin(), "   begin");
	compare_iterators(++int_sort_std->begin(), ++int_sort_ft->begin(),
		" ++begin");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*(++int_sort_std->begin()), *(++int_sort_ft->begin()));
}

TEST_F(Test_List, Iterators_End) {
	std::cout << "----- ITERATOR END -----" << std::endl;
	std::list<int>::iterator it_std = --int_sort_std->end();
	ft::List<int>::iterator it_ft = --int_sort_ft->end();
	compare_content(*int_sort_std, *int_sort_ft);
	compare_iterators(it_std, it_ft, "    --end");
	compare_iterators(--it_std, --it_ft, " --(--end)");
	EXPECT_EQ(*(--int_sort_std->end()), *(--int_sort_ft->end()));
	EXPECT_EQ(*(--it_std), *(--it_ft));
}

TEST_F(Test_List, Iterators_Rbegin) {
	std::cout << "----- ITERATOR RBEGIN -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_iterators(int_sort_std->rbegin(), int_sort_ft->rbegin(),
		"   rbegin");
	compare_iterators(++int_sort_std->rbegin(), ++int_sort_ft->rbegin(),
		" ++rbegin");
	EXPECT_EQ(*int_sort_std->rbegin(), *int_sort_ft->rbegin());
	EXPECT_EQ(*(++int_sort_std->rbegin()), *(++int_sort_ft->rbegin()));
}

TEST_F(Test_List, Iterators_Rend) {
	std::cout << "----- ITERATOR REND -----" << std::endl;
	std::list<int>::reverse_iterator it_std = --int_sort_std->rend();
	ft::List<int>::reverse_iterator it_ft = --int_sort_ft->rend();
	compare_content(*int_sort_std, *int_sort_ft);
	compare_iterators(it_std, it_ft, "    --rend");
	compare_iterators(--it_std, --it_ft, " --(--rend)");
	EXPECT_EQ(*(--int_sort_std->rend()), *(--int_sort_ft->rend()));
	EXPECT_EQ(*(--it_std), *(--it_ft));
}

TEST_F(Test_List, Capacity_Empty) {
	std::cout << "----- EMPTY -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
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

	compare_content(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);
	std::cout << "std empty: " << std::boolalpha << int_sort_std->empty()
		<< std::endl;
	std::cout << " ft empty: " << std::boolalpha << int_sort_ft->empty()
		<< std::endl;

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->empty(), int_sort_ft->empty());
}

TEST_F(Test_List, Capacity_Size) {
	std::cout << "----- SIZE -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Capacity_Max_size) {
	std::cout << "----- MAX SIZE -----" << std::endl;
	std::cout << "std max_size: " << int_sort_std->max_size() << std::endl;
	std::cout << " ft max_size: " << int_sort_ft->max_size() << std::endl;
	EXPECT_EQ(int_sort_std->max_size(), int_sort_ft->max_size());
}

TEST_F(Test_List, Element_access_Front) {
	std::cout << "----- ELEMENT ACCESS FRONT -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_elements(int_sort_std->front(), int_sort_ft->front());
	EXPECT_EQ(int_sort_std->front(), int_sort_ft->front());
}

TEST_F(Test_List, Element_access_Back) {
	std::cout << "----- ELEMENT ACCESS BACK -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_elements(int_sort_std->back(), int_sort_ft->back());
	EXPECT_EQ(int_sort_std->back(), int_sort_ft->back());
}

TEST_F(Test_List, Modifiers_Assign_range) {
	std::cout << "----- ASSIGN (range) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " original");

	std::list<int>	ctnr_std_second;
	ft::List<int>	ctnr_ft_second;

	std::cout << std::endl;
	compare_size(ctnr_std_second, ctnr_ft_second, "_second before");
	std::cout << std::endl;
	std::cout << "Assign by range [++begin(), --end()) from original"
		<< std::endl;

	ctnr_std_second.assign(++int_sort_std->begin(), --int_sort_std->end());
	ctnr_ft_second.assign(++int_sort_ft->begin(), --int_sort_ft->end());

	compare_content(ctnr_std_second, ctnr_ft_second, " assigned");
	compare_size(ctnr_std_second, ctnr_ft_second, "_second after");

	EXPECT_EQ(*ctnr_std_second.begin(), *ctnr_ft_second.begin());
	EXPECT_EQ(ctnr_std_second.size(), ctnr_ft_second.size());
}

TEST_F(Test_List, Modifiers_Assign_fill) {
	std::cout << "----- ASSIGN (fill) -----" << std::endl;
	std::list<int>	ctnr_std;
	ft::List<int>	ctnr_ft;
	compare_size(ctnr_std, ctnr_ft, " before");

	std::cout << std::endl;
	std::cout << "Assign fill" << std::endl;

	ctnr_std.assign(5, 7);
	ctnr_ft.assign(5, 7);

	compare_content(ctnr_std, ctnr_ft, " assigned");
	compare_size(ctnr_std, ctnr_ft, " after");

	EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
}

TEST_F(Test_List, Modifiers_Push_front) {
	std::cout << "----- PUSH_FRONT -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "push_front(7)" << std::endl;

	int_sort_std->push_front(7);
	int_sort_ft->push_front(7);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*(--int_sort_std->end()), *(--int_sort_ft->end()));
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_Pop_front) {
	std::cout << "----- POP_FRONT -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	int_sort_std->pop_front();
	int_sort_ft->pop_front();

	std::cout << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_Push_back) {
	std::cout << "----- PUSH_BACK -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "push_back(7)" << std::endl;

	int_sort_std->push_back(7);
	int_sort_ft->push_back(7);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*(--int_sort_std->end()), *(--int_sort_ft->end()));
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_Pop_back) {
	std::cout << "----- POP_BACK -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	int_sort_std->pop_back();
	int_sort_ft->pop_back();

	std::cout << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*(--int_sort_std->end()), *(--int_sort_ft->end()));
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_Insert_single_element) {
	std::cout << "----- INSERT (single element) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Insert '8' before ++begin() element" << std::endl;

	int_sort_std->insert(++int_sort_std->begin(), 8);
	int_sort_ft->insert(++int_sort_ft->begin(), 8);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_Insert_fill) {
	std::cout << "----- INSERT (fill) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Insert '8' 5 times before ++begin() element" << std::endl;

	int_sort_std->insert(++int_sort_std->begin(), 5, 8);
	int_sort_ft->insert(++int_sort_ft->begin(), 5, 8);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_Insert_range) {
	std::cout << "----- INSERT (range) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, "_first before");
	compare_size(*int_sort_std, *int_sort_ft, "_first before");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second before");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Insert to first before ++begin() element "
		<< "from second range [++begin(), --end())" << std::endl;

	int_sort_std->insert(++int_sort_std->begin(),
			++int_unsort_std->begin(), --int_unsort_std->end());
	int_sort_ft->insert(++int_sort_ft->begin(),
			++int_unsort_ft->begin(), --int_unsort_ft->end());

	compare_content(*int_sort_std, *int_sort_ft, "_first after");
	compare_size(*int_sort_std, *int_sort_ft, "_first after");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second after");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_Erase_position) {
	std::cout << "----- ERASE (position) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::list<int>::iterator it_std;
	ft::List<int>::iterator it_ft;
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

TEST_F(Test_List, Modifiers_Erase_range) {
	std::cout << "----- ERASE (position) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::list<int>::iterator it_std;
	ft::List<int>::iterator it_ft;
	it_std = int_sort_std->erase(++int_sort_std->begin(),
			--int_sort_std->end());
	it_ft = int_sort_ft->erase(++int_sort_ft->begin(),
			--int_sort_ft->end());

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

TEST_F(Test_List, Modifiers_Swap) {
	std::cout << "----- SWAP -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, "_first before");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second before");

	std::list<int>::iterator it_std_first = ++int_sort_std->begin();
	std::list<int>::iterator it_std_second = ++int_unsort_std->begin();
	ft::List<int>::iterator it_ft_first = ++int_sort_ft->begin();
	ft::List<int>::iterator it_ft_second = ++int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  before");
	compare_iterators(it_std_second, it_ft_second, "_second before");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());

	std::cout << std::endl;
	std::cout << "Swap first and second objects" << std::endl;

	int_sort_std->swap(*int_unsort_std);
	int_sort_ft->swap(*int_unsort_ft);

	compare_content(*int_sort_std, *int_sort_ft, "_first  after");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second after");
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first after");
	compare_iterators(it_std_second, it_ft_second, "_second after");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
}

TEST_F(Test_List, Capacity_Resize_reduce) {
	std::cout << "----- RESIZE (reduce) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Downsize to 2" << std::endl;
	int_sort_std->resize(2);
	int_sort_ft->resize(2);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Capacity_Resize_incrase_default) {
	std::cout << "----- RESIZE (incrase default) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Upsize to 11 with default type value for new elements"
		<< std::endl;
	int_sort_std->resize(11);
	int_sort_ft->resize(11);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Capacity_Resize_incrase_fill) {
	std::cout << "----- RESIZE (incrase fill) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Upsize to 10 with '7' value for new elements" << std::endl;
	int_sort_std->resize(10, 7);
	int_sort_ft->resize(10, 7);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_Clear) {
	std::cout << "----- CLEAR -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	int_sort_std->clear();
	int_sort_ft->clear();

	std::cout << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Operations_Splice_entire_list) {
	std::cout << "----- SPLICE (entire list) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, "_first before");
	compare_size(*int_sort_std, *int_sort_ft, "_first before");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second before");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second before");

	std::list<int>::iterator it_std_first = ++int_sort_std->begin();
	std::list<int>::iterator it_std_second = ++int_unsort_std->begin();
	ft::List<int>::iterator it_ft_first = ++int_sort_ft->begin();
	ft::List<int>::iterator it_ft_second = ++int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  before");
	compare_iterators(it_std_second, it_ft_second, "_second before");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());

	std::cout << std::endl;
	std::cout << "Splice second object into first before ++begin()"
		<< std::endl;

	int_sort_std->splice(++int_sort_std->begin(),
			*int_unsort_std);
	int_sort_ft->splice(++int_sort_ft->begin(), *int_unsort_ft);

	compare_content(*int_sort_std, *int_sort_ft, "_first after");
	compare_size(*int_sort_std, *int_sort_ft, "_first after");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second after");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second after");
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  after");
	compare_iterators(it_std_second, it_ft_second, "_second after");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
}

TEST_F(Test_List, Operations_Splice_single_element) {
	std::cout << "----- SPLICE (single element) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, "_first before");
	compare_size(*int_sort_std, *int_sort_ft, "_first before");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second before");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second before");

	std::list<int>::iterator it_std_first = ++int_sort_std->begin();
	std::list<int>::iterator it_std_second = ++int_unsort_std->begin();
	ft::List<int>::iterator it_ft_first = ++int_sort_ft->begin();
	ft::List<int>::iterator it_ft_second = ++int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  before");
	compare_iterators(it_std_second, it_ft_second, "_second before");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());

	std::cout << std::endl;
	std::cout << "Splice single element ++begin() from second object "
		<< "into first before ++begin()" << std::endl;

	int_sort_std->splice(++int_sort_std->begin(),
			*int_unsort_std, ++int_unsort_std->begin());
	int_sort_ft->splice(++int_sort_ft->begin(),
				*int_unsort_ft, ++int_unsort_ft->begin());

	compare_content(*int_sort_std, *int_sort_ft, "_first after");
	compare_size(*int_sort_std, *int_sort_ft, "_first after");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second after");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second after");
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  after");
	compare_iterators(it_std_second, it_ft_second, "_second after");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
}

TEST_F(Test_List, Operations_Splice_range) {
	std::cout << "----- SPLICE (range) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, "_first before");
	compare_size(*int_sort_std, *int_sort_ft, "_first before");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second before");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second before");

	std::list<int>::iterator it_std_first = ++int_sort_std->begin();
	std::list<int>::iterator it_std_second = ++int_unsort_std->begin();
	ft::List<int>::iterator it_ft_first = ++int_sort_ft->begin();
	ft::List<int>::iterator it_ft_second = ++int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  before");
	compare_iterators(it_std_second, it_ft_second, "_second before");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());

	std::cout << std::endl;
	std::cout << "Splice range [++begin(), --end()) from second object "
		<< "into first before ++begin()" << std::endl;

	int_sort_std->splice(++int_sort_std->begin(),
			*int_unsort_std, ++int_unsort_std->begin(),
			--int_unsort_std->end());
	int_sort_ft->splice(++int_sort_ft->begin(),
			*int_unsort_ft, ++int_unsort_ft->begin(),
			--int_unsort_ft->end());

	compare_content(*int_sort_std, *int_sort_ft, "_first after");
	compare_size(*int_sort_std, *int_sort_ft, "_first after");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second after");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second after");
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  after");
	compare_iterators(it_std_second, it_ft_second, "_second after");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
}

TEST_F(Test_List, Operations_Remove) {
	std::cout << "----- REMOVE -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Remove elements with values 1 and 4" << std::endl;
	int_sort_std->remove(1);
	int_sort_std->remove(4);
	int_sort_ft->remove(1);
	int_sort_ft->remove(4);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

bool	is_odd(const int& val) {
	return (val % 2) == 1;
}

TEST_F(Test_List, Operations_Remove_if) {
	std::cout << "----- REMOVE_IF -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Remove odd elements" << std::endl;
	int_sort_std->remove_if(is_odd);
	int_sort_ft->remove_if(is_odd);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Operations_Unique_no_args_sorted) {
	std::cout << "----- UNIQUE (no arguments sorted) -----" << std::endl;
	std::list<int>	ctnr_std;
	ft::List<int>	ctnr_ft;

	int int_arr[] = { 1, 1, 2, 3, 3, 3, 4, 4, 5};
	for (int i = 0; i < 9; ++i) { ctnr_std.push_back(int_arr[i]); }
	for (int i = 0; i < 9; ++i) { ctnr_ft.push_back(int_arr[i]); }

	compare_content(ctnr_std, ctnr_ft, " before");
	compare_size(ctnr_std, ctnr_ft, " before");
	EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());

	std::cout << std::endl;
	std::cout << "Filter unique values" << std::endl;
	ctnr_std.unique();
	ctnr_ft.unique();

	compare_content(ctnr_std, ctnr_ft, " after");
	compare_size(ctnr_std, ctnr_ft, " after");
	EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
}

TEST_F(Test_List, Operations_Unique_no_args_unsorted) {
	std::cout << "----- UNIQUE (no arguments unsorted) -----" << std::endl;
	std::list<int>	ctnr_std;
	ft::List<int>	ctnr_ft;

	int int_arr[] = { 1, 2, 3, 3, 1, 3, 4, 4, 5 };
	for (int i = 0; i < 9; ++i) { ctnr_std.push_back(int_arr[i]); }
	for (int i = 0; i < 9; ++i) { ctnr_ft.push_back(int_arr[i]); }

	compare_content(ctnr_std, ctnr_ft, " before");
	compare_size(ctnr_std, ctnr_ft, " before");
	EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());

	std::cout << std::endl;
	std::cout << "Filter unique values" << std::endl;
	ctnr_std.unique();
	ctnr_ft.unique();

	compare_content(ctnr_std, ctnr_ft, " after");
	compare_size(ctnr_std, ctnr_ft, " after");
	EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
}

// a binary predicate implemented as a function:
bool	same_integral_part(double first, double second) {
	return ( int(first)==int(second) );
}

TEST_F(Test_List, Operations_Unique_binary_pred) {
	std::cout << "----- UNIQUE (binary predicate) -----" << std::endl;
	std::list<double>	ctnr_std;
	ft::List<double>	ctnr_ft;

	double dbl_arr[] = { 1.01, 1.05, 2.15, 2.25, 2.25, 3.40, 3.50, 4.70 };
	for (int i = 0; i < 8; ++i) { ctnr_std.push_back(dbl_arr[i]); }
	for (int i = 0; i < 8; ++i) { ctnr_ft.push_back(dbl_arr[i]); }

	compare_content(ctnr_std, ctnr_ft, " before");
	compare_size(ctnr_std, ctnr_ft, " before");
	EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());

	std::cout << std::endl;
	std::cout << "Filter values with same integral part" << std::endl;
	ctnr_std.unique(same_integral_part);
	ctnr_ft.unique(same_integral_part);

	compare_content(ctnr_std, ctnr_ft, " after");
	compare_size(ctnr_std, ctnr_ft, " after");
	EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
}

TEST_F(Test_List, Operations_Merge_no_args_sort_small_in_big) {
	std::cout << "----- MERGE (no args sorted smaller into bigger) -----"
		<< std::endl;

	std::list<int>	ctnr_std_first;
	std::list<int>	ctnr_std_second;
	ft::List<int>	ctnr_ft_first;
	ft::List<int>	ctnr_ft_second;

	int int_arr_first[] = { 1, 3, 4, 7, 9 };
	for (int i = 0; i < 5; ++i) { ctnr_std_first.push_back(int_arr_first[i]); }
	for (int i = 0; i < 5; ++i) { ctnr_ft_first.push_back(int_arr_first[i]); }

	int int_arr_second[] = { 2, 5, 6, 8 };
	for (int i = 0; i < 4; ++i) {
		ctnr_std_second.push_back(int_arr_second[i]);
	}
	for (int i = 0; i < 4; ++i) {
		ctnr_ft_second.push_back(int_arr_second[i]);
	}

	compare_content(ctnr_std_first, ctnr_ft_first, "_first before");
	compare_size(ctnr_std_first, ctnr_ft_first, "_first before");
	std::cout << std::endl;
	compare_content(ctnr_std_second, ctnr_ft_second, "_second before");
	compare_size(ctnr_std_second, ctnr_ft_second, "_second before");

	std::list<int>::iterator it_std_first = ++ctnr_std_first.begin();
	std::list<int>::iterator it_std_second = ++ctnr_std_second.begin();
	ft::List<int>::iterator it_ft_first = ++ctnr_ft_first.begin();
	ft::List<int>::iterator it_ft_second = ++ctnr_ft_second.begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  before");
	compare_iterators(it_std_second, it_ft_second, "_second before");

	EXPECT_EQ(*ctnr_std_first.begin(), *ctnr_ft_first.begin());
	EXPECT_EQ(*ctnr_std_second.begin(), *ctnr_ft_second.begin());
	EXPECT_EQ(ctnr_std_first.size(), ctnr_ft_first.size());
	EXPECT_EQ(ctnr_std_second.size(), ctnr_ft_second.size());

	std::cout << std::endl;
	std::cout << "Merge second object into first" << std::endl;

	ctnr_std_first.merge(ctnr_std_second);
	ctnr_ft_first.merge(ctnr_ft_second);

	compare_content(ctnr_std_first, ctnr_ft_first, "_first after");
	compare_size(ctnr_std_first, ctnr_ft_first, "_first after");
	std::cout << std::endl;
	compare_content(ctnr_std_second, ctnr_ft_second, "_second after");
	compare_size(ctnr_std_second, ctnr_ft_second, "_second after");
	std::cout << "Check iterators (should be the same)" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  after");
	compare_iterators(it_std_second, it_ft_second, "_second after");

	EXPECT_EQ(*ctnr_std_first.begin(), *ctnr_ft_first.begin());
	EXPECT_EQ(*ctnr_std_second.begin(), *ctnr_ft_second.begin());
	EXPECT_EQ(ctnr_std_first.size(), ctnr_ft_first.size());
	EXPECT_EQ(ctnr_std_second.size(), ctnr_ft_second.size());
}

TEST_F(Test_List, Operations_Merge_no_args_unsort_big_in_small) {
	std::cout << "----- MERGE (no args unsorted bigger into smaller) -----"
		<< std::endl;

	std::list<int>	ctnr_std_first;
	std::list<int>	ctnr_std_second;
	ft::List<int>	ctnr_ft_first;
	ft::List<int>	ctnr_ft_second;

	int int_arr_first[] = { 1, 4, 3 };
	for (int i = 0; i < 3; ++i) { ctnr_std_first.push_back(int_arr_first[i]); }
	for (int i = 0; i < 3; ++i) { ctnr_ft_first.push_back(int_arr_first[i]); }

	int int_arr_second[] = { 2, 9, 5, 7, 6, 8 };
	for (int i = 0; i < 6; ++i) {
		ctnr_std_second.push_back(int_arr_second[i]);
	}
	for (int i = 0; i < 6; ++i) {
		ctnr_ft_second.push_back(int_arr_second[i]);
	}

	compare_content(ctnr_std_first, ctnr_ft_first, "_first before");
	compare_size(ctnr_std_first, ctnr_ft_first, "_first before");
	std::cout << std::endl;
	compare_content(ctnr_std_second, ctnr_ft_second, "_second before");
	compare_size(ctnr_std_second, ctnr_ft_second, "_second before");

	std::list<int>::iterator it_std_first = ++ctnr_std_first.begin();
	std::list<int>::iterator it_std_second = ++ctnr_std_second.begin();
	ft::List<int>::iterator it_ft_first = ++ctnr_ft_first.begin();
	ft::List<int>::iterator it_ft_second = ++ctnr_ft_second.begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  before");
	compare_iterators(it_std_second, it_ft_second, "_second before");

	EXPECT_EQ(*ctnr_std_first.begin(), *ctnr_ft_first.begin());
	EXPECT_EQ(*ctnr_std_second.begin(), *ctnr_ft_second.begin());
	EXPECT_EQ(ctnr_std_first.size(), ctnr_ft_first.size());
	EXPECT_EQ(ctnr_std_second.size(), ctnr_ft_second.size());

	std::cout << std::endl;
	std::cout << "Merge second object into first" << std::endl;

	ctnr_std_first.merge(ctnr_std_second);
	ctnr_ft_first.merge(ctnr_ft_second);

	compare_content(ctnr_std_first, ctnr_ft_first, "_first after");
	compare_size(ctnr_std_first, ctnr_ft_first, "_first after");
	std::cout << std::endl;
	compare_content(ctnr_std_second, ctnr_ft_second, "_second after");
	compare_size(ctnr_std_second, ctnr_ft_second, "_second after");
	std::cout << "Check iterators (should be the same)" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  after");
	compare_iterators(it_std_second, it_ft_second, "_second after");

	EXPECT_EQ(*ctnr_std_first.begin(), *ctnr_ft_first.begin());
	EXPECT_EQ(*ctnr_std_second.begin(), *ctnr_ft_second.begin());
	EXPECT_EQ(ctnr_std_first.size(), ctnr_ft_first.size());
	EXPECT_EQ(ctnr_std_second.size(), ctnr_ft_second.size());
}

// compare only integral part:
bool	mycomparison(double first, double second) {
	return ( int(first)<int(second) );
}

TEST_F(Test_List, Operations_Merge_compare) {
	std::cout << "----- MERGE (compare) -----" << std::endl;

	std::list<double>	ctnr_std_first;
	std::list<double>	ctnr_std_second;
	ft::List<double>	ctnr_ft_first;
	ft::List<double>	ctnr_ft_second;

	double dbl_arr_first[] = { 1.01, 1.05, 2.15, 3.75 };
	for (int i = 0; i < 4; ++i) { ctnr_std_first.push_back(dbl_arr_first[i]); }
	for (int i = 0; i < 4; ++i) { ctnr_ft_first.push_back(dbl_arr_first[i]); }

	double dbl_arr_second[] = { 2.25, 3.40, 3.50, 4.70 };
	for (int i = 0; i < 4; ++i) {
		ctnr_std_second.push_back(dbl_arr_second[i]);
	}
	for (int i = 0; i < 4; ++i) {
		ctnr_ft_second.push_back(dbl_arr_second[i]);
	}

	compare_content(ctnr_std_first, ctnr_ft_first, "_first before");
	compare_size(ctnr_std_first, ctnr_ft_first, "_first before");
	std::cout << std::endl;
	compare_content(ctnr_std_second, ctnr_ft_second, "_second before");
	compare_size(ctnr_std_second, ctnr_ft_second, "_second before");

	std::list<double>::iterator it_std_first = ++ctnr_std_first.begin();
	std::list<double>::iterator it_std_second = ++ctnr_std_second.begin();
	ft::List<double>::iterator it_ft_first = ++ctnr_ft_first.begin();
	ft::List<double>::iterator it_ft_second = ++ctnr_ft_second.begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  before");
	compare_iterators(it_std_second, it_ft_second, "_second before");

	EXPECT_EQ(*ctnr_std_first.begin(), *ctnr_ft_first.begin());
	EXPECT_EQ(*ctnr_std_second.begin(), *ctnr_ft_second.begin());
	EXPECT_EQ(ctnr_std_first.size(), ctnr_ft_first.size());
	EXPECT_EQ(ctnr_std_second.size(), ctnr_ft_second.size());

	std::cout << std::endl;
	std::cout
		<< "Merge second object into first with comparing elements by function"
		<< std::endl;

	ctnr_std_first.merge(ctnr_std_second, mycomparison);
	ctnr_ft_first.merge(ctnr_ft_second, mycomparison);

	compare_content(ctnr_std_first, ctnr_ft_first, "_first after");
	compare_size(ctnr_std_first, ctnr_ft_first, "_first after");
	std::cout << std::endl;
	compare_content(ctnr_std_second, ctnr_ft_second, "_second after");
	compare_size(ctnr_std_second, ctnr_ft_second, "_second after");
	std::cout << "Check iterators (should be the same)" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  after");
	compare_iterators(it_std_second, it_ft_second, "_second after");

	EXPECT_EQ(*ctnr_std_first.begin(), *ctnr_ft_first.begin());
	EXPECT_EQ(*ctnr_std_second.begin(), *ctnr_ft_second.begin());
	EXPECT_EQ(ctnr_std_first.size(), ctnr_ft_first.size());
	EXPECT_EQ(ctnr_std_second.size(), ctnr_ft_second.size());
}

TEST_F(Test_List, Operations_Sort_no_args) {
	std::cout << "----- SORT (no args) -----" << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, " before");

	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(*(--int_unsort_std->end()), *(--int_unsort_ft->end()));

	std::cout << std::endl;
	std::cout << "Sort without arguments" << std::endl;
	int_unsort_std->sort();
	int_unsort_ft->sort();

	compare_content(*int_unsort_std, *int_unsort_ft, " after");
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(*(--int_unsort_std->end()), *(--int_unsort_ft->end()));
}

// comparison, not case sensitive.
bool	compare_nocase(const std::string& first, const std::string& second) {
	unsigned int i=0;
	while ( (i<first.length()) && (i<second.length()) ) {
		if (tolower(first[i])<tolower(second[i])) return true;
		else if (tolower(first[i])>tolower(second[i])) return false;
		++i;
	}
	return ( first.length() < second.length() );
}

TEST_F(Test_List, Operations_Sort_compare) {
	std::cout << "----- SORT (compare) -----" << std::endl;
	std::list<std::string>	ctnr_std;
	ctnr_std.push_back ("one");
	ctnr_std.push_back ("two");
	ctnr_std.push_back ("Three");
	std::list<std::string>::iterator it_std = ++ctnr_std.begin();

	ft::List<std::string>	ctnr_ft;
	ctnr_ft.push_back ("one");
	ctnr_ft.push_back ("two");
	ctnr_ft.push_back ("Three");
	ft::List<std::string>::iterator it_ft = ++ctnr_ft.begin();

	compare_content(ctnr_std, ctnr_ft, " before");
	compare_iterators(it_std, it_ft, " before");

	EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
	EXPECT_EQ(*(--ctnr_std.end()), *(--ctnr_ft.end()));

	std::cout << std::endl;
	std::cout << "Sort with function compare_nocase" << std::endl;
	ctnr_std.sort(compare_nocase);
	ctnr_ft.sort(compare_nocase);

	compare_content(ctnr_std, ctnr_ft, " after");
	compare_iterators(it_std, it_ft, " after");

	EXPECT_EQ(*ctnr_std.begin(), *ctnr_ft.begin());
	EXPECT_EQ(*(--ctnr_std.end()), *(--ctnr_ft.end()));
}

TEST_F(Test_List, Operations_Reverse) {
	std::cout << "----- Reverse -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");

	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::list<int>::iterator it_std = --int_sort_std->end();
	ft::List<int>::iterator it_ft = --int_sort_ft->end();

	compare_iterators(it_std, it_ft, " before");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*(--int_sort_std->end()), *(--int_sort_ft->end()));

	std::cout << std::endl;
	std::cout << "Reverse elements in container" << std::endl;
	int_sort_std->reverse();
	int_sort_ft->reverse();

	compare_content(*int_sort_std, *int_sort_ft, " after");

	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	compare_iterators(it_std, it_ft, " after");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*(--int_sort_std->end()), *(--int_sort_ft->end()));
}

TEST_F(Test_List, Relational_operators_Equal) {
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

		std::list<int>	ctnr_std_cpy(*int_sort_std);
		ft::List<int>	ctnr_ft_cpy(*int_sort_ft);

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

TEST_F(Test_List, Relational_operators_Not_equal) {
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

		std::list<int>	ctnr_std_cpy(*int_sort_std);
		ft::List<int>	ctnr_ft_cpy(*int_sort_ft);

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

TEST_F(Test_List, Relational_operators_Less) {
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

		std::list<int>	ctnr_std_cpy(*int_sort_std);
		ft::List<int>	ctnr_ft_cpy(*int_sort_ft);

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

TEST_F(Test_List, Relational_operators_Less_or_equal) {
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

		std::list<int>	ctnr_std_cpy(*int_sort_std);
		ft::List<int>	ctnr_ft_cpy(*int_sort_ft);

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

TEST_F(Test_List, Relational_operators_More) {
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

		std::list<int>	ctnr_std_cpy(*int_sort_std);
		ft::List<int>	ctnr_ft_cpy(*int_sort_ft);

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

TEST_F(Test_List, Relational_operators_More_or_equal) {
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

		std::list<int>	ctnr_std_cpy(*int_sort_std);
		ft::List<int>	ctnr_ft_cpy(*int_sort_ft);

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

TEST_F(Test_List, Non_member_overload_Swap) {
	std::cout << "----- NON-MEMBER OVERLOAD SWAP -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, "_first before");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second before");

	std::list<int>::iterator it_std_first = ++int_sort_std->begin();
	std::list<int>::iterator it_std_second = ++int_unsort_std->begin();
	ft::List<int>::iterator it_ft_first = ++int_sort_ft->begin();
	ft::List<int>::iterator it_ft_second = ++int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  before");
	compare_iterators(it_std_second, it_ft_second, "_second before");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());

	std::cout << std::endl;
	std::cout << "Swap first and second objects" << std::endl;

	std::swap(*int_sort_std, *int_unsort_std);
	ft::swap(*int_sort_ft, *int_unsort_ft);

	compare_content(*int_sort_std, *int_sort_ft, "_first after");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second after");
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	compare_iterators(it_std_first, it_ft_first, "_first  after");
	compare_iterators(it_std_second, it_ft_second, "_second after");

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
}
