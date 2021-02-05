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
		int unsort_int_array[] = { 8, 0, 6, 9, 7 };
		int_unsort_std = new std::list<int>;
		for (int i = 0; i < 5; ++i) {
			int_unsort_std->push_back(unsort_int_array[i]);
		}
		int_unsort_ft = new ft::List<int>;
		for (int i = 0; i < 5; ++i) {
			int_unsort_ft->push_back(unsort_int_array[i]);
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

TEST_F(Test_List, Constructor_default) {
	std::list<int> cnt_std;
	ft::List<int> cnt_ft;
	std::cout << "----- CONSTRUCTOR (default) -----" << std::endl;
	compare_size(cnt_std, cnt_ft);

	EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
	EXPECT_EQ(cnt_std.size(), cnt_ft.size());
}

TEST_F(Test_List, Constructor_fill) {
	{
		std::list<int> cnt_std(2);
		ft::List<int> cnt_ft(2);

		std::cout << "----- CONSTRUCTOR (fill) -----" << std::endl;
		compare_content(cnt_std, cnt_ft);

		EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
		EXPECT_EQ(cnt_std.size(), cnt_ft.size());
	}
	{
		std::list<std::string> cnt_std(2, "test");
		ft::List<std::string> cnt_ft(2, "test");

		std::cout << "----- CONSTRUCTOR (fill) -----" << std::endl;
		compare_content(cnt_std, cnt_ft);

		EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
		EXPECT_EQ(cnt_std.size(), cnt_ft.size());
	}
}

TEST_F(Test_List, Constructor_range) {
	std::list<int>	cnt_std_cpy(++(*int_sort_std).begin(),
			--(*int_sort_std).end());
	ft::List<int>	cnt_ft_cpy(++(*int_sort_ft).begin(),
			--(*int_sort_ft).end());

	std::cout << "----- CONSTRUCTOR (range) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " original");
	compare_content(cnt_std_cpy, cnt_ft_cpy, " ranged");
	EXPECT_EQ(*cnt_std_cpy.begin(), *cnt_ft_cpy.begin());
	EXPECT_EQ(*(--cnt_std_cpy.end()), *(--cnt_ft_cpy.end()));
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(cnt_std_cpy.size(), cnt_ft_cpy.size());
}

TEST_F(Test_List, Constructor_cpy) {
	std::list<int>	cnt_std_cpy(*int_unsort_std);
	ft::List<int>	cnt_ft_cpy(*int_unsort_ft);

	std::cout << "----- CONSTRUCTOR (copy) -----" << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, " original");
	compare_content(cnt_std_cpy, cnt_ft_cpy, " copy");
	EXPECT_EQ(*cnt_std_cpy.begin(), *cnt_ft_cpy.begin());
	EXPECT_EQ(*(--cnt_std_cpy.end()), *(--cnt_ft_cpy.end()));
	EXPECT_EQ(int_unsort_std->size(), cnt_std_cpy.size());
	EXPECT_EQ(int_unsort_ft->size(), cnt_ft_cpy.size());
}

TEST_F(Test_List, Destructor) {
	std::list<int>	* cnt_std = new std::list<int>(5, 5);
	ft::List<int>	* cnt_ft = new ft::List<int>(5, 5);

	std::cout << "----- DESTRUCTOR -----" << std::endl;
	delete(cnt_std);
	delete(cnt_ft);
}

TEST_F(Test_List, Operator_assign) {
	std::list<int>	cnt_std_cpy;
	ft::List<int>	cnt_ft_cpy;

	cnt_std_cpy = *int_sort_std;
	cnt_ft_cpy = *int_sort_ft;

	std::cout << "----- OPERATOR =  -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " original");
	compare_content(cnt_std_cpy, cnt_ft_cpy, " copy");
	EXPECT_EQ(*cnt_std_cpy.begin(), *cnt_ft_cpy.begin());
	EXPECT_EQ(*(--cnt_std_cpy.end()), *(--cnt_ft_cpy.end()));
	EXPECT_EQ(int_sort_std->size(), cnt_std_cpy.size());
	EXPECT_EQ(int_sort_ft->size(), cnt_ft_cpy.size());
}

TEST_F(Test_List, Iterators_begin) {
	std::cout << "----- ITERATOR BEGIN -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	std::cout << "std   begin: " << *int_sort_std->begin() << std::endl;
	std::cout << "std ++begin: " << *(++int_sort_std->begin())
		<< std::endl;
	std::cout << " ft   begin: " << *int_sort_ft->begin() << std::endl;
	std::cout << " ft ++begin: " << *(++int_sort_ft->begin()) << std::endl;
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*(++int_sort_std->begin()), *(++int_sort_ft->begin()));
}

TEST_F(Test_List, Iterators_end) {
	std::cout << "----- ITERATOR END -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	std::list<int>::iterator it_std = --int_sort_std->end();

	std::cout << "std    --end:  " << *it_std << std::endl;
	std::cout << "std --(--end): " << *(--it_std) << std::endl;

	ft::List<int>::iterator it_ft = --int_sort_ft->end();
	std::cout << " ft    --end:  " << *it_ft << std::endl;
	std::cout << " ft --(--end): " << *(--it_ft) << std::endl;

	EXPECT_EQ(*(--int_sort_std->end()), *(--int_sort_ft->end()));
	EXPECT_EQ(*(--it_std), *(--it_ft));
}

TEST_F(Test_List, Iterators_rbegin) {
	std::cout << "----- ITERATOR RBEGIN -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	std::cout << "std   rbegin: " << *int_sort_std->rbegin() << std::endl;
	std::cout << "std ++rbegin: " << *(++int_sort_std->rbegin())
		<< std::endl;
	std::cout << " ft   rbegin: " << *int_sort_ft->rbegin() << std::endl;
	std::cout << " ft ++rbegin: " << *(++int_sort_ft->rbegin())
		<< std::endl;
	EXPECT_EQ(*int_sort_std->rbegin(), *int_sort_ft->rbegin());
	EXPECT_EQ(*(++int_sort_std->rbegin()),
			*(++int_sort_ft->rbegin()));
}

TEST_F(Test_List, Iterators_rend) {
	std::cout << "----- ITERATOR REND -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	std::list<int>::reverse_iterator it_std = --int_sort_std->rend();

	std::cout << "std    --rend:  " << *it_std << std::endl;
	std::cout << "std --(--rend): " << *(--it_std) << std::endl;

	ft::List<int>::reverse_iterator it_ft = --int_sort_ft->rend();
	std::cout << " ft    --rend:  " << *it_ft << std::endl;
	std::cout << " ft --(--rend): " << *(--it_ft) << std::endl;

	EXPECT_EQ(*(--int_sort_std->rend()), *(--int_sort_ft->rend()));
	EXPECT_EQ(*(--it_std), *(--it_ft));
}

TEST_F(Test_List, Modifiers_clear) {
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

TEST_F(Test_List, Modifiers_erase_position) {
	std::cout << "----- ERASE (position) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	int_sort_std->erase(int_sort_std->begin());
	int_sort_ft->erase(int_sort_ft->begin());

	std::cout << std::endl;
	std::cout << "Erase begin() element" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_erase_range) {
	std::cout << "----- ERASE (position) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	int_sort_std->erase(++int_sort_std->begin(),
			--int_sort_std->end());
	int_sort_ft->erase(++int_sort_ft->begin(),
			--int_sort_ft->end());

	std::cout << std::endl;
	std::cout << "Erase range [++begin(), --end())" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_pop_front) {
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

TEST_F(Test_List, Modifiers_pop_back) {
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

TEST_F(Test_List, Modifiers_element_access_front) {
	std::cout << "----- FRONT -----" << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft);
	std::cout << "std front: " << int_unsort_std->front() << std::endl;
	std::cout << " ft front: " << int_unsort_ft->front() << std::endl;
	EXPECT_EQ(int_unsort_std->front(), int_unsort_ft->front());

	std::cout << "Modify data in element by increment reference" << std::endl;
	++int_unsort_std->front();
	++int_unsort_ft->front();
	compare_content(*int_unsort_std, *int_unsort_ft);
	EXPECT_EQ(int_unsort_std->front(), int_unsort_ft->front());
}

TEST_F(Test_List, Modifiers_element_access_back) {
	std::cout << "----- BACK -----" << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft);
	std::cout << "std back: " << int_unsort_std->back() << std::endl;
	std::cout << " ft back: " << int_unsort_ft->back() << std::endl;
	EXPECT_EQ(int_unsort_std->back(), int_unsort_ft->back());

	std::cout << std::endl;
	std::cout << "Modify data in element by increment reference" << std::endl;
	++int_unsort_std->back();
	++int_unsort_ft->back();
	compare_content(*int_unsort_std, *int_unsort_ft);
	EXPECT_EQ(int_unsort_std->back(), int_unsort_ft->back());
}

TEST_F(Test_List, Modifiers_assign_range) {
	std::cout << "----- ASSIGN (range) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " original");

	std::list<int>	cnt_std_second;
	ft::List<int>	cnt_ft_second;

	std::cout << std::endl;
	compare_size(cnt_std_second, cnt_ft_second, "_second before");
	std::cout << std::endl;
	std::cout << "Assign by range [++begin(), --end()) from original"
		<< std::endl;

	cnt_std_second.assign(++int_sort_std->begin(),
												--int_sort_std->end());
	cnt_ft_second.assign(++int_sort_ft->begin(),
												--int_sort_ft->end());

	compare_content(cnt_std_second, cnt_ft_second, " assigned");
	compare_size(cnt_std_second, cnt_ft_second, "_second after");

	EXPECT_EQ(*cnt_std_second.begin(), *cnt_ft_second.begin());
	EXPECT_EQ(cnt_std_second.size(), cnt_ft_second.size());
}

TEST_F(Test_List, Modifiers_assign_fill) {
	std::cout << "----- ASSIGN (fill) -----" << std::endl;
	std::list<int>	cnt_std;
	ft::List<int>	cnt_ft;
	compare_size(cnt_std, cnt_ft, " before");

	std::cout << std::endl;
	std::cout << "Assign fill" << std::endl;

	cnt_std.assign(5, 7);
	cnt_ft.assign(5, 7);

	compare_content(cnt_std, cnt_ft, " assigned");
	compare_size(cnt_std, cnt_ft, " after");

	EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
	EXPECT_EQ(cnt_std.size(), cnt_ft.size());
}

TEST_F(Test_List, Modifiers_insert_single_element) {
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

TEST_F(Test_List, Modifiers_insert_fill) {
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

TEST_F(Test_List, Modifiers_insert_range) {
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

TEST_F(Test_List, Modifiers_swap) {
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
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());

	std::cout << std::endl;
	std::cout << "Swap first and second objects" << std::endl;

	int_sort_std->swap(*int_unsort_std);
	int_sort_ft->swap(*int_unsort_ft);

	compare_content(*int_sort_std, *int_sort_ft, "_first after");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second after");
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
}

TEST_F(Test_List, Modifiers_resize_reduce) {
	std::cout << "----- RESIZE (reduce) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Downsize to 2" << std::endl;
	int_sort_std->resize(2);
	int_sort_ft->resize(2);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_resize_incrase_default) {
	std::cout << "----- RESIZE (incrase default) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Upsize to 8 with default type value for new elements"
		<< std::endl;
	int_sort_std->resize(8);
	int_sort_ft->resize(8);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_resize_incrase_fill) {
	std::cout << "----- RESIZE (incrase fill) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");
	compare_size(*int_sort_std, *int_sort_ft, " before");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Upsize to 8 with '7' value for new elements" << std::endl;
	int_sort_std->resize(8, 7);
	int_sort_ft->resize(8, 7);

	compare_content(*int_sort_std, *int_sort_ft, " after");
	compare_size(*int_sort_std, *int_sort_ft, " after");
	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Operations_splice_entire_list) {
	std::cout << "----- SPLICE (entire list) -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, "_first before");
	compare_size(*int_sort_std, *int_sort_ft, "_first before");
	std::cout << std::endl;
	compare_content(*int_unsort_std, *int_unsort_ft, "_second before");
	compare_size(*int_unsort_std, *int_unsort_ft, "_second before");
	std::cout << std::endl;
	std::cout << "std_second before:"; print_container(*int_unsort_std);
	std::cout << " ft_second before:"; print_container(*int_unsort_ft);
	std::cout << "std_second size before: " << int_unsort_std->size()
		<< std::endl;
	std::cout << " ft_second size before: " << int_unsort_ft->size()
		<< std::endl;

	std::list<int>::iterator it_std_first = ++int_sort_std->begin();
	std::list<int>::iterator it_std_second = ++int_unsort_std->begin();
	ft::List<int>::iterator it_ft_first = ++int_sort_ft->begin();
	ft::List<int>::iterator it_ft_second = ++int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

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
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
}

TEST_F(Test_List, Operations_splice_single_element) {
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
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

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
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
}

TEST_F(Test_List, Operations_splice_range) {
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
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

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
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
}

TEST_F(Test_List, Operations_remove) {
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

TEST_F(Test_List, Operations_remove_if) {
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

TEST_F(Test_List, Operations_unique_no_args_sorted) {
	std::cout << "----- UNIQUE (no arguments sorted) -----" << std::endl;
	std::list<int>	cnt_std;
	ft::List<int>	cnt_ft;

	int int_array[] = { 1, 1, 2, 3, 3, 3, 4, 4, 5};
	for (int i = 0; i < 9; ++i) { cnt_std.push_back(int_array[i]); }
	for (int i = 0; i < 9; ++i) { cnt_ft.push_back(int_array[i]); }

	compare_content(cnt_std, cnt_ft, " before");
	compare_size(cnt_std, cnt_ft, " before");
	EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
	EXPECT_EQ(cnt_std.size(), cnt_ft.size());

	std::cout << std::endl;
	std::cout << "Filter unique values" << std::endl;
	cnt_std.unique();
	cnt_ft.unique();

	compare_content(cnt_std, cnt_ft, " after");
	compare_size(cnt_std, cnt_ft, " after");
	EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
	EXPECT_EQ(cnt_std.size(), cnt_ft.size());
}

TEST_F(Test_List, Operations_unique_no_args_unsorted) {
	std::cout << "----- UNIQUE (no arguments unsorted) -----" << std::endl;
	std::list<int>	cnt_std;
	ft::List<int>	cnt_ft;

	int int_array[] = { 1, 2, 3, 3, 1, 3, 4, 4, 5 };
	for (int i = 0; i < 9; ++i) { cnt_std.push_back(int_array[i]); }
	for (int i = 0; i < 9; ++i) { cnt_ft.push_back(int_array[i]); }

	compare_content(cnt_std, cnt_ft, " before");
	compare_size(cnt_std, cnt_ft, " before");
	EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
	EXPECT_EQ(cnt_std.size(), cnt_ft.size());

	std::cout << std::endl;
	std::cout << "Filter unique values" << std::endl;
	cnt_std.unique();
	cnt_ft.unique();

	compare_content(cnt_std, cnt_ft, " after");
	compare_size(cnt_std, cnt_ft, " after");
	EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
	EXPECT_EQ(cnt_std.size(), cnt_ft.size());
}

// a binary predicate implemented as a function:
bool	same_integral_part(double first, double second) {
	return ( int(first)==int(second) );
}

TEST_F(Test_List, Operations_unique_binary_pred) {
	std::cout << "----- UNIQUE (binary predicate) -----" << std::endl;
	std::list<double>	cnt_std;
	ft::List<double>	cnt_ft;

	double dbl_array[] = { 1.01, 1.05, 2.15, 2.25, 2.25, 3.40, 3.50, 4.70 };
	for (int i = 0; i < 8; ++i) { cnt_std.push_back(dbl_array[i]); }
	for (int i = 0; i < 8; ++i) { cnt_ft.push_back(dbl_array[i]); }

	compare_content(cnt_std, cnt_ft, " before");
	compare_size(cnt_std, cnt_ft, " before");
	EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
	EXPECT_EQ(cnt_std.size(), cnt_ft.size());

	std::cout << std::endl;
	std::cout << "Filter values with same integral part" << std::endl;
	cnt_std.unique(same_integral_part);
	cnt_ft.unique(same_integral_part);

	compare_content(cnt_std, cnt_ft, " after");
	compare_size(cnt_std, cnt_ft, " after");
	EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
	EXPECT_EQ(cnt_std.size(), cnt_ft.size());
}

TEST_F(Test_List, Operations_merge_no_args_sort_small_in_big) {
	std::cout << "----- MERGE (no args sorted smaller into bigger) -----"
		<< std::endl;

	std::list<int>	cnt_std_first;
	std::list<int>	cnt_std_second;
	ft::List<int>	cnt_ft_first;
	ft::List<int>	cnt_ft_second;

	int int_array_first[] = { 1, 3, 4, 7, 9 };
	for (int i = 0; i < 5; ++i) { cnt_std_first.push_back(int_array_first[i]); }
	for (int i = 0; i < 5; ++i) { cnt_ft_first.push_back(int_array_first[i]); }

	int int_array_second[] = { 2, 5, 6, 8 };
	for (int i = 0; i < 4; ++i) {
		cnt_std_second.push_back(int_array_second[i]);
	}
	for (int i = 0; i < 4; ++i) {
		cnt_ft_second.push_back(int_array_second[i]);
	}

	compare_content(cnt_std_first, cnt_ft_first, "_first before");
	compare_size(cnt_std_first, cnt_ft_first, "_first before");
	std::cout << std::endl;
	compare_content(cnt_std_second, cnt_ft_second, "_second before");
	compare_size(cnt_std_second, cnt_ft_second, "_second before");

	std::list<int>::iterator it_std_first = ++cnt_std_first.begin();
	std::list<int>::iterator it_std_second = ++cnt_std_second.begin();
	ft::List<int>::iterator it_ft_first = ++cnt_ft_first.begin();
	ft::List<int>::iterator it_ft_second = ++cnt_ft_second.begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

	EXPECT_EQ(*cnt_std_first.begin(), *cnt_ft_first.begin());
	EXPECT_EQ(*cnt_std_second.begin(), *cnt_ft_second.begin());
	EXPECT_EQ(cnt_std_first.size(), cnt_ft_first.size());
	EXPECT_EQ(cnt_std_second.size(), cnt_ft_second.size());

	std::cout << std::endl;
	std::cout << "Merge second object into first" << std::endl;

	cnt_std_first.merge(cnt_std_second);
	cnt_ft_first.merge(cnt_ft_second);

	compare_content(cnt_std_first, cnt_ft_first, "_first after");
	compare_size(cnt_std_first, cnt_ft_first, "_first after");
	std::cout << std::endl;
	compare_content(cnt_std_second, cnt_ft_second, "_second after");
	compare_size(cnt_std_second, cnt_ft_second, "_second after");
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*cnt_std_first.begin(), *cnt_ft_first.begin());
	EXPECT_EQ(*cnt_std_second.begin(), *cnt_ft_second.begin());
	EXPECT_EQ(cnt_std_first.size(), cnt_ft_first.size());
	EXPECT_EQ(cnt_std_second.size(), cnt_ft_second.size());
}

TEST_F(Test_List, Operations_merge_no_args_unsort_big_in_small) {
	std::cout << "----- MERGE (no args unsorted bigger into smaller) -----"
		<< std::endl;

	std::list<int>	cnt_std_first;
	std::list<int>	cnt_std_second;
	ft::List<int>	cnt_ft_first;
	ft::List<int>	cnt_ft_second;

	int int_array_first[] = { 1, 4, 3 };
	for (int i = 0; i < 3; ++i) { cnt_std_first.push_back(int_array_first[i]); }
	for (int i = 0; i < 3; ++i) { cnt_ft_first.push_back(int_array_first[i]); }

	int int_array_second[] = { 2, 9, 5, 7, 6, 8 };
	for (int i = 0; i < 6; ++i) {
		cnt_std_second.push_back(int_array_second[i]);
	}
	for (int i = 0; i < 6; ++i) {
		cnt_ft_second.push_back(int_array_second[i]);
	}

	compare_content(cnt_std_first, cnt_ft_first, "_first before");
	compare_size(cnt_std_first, cnt_ft_first, "_first before");
	std::cout << std::endl;
	compare_content(cnt_std_second, cnt_ft_second, "_second before");
	compare_size(cnt_std_second, cnt_ft_second, "_second before");

	std::list<int>::iterator it_std_first = ++cnt_std_first.begin();
	std::list<int>::iterator it_std_second = ++cnt_std_second.begin();
	ft::List<int>::iterator it_ft_first = ++cnt_ft_first.begin();
	ft::List<int>::iterator it_ft_second = ++cnt_ft_second.begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

	EXPECT_EQ(*cnt_std_first.begin(), *cnt_ft_first.begin());
	EXPECT_EQ(*cnt_std_second.begin(), *cnt_ft_second.begin());
	EXPECT_EQ(cnt_std_first.size(), cnt_ft_first.size());
	EXPECT_EQ(cnt_std_second.size(), cnt_ft_second.size());

	std::cout << std::endl;
	std::cout << "Merge second object into first" << std::endl;

	cnt_std_first.merge(cnt_std_second);
	cnt_ft_first.merge(cnt_ft_second);

	compare_content(cnt_std_first, cnt_ft_first, "_first after");
	compare_size(cnt_std_first, cnt_ft_first, "_first after");
	std::cout << std::endl;
	compare_content(cnt_std_second, cnt_ft_second, "_second after");
	compare_size(cnt_std_second, cnt_ft_second, "_second after");
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*cnt_std_first.begin(), *cnt_ft_first.begin());
	EXPECT_EQ(*cnt_std_second.begin(), *cnt_ft_second.begin());
	EXPECT_EQ(cnt_std_first.size(), cnt_ft_first.size());
	EXPECT_EQ(cnt_std_second.size(), cnt_ft_second.size());
}

// compare only integral part:
bool	mycomparison(double first, double second) {
	return ( int(first)<int(second) );
}

TEST_F(Test_List, Operations_merge_compare) {
	std::cout << "----- MERGE (compare) -----" << std::endl;

	std::list<double>	cnt_std_first;
	std::list<double>	cnt_std_second;
	ft::List<double>	cnt_ft_first;
	ft::List<double>	cnt_ft_second;

	double dbl_array_first[] = { 1.01, 1.05, 2.15, 3.75 };
	for (int i = 0; i < 4; ++i) { cnt_std_first.push_back(dbl_array_first[i]); }
	for (int i = 0; i < 4; ++i) { cnt_ft_first.push_back(dbl_array_first[i]); }

	double dbl_array_second[] = { 2.25, 3.40, 3.50, 4.70 };
	for (int i = 0; i < 4; ++i) {
		cnt_std_second.push_back(dbl_array_second[i]);
	}
	for (int i = 0; i < 4; ++i) {
		cnt_ft_second.push_back(dbl_array_second[i]);
	}

	compare_content(cnt_std_first, cnt_ft_first, "_first before");
	compare_size(cnt_std_first, cnt_ft_first, "_first before");
	std::cout << std::endl;
	compare_content(cnt_std_second, cnt_ft_second, "_second before");
	compare_size(cnt_std_second, cnt_ft_second, "_second before");

	std::list<double>::iterator it_std_first = ++cnt_std_first.begin();
	std::list<double>::iterator it_std_second = ++cnt_std_second.begin();
	ft::List<double>::iterator it_ft_first = ++cnt_ft_first.begin();
	ft::List<double>::iterator it_ft_second = ++cnt_ft_second.begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

	EXPECT_EQ(*cnt_std_first.begin(), *cnt_ft_first.begin());
	EXPECT_EQ(*cnt_std_second.begin(), *cnt_ft_second.begin());
	EXPECT_EQ(cnt_std_first.size(), cnt_ft_first.size());
	EXPECT_EQ(cnt_std_second.size(), cnt_ft_second.size());

	std::cout << std::endl;
	std::cout
		<< "Merge second object into first with comparing elements by function"
		<< std::endl;

	cnt_std_first.merge(cnt_std_second, mycomparison);
	cnt_ft_first.merge(cnt_ft_second, mycomparison);

	compare_content(cnt_std_first, cnt_ft_first, "_first after");
	compare_size(cnt_std_first, cnt_ft_first, "_first after");
	std::cout << std::endl;
	compare_content(cnt_std_second, cnt_ft_second, "_second after");
	compare_size(cnt_std_second, cnt_ft_second, "_second after");
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*cnt_std_first.begin(), *cnt_ft_first.begin());
	EXPECT_EQ(*cnt_std_second.begin(), *cnt_ft_second.begin());
	EXPECT_EQ(cnt_std_first.size(), cnt_ft_first.size());
	EXPECT_EQ(cnt_std_second.size(), cnt_ft_second.size());
}

TEST_F(Test_List, Operations_sort_no_args) {
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

TEST_F(Test_List, Operations_sort_compare) {
	std::cout << "----- SORT (compare) -----" << std::endl;
	std::list<std::string>	cnt_std;
	cnt_std.push_back ("one");
	cnt_std.push_back ("two");
	cnt_std.push_back ("Three");
	std::list<std::string>::iterator it_std = ++cnt_std.begin();

	ft::List<std::string>	cnt_ft;
	cnt_ft.push_back ("one");
	cnt_ft.push_back ("two");
	cnt_ft.push_back ("Three");
	ft::List<std::string>::iterator it_ft = ++cnt_ft.begin();

	compare_content(cnt_std, cnt_ft, " before");
	std::cout << "it_std before: " << *it_std << std::endl;
	std::cout << "it_ft  before: " << *it_ft << std::endl;

	EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
	EXPECT_EQ(*(--cnt_std.end()), *(--cnt_ft.end()));

	std::cout << std::endl;
	std::cout << "Sort with function compare_nocase" << std::endl;
	cnt_std.sort(compare_nocase);
	cnt_ft.sort(compare_nocase);

	compare_content(cnt_std, cnt_ft, " after");
	std::cout << "it_std after: " << *it_std << std::endl;
	std::cout << "it_ft  after: " << *it_ft << std::endl;

	EXPECT_EQ(*cnt_std.begin(), *cnt_ft.begin());
	EXPECT_EQ(*(--cnt_std.end()), *(--cnt_ft.end()));
}

TEST_F(Test_List, Operations_reverse) {
	std::cout << "----- Reverse -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft, " before");

	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::list<int>::iterator it_std = --int_sort_std->end();
	ft::List<int>::iterator it_ft = --int_sort_ft->end();

	std::cout << "it_std: " << *it_std << std::endl;
	std::cout << "it_ft : " << *it_ft << std::endl;

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*(--int_sort_std->end()), *(--int_sort_ft->end()));

	std::cout << std::endl;
	std::cout << "Reverse elements in container" << std::endl;
	int_sort_std->reverse();
	int_sort_ft->reverse();

	compare_content(*int_sort_std, *int_sort_ft, " after");

	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std: " << *it_std << std::endl;
	std::cout << "it_ft : " << *it_ft << std::endl;

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*(--int_sort_std->end()), *(--int_sort_ft->end()));
}

TEST_F(Test_List, Capacity_size) {
	std::cout << "----- SIZE -----" << std::endl;
	compare_content(*int_sort_std, *int_sort_ft);
	compare_size(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
}

TEST_F(Test_List, Capacity_max_size) {
	std::cout << "----- MAX SIZE -----" << std::endl;
	ft::List<int>	cnt_ft;
	std::cout << " ft max_size: " << cnt_ft.max_size() << std::endl;
}

TEST_F(Test_List, Capacity_empty) {
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

TEST_F(Test_List, Non_member_overload_swap) {
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
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

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
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*int_sort_std->begin(), *int_sort_ft->begin());
	EXPECT_EQ(*int_unsort_std->begin(), *int_unsort_ft->begin());
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_unsort_std->size(), int_unsort_ft->size());
}

TEST_F(Test_List, relational_operators_equal) {
	{
		std::cout << "----- RELATIONAL OPERATORS == -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");

		std::cout << std::endl;
		std::cout << "std_first == std_second: " << std::boolalpha
			<< (int_sort_std == int_unsort_std) << std::endl;
		std::cout << " ft_first ==  ft_second: " << std::boolalpha
			<< (int_sort_ft == int_unsort_ft) << std::endl;

		EXPECT_EQ((*int_sort_std == *int_unsort_std), 0);
		EXPECT_EQ((*int_sort_ft == *int_unsort_ft), 0);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS == -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;

		std::list<int>	cnt_std_cpy(*int_sort_std);
		ft::List<int>	cnt_ft_cpy(*int_sort_ft);

		compare_content(cnt_std_cpy, cnt_ft_cpy, "_second");

		std::cout << std::endl;
		std::cout << "std_first == std_second: " << std::boolalpha
			<< (*int_sort_std == cnt_std_cpy) << std::endl;
		std::cout << " ft_first ==  ft_second: " << std::boolalpha
			<< (*int_sort_ft == cnt_ft_cpy) << std::endl;

		EXPECT_EQ((*int_sort_std == cnt_std_cpy), 1);
		EXPECT_EQ((*int_sort_ft == cnt_ft_cpy), 1);
	}
}

TEST_F(Test_List, relational_operators_not_equal) {
	{
		std::cout << "----- RELATIONAL OPERATORS != -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");

		std::cout << std::endl;
		std::cout << "std_first != std_second: " << std::boolalpha
			<< (int_sort_std != int_unsort_std) << std::endl;
		std::cout << " ft_first !=  ft_second: " << std::boolalpha
			<< (int_sort_ft != int_unsort_ft) << std::endl;

		EXPECT_EQ((*int_sort_std != *int_unsort_std), 1);
		EXPECT_EQ((*int_sort_ft != *int_unsort_ft), 1);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS != -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;

		std::list<int>	cnt_std_cpy(*int_sort_std);
		ft::List<int>	cnt_ft_cpy(*int_sort_ft);

		compare_content(cnt_std_cpy, cnt_ft_cpy, "_second");

		std::cout << std::endl;
		std::cout << "std_first != std_second: " << std::boolalpha
			<< (*int_sort_std != cnt_std_cpy) << std::endl;
		std::cout << " ft_first !=  ft_second: " << std::boolalpha
			<< (*int_sort_ft != cnt_ft_cpy) << std::endl;

		EXPECT_EQ((*int_sort_std != cnt_std_cpy), 0);
		EXPECT_EQ((*int_sort_ft != cnt_ft_cpy), 0);
	}
}

TEST_F(Test_List, relational_operators_less) {
	{
		std::cout << "----- RELATIONAL OPERATORS < -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");

		std::cout << std::endl;
		std::cout << "std_first < std_second: " << std::boolalpha
			<< (int_sort_std < int_unsort_std) << std::endl;
		std::cout << " ft_first <  ft_second: " << std::boolalpha
			<< (int_sort_ft < int_unsort_ft) << std::endl;

		EXPECT_EQ((*int_sort_std < *int_unsort_std), 1);
		EXPECT_EQ((*int_sort_ft < *int_unsort_ft), 1);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS < -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;

		std::list<int>	cnt_std_cpy(*int_sort_std);
		ft::List<int>	cnt_ft_cpy(*int_sort_ft);

		compare_content(cnt_std_cpy, cnt_ft_cpy, "_second");

		std::cout << std::endl;
		std::cout << "std_first < std_second: " << std::boolalpha
			<< (*int_sort_std < cnt_std_cpy) << std::endl;
		std::cout << " ft_first <  ft_second: " << std::boolalpha
			<< (*int_sort_ft < cnt_ft_cpy) << std::endl;

		EXPECT_EQ((*int_sort_std < cnt_std_cpy), 0);
		EXPECT_EQ((*int_sort_ft < cnt_ft_cpy), 0);
	}
}

TEST_F(Test_List, relational_operators_less_or_equal) {
	{
		std::cout << "----- RELATIONAL OPERATORS <= -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");

		std::cout << std::endl;
		std::cout << "std_first <= std_second: " << std::boolalpha
			<< (int_sort_std <= int_unsort_std) << std::endl;
		std::cout << " ft_first <=  ft_second: " << std::boolalpha
			<< (int_sort_ft <= int_unsort_ft) << std::endl;

		EXPECT_EQ((*int_sort_std <= *int_unsort_std), 1);
		EXPECT_EQ((*int_sort_ft <= *int_unsort_ft), 1);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS <= -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;

		std::list<int>	cnt_std_cpy(*int_sort_std);
		ft::List<int>	cnt_ft_cpy(*int_sort_ft);

		compare_content(cnt_std_cpy, cnt_ft_cpy, "_second");

		std::cout << std::endl;
		std::cout << "std_first <= std_second: " << std::boolalpha
			<< (*int_sort_std <= cnt_std_cpy) << std::endl;
		std::cout << " ft_first <=  ft_second: " << std::boolalpha
			<< (*int_sort_ft <= cnt_ft_cpy) << std::endl;

		EXPECT_EQ((*int_sort_std <= cnt_std_cpy), 1);
		EXPECT_EQ((*int_sort_ft <= cnt_ft_cpy), 1);
	}
}

TEST_F(Test_List, relational_operators_more) {
	{
		std::cout << "----- RELATIONAL OPERATORS > -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");

		std::cout << std::endl;
		std::cout << "std_first > std_second: " << std::boolalpha
			<< (int_sort_std > int_unsort_std) << std::endl;
		std::cout << " ft_first >  ft_second: " << std::boolalpha
			<< (int_sort_ft > int_unsort_ft) << std::endl;

		EXPECT_EQ((*int_sort_std > *int_unsort_std), 0);
		EXPECT_EQ((*int_sort_ft > *int_unsort_ft), 0);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS > -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;

		std::list<int>	cnt_std_cpy(*int_sort_std);
		ft::List<int>	cnt_ft_cpy(*int_sort_ft);

		compare_content(cnt_std_cpy, cnt_ft_cpy, "_second");

		std::cout << std::endl;
		std::cout << "std_first > std_second: " << std::boolalpha
			<< (*int_sort_std > cnt_std_cpy) << std::endl;
		std::cout << " ft_first >  ft_second: " << std::boolalpha
			<< (*int_sort_ft > cnt_ft_cpy) << std::endl;

		EXPECT_EQ((*int_sort_std > cnt_std_cpy), 0);
		EXPECT_EQ((*int_sort_ft > cnt_ft_cpy), 0);
	}
}

TEST_F(Test_List, relational_operators_more_or_equal) {
	{
		std::cout << "----- RELATIONAL OPERATORS >= -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;
		compare_content(*int_unsort_std, *int_unsort_ft, "_second");

		std::cout << std::endl;
		std::cout << "std_first >= std_second: " << std::boolalpha
			<< (int_sort_std > int_unsort_std) << std::endl;
		std::cout << " ft_first >=  ft_second: " << std::boolalpha
			<< (int_sort_ft > int_unsort_ft) << std::endl;

		EXPECT_EQ((*int_sort_std >= *int_unsort_std), 0);
		EXPECT_EQ((*int_sort_ft >= *int_unsort_ft), 0);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS >= -----" << std::endl;
		compare_content(*int_sort_std, *int_sort_ft, "_first");
		std::cout << std::endl;

		std::list<int>	cnt_std_cpy(*int_sort_std);
		ft::List<int>	cnt_ft_cpy(*int_sort_ft);

		compare_content(cnt_std_cpy, cnt_ft_cpy, "_second");

		std::cout << std::endl;
		std::cout << "std_first >= std_second: " << std::boolalpha
			<< (*int_sort_std >= cnt_std_cpy) << std::endl;
		std::cout << " ft_first >=  ft_second: " << std::boolalpha
			<< (*int_sort_ft >= cnt_ft_cpy) << std::endl;

		EXPECT_EQ((*int_sort_std >= cnt_std_cpy), 1);
		EXPECT_EQ((*int_sort_ft >= cnt_ft_cpy), 1);
	}
}

//TEST(INF_LOOP, Loop) {
//	while (1) {}
//}