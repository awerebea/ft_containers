/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtests_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:07:59 by awerebea          #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "List.hpp"
#include <list>

class Test_List : public ::testing::Test {
protected:
	void SetUp() {
		list_int_sort_std = new std::list<int>;
		for (int i = 0; i < 5; ++i) {
			list_int_sort_std->push_back(i + 1);
		}
		list_int_sort_ft = new ft::List<int>;
		for (int i = 0; i < 5; ++i) {
			list_int_sort_ft->push_back(i + 1);
		}
		int unsort_int_array[] = { 8, 0, 6, 9, 7 };
		list_int_unsort_std = new std::list<int>;
		for (int i = 0; i < 5; ++i) {
			list_int_unsort_std->push_back(unsort_int_array[i]);
		}
		list_int_unsort_ft = new ft::List<int>;
		for (int i = 0; i < 5; ++i) {
			list_int_unsort_ft->push_back(unsort_int_array[i]);
		}
	}
	void TearDown() {
		delete list_int_sort_std;
		delete list_int_sort_ft;

		delete list_int_unsort_std;
		delete list_int_unsort_ft;
	}
	std::list<int> * list_int_sort_std;
	ft::List<int> * list_int_sort_ft;

	std::list<int> * list_int_unsort_std;
	ft::List<int> * list_int_unsort_ft;
};

template <typename T>
void print_container(T& obj) {
	for (typename T::iterator it = obj.begin(); it != obj.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

TEST_F(Test_List, Constructor_default) {
	std::list<int> lst_std;
	ft::List<int> lst_ft;
	std::cout << "----- CONSTRUCTOR (default) -----" << std::endl;
	std::cout << "std size: " << lst_std.size() << std::endl;
	std::cout << " ft size: " << lst_ft.size() << std::endl;

	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

TEST_F(Test_List, Constructor_fill) {
	{
		std::list<int> lst_std(2);
		ft::List<int> lst_ft(2);

		std::cout << "----- CONSTRUCTOR (fill) -----" << std::endl;
		std::cout << "std:"; print_container(lst_std);
		std::cout << " ft:"; print_container(lst_ft);

		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
		EXPECT_EQ(lst_std.size(), lst_ft.size());
	}
	{
		std::list<std::string> lst_std(2, "test");
		ft::List<std::string> lst_ft(2, "test");

		std::cout << "----- CONSTRUCTOR (fill) -----" << std::endl;
		std::cout << "std:"; print_container(lst_std);
		std::cout << " ft:"; print_container(lst_ft);

		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
		EXPECT_EQ(lst_std.size(), lst_ft.size());
	}
}

TEST_F(Test_List, Constructor_copy) {
	std::list<int>	lst_std_copy(*list_int_unsort_std);
	ft::List<int>	lst_ft_copy(*list_int_unsort_ft);

	std::cout << "----- CONSTRUCTOR (copy) -----" << std::endl;
	std::cout << "std:"; print_container(*list_int_unsort_std);
	std::cout << " ft:"; print_container(*list_int_unsort_ft);
	std::cout << "std_copy:"; print_container(lst_std_copy);
	std::cout << " ft_copy:"; print_container(lst_ft_copy);
	EXPECT_EQ(*lst_std_copy.begin(), *lst_ft_copy.begin());
	EXPECT_EQ(*(--lst_std_copy.end()), *(--lst_ft_copy.end()));
	EXPECT_EQ(list_int_unsort_std->size(), lst_std_copy.size());
	EXPECT_EQ(list_int_unsort_ft->size(), lst_ft_copy.size());
}

TEST_F(Test_List, Constructor_range) {
	std::list<int>	lst_std_copy(++(*list_int_sort_std).begin(),
			--(*list_int_sort_std).end());
	ft::List<int>	lst_ft_copy(++(*list_int_sort_ft).begin(),
			--(*list_int_sort_ft).end());

	std::cout << "----- CONSTRUCTOR (range) -----" << std::endl;
	std::cout << "std:"; print_container(*list_int_sort_std);
	std::cout << " ft:"; print_container(*list_int_sort_ft);
	std::cout << "std ranged:"; print_container(lst_std_copy);
	std::cout << " ft ranged:"; print_container(lst_ft_copy);
	EXPECT_EQ(*lst_std_copy.begin(), *lst_ft_copy.begin());
	EXPECT_EQ(*(--lst_std_copy.end()), *(--lst_ft_copy.end()));
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
	EXPECT_EQ(lst_std_copy.size(), lst_ft_copy.size());
}

TEST_F(Test_List, Destructor) {
	std::list<int>	* lst_std = new std::list<int>(5, 5);
	ft::List<int>	* lst_ft = new ft::List<int>(5, 5);

	std::cout << "----- DESTRUCTOR -----" << std::endl;
	delete(lst_std);
	delete(lst_ft);
}

TEST_F(Test_List, Operator_assign) {
	std::list<int>	lst_std_copy;
	ft::List<int>	lst_ft_copy;

	lst_std_copy = *list_int_sort_std;
	lst_ft_copy = *list_int_sort_ft;

	std::cout << "----- OPERATOR =  -----" << std::endl;
	std::cout << "std:"; print_container(*list_int_sort_std);
	std::cout << " ft:"; print_container(*list_int_sort_ft);
	std::cout << "std_copy:"; print_container(lst_std_copy);
	std::cout << " ft_copy:"; print_container(lst_ft_copy);
	EXPECT_EQ(*lst_std_copy.begin(), *lst_ft_copy.begin());
	EXPECT_EQ(*(--lst_std_copy.end()), *(--lst_ft_copy.end()));
	EXPECT_EQ(list_int_sort_std->size(), lst_std_copy.size());
	EXPECT_EQ(list_int_sort_ft->size(), lst_ft_copy.size());
}

TEST_F(Test_List, Iterators_begin) {
	std::cout << "----- ITERATOR BEGIN -----" << std::endl;
	std::cout << "std:"; print_container(*list_int_sort_std);
	std::cout << " ft:"; print_container(*list_int_sort_ft);
	std::cout << "std   begin: " << *list_int_sort_std->begin() << std::endl;
	std::cout << "std ++begin: " << *(++list_int_sort_std->begin())
		<< std::endl;
	std::cout << " ft   begin: " << *list_int_sort_ft->begin() << std::endl;
	std::cout << " ft ++begin: " << *(++list_int_sort_ft->begin()) << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(*(++list_int_sort_std->begin()), *(++list_int_sort_ft->begin()));
}

TEST_F(Test_List, Iterators_end) {
	std::cout << "----- ITERATOR END -----" << std::endl;
	std::cout << "std:"; print_container(*list_int_sort_std);
	std::cout << " ft:"; print_container(*list_int_sort_ft);
	std::list<int>::iterator it_std = --list_int_sort_std->end();

	std::cout << "std    --end:  " << *it_std << std::endl;
	std::cout << "std --(--end): " << *(--it_std) << std::endl;

	ft::List<int>::iterator it_ft = --list_int_sort_ft->end();
	std::cout << " ft    --end:  " << *it_ft << std::endl;
	std::cout << " ft --(--end): " << *(--it_ft) << std::endl;

	EXPECT_EQ(*(--list_int_sort_std->end()), *(--list_int_sort_ft->end()));
	EXPECT_EQ(*(--it_std), *(--it_ft));
}

TEST_F(Test_List, Iterators_rbegin) {
	std::cout << "----- ITERATOR RBEGIN -----" << std::endl;
	std::cout << "std:"; print_container(*list_int_sort_std);
	std::cout << " ft:"; print_container(*list_int_sort_ft);
	std::cout << "std   rbegin: " << *list_int_sort_std->rbegin() << std::endl;
	std::cout << "std ++rbegin: " << *(++list_int_sort_std->rbegin())
		<< std::endl;
	std::cout << " ft   rbegin: " << *list_int_sort_ft->rbegin() << std::endl;
	std::cout << " ft ++rbegin: " << *(++list_int_sort_ft->rbegin())
		<< std::endl;
	EXPECT_EQ(*list_int_sort_std->rbegin(), *list_int_sort_ft->rbegin());
	EXPECT_EQ(*(++list_int_sort_std->rbegin()),
			*(++list_int_sort_ft->rbegin()));
}

TEST_F(Test_List, Iterators_rend) {
	std::cout << "----- ITERATOR REND -----" << std::endl;
	std::cout << "std:"; print_container(*list_int_sort_std);
	std::cout << " ft:"; print_container(*list_int_sort_ft);
	std::list<int>::reverse_iterator it_std = --list_int_sort_std->rend();

	std::cout << "std    --rend:  " << *it_std << std::endl;
	std::cout << "std --(--rend): " << *(--it_std) << std::endl;

	ft::List<int>::reverse_iterator it_ft = --list_int_sort_ft->rend();
	std::cout << " ft    --rend:  " << *it_ft << std::endl;
	std::cout << " ft --(--rend): " << *(--it_ft) << std::endl;

	EXPECT_EQ(*(--list_int_sort_std->rend()), *(--list_int_sort_ft->rend()));
	EXPECT_EQ(*(--it_std), *(--it_ft));
}

TEST_F(Test_List, Modifiers_clear) {
	std::cout << "----- CLEAR -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_sort_std);
	std::cout << " ft before:"; print_container(*list_int_sort_ft);
	std::cout << "std size before: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size before: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());

	list_int_sort_std->clear();
	list_int_sort_ft->clear();

	std::cout << std::endl;
	std::cout << "std after:"; print_container(*list_int_sort_std);
	std::cout << " ft after:"; print_container(*list_int_sort_ft);
	std::cout << "std size after: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size after: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_erase_position) {
	std::cout << "----- ERASE (position) -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_sort_std);
	std::cout << " ft before:"; print_container(*list_int_sort_ft);
	std::cout << "std size before: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size before: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());

	list_int_sort_std->erase(list_int_sort_std->begin());
	list_int_sort_ft->erase(list_int_sort_ft->begin());

	std::cout << std::endl;
	std::cout << "Erase begin() element" << std::endl;
	std::cout << "std after:"; print_container(*list_int_sort_std);
	std::cout << " ft after:"; print_container(*list_int_sort_ft);
	std::cout << "std size after: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size after: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_erase_range) {
	std::cout << "----- ERASE (position) -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_sort_std);
	std::cout << " ft before:"; print_container(*list_int_sort_ft);
	std::cout << "std size before: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size before: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());

	list_int_sort_std->erase(++list_int_sort_std->begin(),
			--list_int_sort_std->end());
	list_int_sort_ft->erase(++list_int_sort_ft->begin(),
			--list_int_sort_ft->end());

	std::cout << std::endl;
	std::cout << "Erase range [++begin(), --end())" << std::endl;
	std::cout << "std after:"; print_container(*list_int_sort_std);
	std::cout << " ft after:"; print_container(*list_int_sort_ft);
	std::cout << "std size after: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size after: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_pop_front) {
	std::cout << "----- POP_FRONT -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_sort_std);
	std::cout << " ft before:"; print_container(*list_int_sort_ft);
	std::cout << "std size before: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size before: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());

	list_int_sort_std->pop_front();
	list_int_sort_ft->pop_front();

	std::cout << std::endl;
	std::cout << "std after:"; print_container(*list_int_sort_std);
	std::cout << " ft after:"; print_container(*list_int_sort_ft);
	std::cout << "std size after: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size after: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_pop_back) {
	std::cout << "----- POP_BACK -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_sort_std);
	std::cout << " ft before:"; print_container(*list_int_sort_ft);
	std::cout << "std size before: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size before: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());

	list_int_sort_std->pop_back();
	list_int_sort_ft->pop_back();

	std::cout << std::endl;
	std::cout << "std after:"; print_container(*list_int_sort_std);
	std::cout << " ft after:"; print_container(*list_int_sort_ft);
	std::cout << "std size after: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size after: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*(--list_int_sort_std->end()), *(--list_int_sort_ft->end()));
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_element_access_front) {
	std::cout << "----- FRONT -----" << std::endl;
	std::cout << "std:"; print_container(*list_int_unsort_std);
	std::cout << " ft:"; print_container(*list_int_unsort_ft);
	std::cout << "std front: " << list_int_unsort_std->front() << std::endl;
	std::cout << " ft front: " << list_int_unsort_ft->front() << std::endl;
	EXPECT_EQ(list_int_unsort_std->front(), list_int_unsort_ft->front());

	std::cout << "Modify data in element by increment reference" << std::endl;
	++list_int_unsort_std->front();
	++list_int_unsort_ft->front();
	std::cout << "std:"; print_container(*list_int_unsort_std);
	std::cout << " ft:"; print_container(*list_int_unsort_ft);
	EXPECT_EQ(list_int_unsort_std->front(), list_int_unsort_ft->front());
}

TEST_F(Test_List, Modifiers_element_access_back) {
	std::cout << "----- BACK -----" << std::endl;
	std::cout << "std:"; print_container(*list_int_unsort_std);
	std::cout << " ft:"; print_container(*list_int_unsort_ft);
	std::cout << "std back: " << list_int_unsort_std->back() << std::endl;
	std::cout << " ft back: " << list_int_unsort_ft->back() << std::endl;
	EXPECT_EQ(list_int_unsort_std->back(), list_int_unsort_ft->back());

	std::cout << std::endl;
	std::cout << "Modify data in element by increment reference" << std::endl;
	++list_int_unsort_std->back();
	++list_int_unsort_ft->back();
	std::cout << "std:"; print_container(*list_int_unsort_std);
	std::cout << " ft:"; print_container(*list_int_unsort_ft);
	EXPECT_EQ(list_int_unsort_std->back(), list_int_unsort_ft->back());
}

TEST_F(Test_List, Modifiers_assign_range) {
	std::cout << "----- ASSIGN (range) -----" << std::endl;
	std::cout << "std original:"; print_container(*list_int_sort_std);
	std::cout << " ft original:"; print_container(*list_int_sort_ft);

	std::list<int>	lst_std_second;
	ft::List<int>	lst_ft_second;

	std::cout << std::endl;
	std::cout << "std_second size before: " << lst_std_second.size()
		<< std::endl;
	std::cout << " ft_second size before: " << lst_ft_second.size()
		<< std::endl;
	std::cout << std::endl;
	std::cout << "Assign by range [++begin(), --end()) from original"
		<< std::endl;

	lst_std_second.assign(++list_int_sort_std->begin(),
												--list_int_sort_std->end());
	lst_ft_second.assign(++list_int_sort_ft->begin(),
												--list_int_sort_ft->end());

	std::cout << "std assigned:"; print_container(lst_std_second);
	std::cout << " ft assigned:"; print_container(lst_ft_second);
	std::cout << "std_second size after: " << lst_std_second.size()
		<< std::endl;
	std::cout << " ft_second size after: " << lst_ft_second.size()
		<< std::endl;

	EXPECT_EQ(*lst_std_second.begin(), *lst_ft_second.begin());
	EXPECT_EQ(lst_std_second.size(), lst_ft_second.size());
}

TEST_F(Test_List, Modifiers_assign_fill) {
	std::cout << "----- ASSIGN (fill) -----" << std::endl;
	std::list<int>	lst_std;
	ft::List<int>	lst_ft;
	std::cout << "std size before: " << lst_std.size() << std::endl;
	std::cout << " ft size before: " << lst_ft.size() << std::endl;

	std::cout << std::endl;
	std::cout << "Assign fill" << std::endl;

	lst_std.assign(5, 7);
	lst_ft.assign(5, 7);

	std::cout << "std assigned:"; print_container(lst_std);
	std::cout << " ft assigned:"; print_container(lst_ft);
	std::cout << "std size after: " << lst_std.size() << std::endl;
	std::cout << " ft size after: " << lst_ft.size() << std::endl;

	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

TEST_F(Test_List, Modifiers_insert_single_element) {
	std::cout << "----- INSERT (single element) -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_sort_std);
	std::cout << " ft before:"; print_container(*list_int_sort_ft);
	std::cout << "std size before: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size before: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Insert '8' before ++begin() element" << std::endl;

	list_int_sort_std->insert(++list_int_sort_std->begin(), 8);
	list_int_sort_ft->insert(++list_int_sort_ft->begin(), 8);

	std::cout << "std after:"; print_container(*list_int_sort_std);
	std::cout << " ft after:"; print_container(*list_int_sort_ft);
	std::cout << "std size after: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size after: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_insert_fill) {
	std::cout << "----- INSERT (fill) -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_sort_std);
	std::cout << " ft before:"; print_container(*list_int_sort_ft);
	std::cout << "std size before: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size before: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Insert '8' 5 times before ++begin() element" << std::endl;

	list_int_sort_std->insert(++list_int_sort_std->begin(), 5, 8);
	list_int_sort_ft->insert(++list_int_sort_ft->begin(), 5, 8);

	std::cout << "std after:"; print_container(*list_int_sort_std);
	std::cout << " ft after:"; print_container(*list_int_sort_ft);
	std::cout << "std size after: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size after: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_insert_range) {
	std::cout << "----- INSERT (fill) -----" << std::endl;
	std::cout << "std_first before:"; print_container(*list_int_sort_std);
	std::cout << " ft_first before:"; print_container(*list_int_sort_ft);
	std::cout << "std_first size before: " << list_int_sort_std->size()
		<< std::endl;
	std::cout << " ft_first size before: " << list_int_sort_ft->size()
		<< std::endl;
	std::cout << std::endl;
	std::cout << "std_second:"; print_container(*list_int_unsort_std);
	std::cout << " ft_second:"; print_container(*list_int_unsort_ft);
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Insert to first before ++begin() element "
		<< "from second range [++begin(), --end())" << std::endl;

	list_int_sort_std->insert(++list_int_sort_std->begin(),
				++list_int_unsort_std->begin(), --list_int_unsort_std->end());
	list_int_sort_ft->insert(++list_int_sort_ft->begin(),
				++list_int_unsort_ft->begin(), --list_int_unsort_ft->end());

	std::cout << "std_first after:"; print_container(*list_int_sort_std);
	std::cout << " ft_first after:"; print_container(*list_int_sort_ft);
	std::cout << "std_first size after: " << list_int_sort_std->size()
		<< std::endl;
	std::cout << " ft_first size after: " << list_int_sort_ft->size()
		<< std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_swap) {
	std::cout << "----- SWAP -----" << std::endl;
	std::cout << "std_first before:"; print_container(*list_int_sort_std);
	std::cout << " ft_first before:"; print_container(*list_int_sort_ft);
	std::cout << std::endl;
	std::cout << "std_second before:"; print_container(*list_int_unsort_std);
	std::cout << " ft_second before:"; print_container(*list_int_unsort_ft);

	std::list<int>::iterator it_std_first = ++list_int_sort_std->begin();
	std::list<int>::iterator it_std_second = ++list_int_unsort_std->begin();
	ft::List<int>::iterator it_ft_first = ++list_int_sort_ft->begin();
	ft::List<int>::iterator it_ft_second = ++list_int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(*list_int_unsort_std->begin(), *list_int_unsort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
	EXPECT_EQ(list_int_unsort_std->size(), list_int_unsort_ft->size());

	std::cout << std::endl;
	std::cout << "Swap first and second objects" << std::endl;

	list_int_sort_std->swap(*list_int_unsort_std);
	list_int_sort_ft->swap(*list_int_unsort_ft);

	std::cout << "std_first after:"; print_container(*list_int_sort_std);
	std::cout << " ft_first after:"; print_container(*list_int_sort_ft);
	std::cout << std::endl;
	std::cout << "std_second after:"; print_container(*list_int_unsort_std);
	std::cout << " ft_second after:"; print_container(*list_int_unsort_ft);
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(*list_int_unsort_std->begin(), *list_int_unsort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
	EXPECT_EQ(list_int_unsort_std->size(), list_int_unsort_ft->size());
}

TEST_F(Test_List, Modifiers_resize_reduce) {
	std::cout << "----- RESIZE (reduce) -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_sort_std);
	std::cout << " ft before:"; print_container(*list_int_sort_ft);
	std::cout << "std size before: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size before: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Downsize to 2" << std::endl;
	list_int_sort_std->resize(2);
	list_int_sort_ft->resize(2);

	std::cout << "std after:"; print_container(*list_int_sort_std);
	std::cout << " ft after:"; print_container(*list_int_sort_ft);
	std::cout << "std size after: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size after: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_resize_incrase_default) {
	std::cout << "----- RESIZE (incrase default) -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_sort_std);
	std::cout << " ft before:"; print_container(*list_int_sort_ft);
	std::cout << "std size before: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size before: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Upsize to 8 with default type value for new elements"
		<< std::endl;
	list_int_sort_std->resize(8);
	list_int_sort_ft->resize(8);

	std::cout << "std after:"; print_container(*list_int_sort_std);
	std::cout << " ft after:"; print_container(*list_int_sort_ft);
	std::cout << "std size after: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size after: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

TEST_F(Test_List, Modifiers_resize_incrase_fill) {
	std::cout << "----- RESIZE (incrase fill) -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_sort_std);
	std::cout << " ft before:"; print_container(*list_int_sort_ft);
	std::cout << "std size before: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size before: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Upsize to 8 with '7' value for new elements" << std::endl;
	list_int_sort_std->resize(8, 7);
	list_int_sort_ft->resize(8, 7);

	std::cout << "std after:";
	print_container(*list_int_sort_std);
	std::cout << " ft after:";
	print_container(*list_int_sort_ft);
	std::cout << "std size after: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size after: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

TEST_F(Test_List, Operations_splice_entire_list) {
	std::cout << "----- SPLICE (entire list) -----" << std::endl;
	std::cout << "std_first before:"; print_container(*list_int_sort_std);
	std::cout << " ft_first before:"; print_container(*list_int_sort_ft);
	std::cout << "std_first size before: " << list_int_sort_std->size()
		<< std::endl;
	std::cout << " ft_first size before: " << list_int_sort_ft->size()
		<< std::endl;
	std::cout << std::endl;
	std::cout << "std_second before:"; print_container(*list_int_unsort_std);
	std::cout << " ft_second before:"; print_container(*list_int_unsort_ft);
	std::cout << "std_second size before: " << list_int_unsort_std->size()
		<< std::endl;
	std::cout << " ft_second size before: " << list_int_unsort_ft->size()
		<< std::endl;

	std::list<int>::iterator it_std_first = ++list_int_sort_std->begin();
	std::list<int>::iterator it_std_second = ++list_int_unsort_std->begin();
	ft::List<int>::iterator it_ft_first = ++list_int_sort_ft->begin();
	ft::List<int>::iterator it_ft_second = ++list_int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(*list_int_unsort_std->begin(), *list_int_unsort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
	EXPECT_EQ(list_int_unsort_std->size(), list_int_unsort_ft->size());

	std::cout << std::endl;
	std::cout << "Splice second object into first before ++begin()"
		<< std::endl;

	list_int_sort_std->splice(++list_int_sort_std->begin(),
			*list_int_unsort_std);
	list_int_sort_ft->splice(++list_int_sort_ft->begin(), *list_int_unsort_ft);

	std::cout << "std_first after:"; print_container(*list_int_sort_std);
	std::cout << " ft_first after:"; print_container(*list_int_sort_ft);
	std::cout << "std_first size after: " << list_int_sort_std->size()
		<< std::endl;
	std::cout << " ft_first size after: " << list_int_sort_ft->size()
		<< std::endl;
	std::cout << std::endl;
	std::cout << "std_second after:"; print_container(*list_int_unsort_std);
	std::cout << " ft_second after:"; print_container(*list_int_unsort_ft);
	std::cout << "std_second size after: " << list_int_unsort_std->size()
		<< std::endl;
	std::cout << " ft_second size after: " << list_int_unsort_ft->size()
		<< std::endl;
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(*list_int_unsort_std->begin(), *list_int_unsort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
	EXPECT_EQ(list_int_unsort_std->size(), list_int_unsort_ft->size());
}

TEST_F(Test_List, Operations_splice_single_element) {
	std::cout << "std_first before:"; print_container(*list_int_sort_std);
	std::cout << " ft_first before:"; print_container(*list_int_sort_ft);
	std::cout << "std_first size before: " << list_int_sort_std->size()
		<< std::endl;
	std::cout << " ft_first size before: " << list_int_sort_ft->size()
		<< std::endl;
	std::cout << std::endl;
	std::cout << "std_second before:"; print_container(*list_int_unsort_std);
	std::cout << " ft_second before:"; print_container(*list_int_unsort_ft);
	std::cout << "std_second size before: " << list_int_unsort_std->size()
		<< std::endl;
	std::cout << " ft_second size before: " << list_int_unsort_ft->size()
		<< std::endl;

	std::list<int>::iterator it_std_first = ++list_int_sort_std->begin();
	std::list<int>::iterator it_std_second = ++list_int_unsort_std->begin();
	ft::List<int>::iterator it_ft_first = ++list_int_sort_ft->begin();
	ft::List<int>::iterator it_ft_second = ++list_int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(*list_int_unsort_std->begin(), *list_int_unsort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
	EXPECT_EQ(list_int_unsort_std->size(), list_int_unsort_ft->size());

	std::cout << std::endl;
	std::cout << "Splice single element ++begin() from second object "
		<< "into first before ++begin()" << std::endl;

	list_int_sort_std->splice(++list_int_sort_std->begin(),
			*list_int_unsort_std, ++list_int_unsort_std->begin());
	list_int_sort_ft->splice(++list_int_sort_ft->begin(),
				*list_int_unsort_ft, ++list_int_unsort_ft->begin());

	std::cout << "std_first after:"; print_container(*list_int_sort_std);
	std::cout << " ft_first after:"; print_container(*list_int_sort_ft);
	std::cout << "std_first size after: " << list_int_sort_std->size()
		<< std::endl;
	std::cout << " ft_first size after: " << list_int_sort_ft->size()
		<< std::endl;
	std::cout << std::endl;
	std::cout << "std_second after:"; print_container(*list_int_unsort_std);
	std::cout << " ft_second after:"; print_container(*list_int_unsort_ft);
	std::cout << "std_second size after: " << list_int_unsort_std->size()
		<< std::endl;
	std::cout << " ft_second size after: " << list_int_unsort_ft->size()
		<< std::endl;
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(*list_int_unsort_std->begin(), *list_int_unsort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
	EXPECT_EQ(list_int_unsort_std->size(), list_int_unsort_ft->size());
}

TEST_F(Test_List, Operations_splice_range) {
	std::cout << "----- SPLICE (range) -----" << std::endl;
	std::cout << "std_first before:"; print_container(*list_int_sort_std);
	std::cout << " ft_first before:"; print_container(*list_int_sort_ft);
	std::cout << "std_first size before: " << list_int_sort_std->size()
		<< std::endl;
	std::cout << " ft_first size before: " << list_int_sort_ft->size()
		<< std::endl;
	std::cout << std::endl;
	std::cout << "std_second before:"; print_container(*list_int_unsort_std);
	std::cout << " ft_second before:"; print_container(*list_int_unsort_ft);
	std::cout << "std_second size before: " << list_int_unsort_std->size()
		<< std::endl;
	std::cout << " ft_second size before: " << list_int_unsort_ft->size()
		<< std::endl;

	std::list<int>::iterator it_std_first = ++list_int_sort_std->begin();
	std::list<int>::iterator it_std_second = ++list_int_unsort_std->begin();
	ft::List<int>::iterator it_ft_first = ++list_int_sort_ft->begin();
	ft::List<int>::iterator it_ft_second = ++list_int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(*list_int_unsort_std->begin(), *list_int_unsort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
	EXPECT_EQ(list_int_unsort_std->size(), list_int_unsort_ft->size());

	std::cout << std::endl;
	std::cout << "Splice range [++begin(), --end()) from second object "
		<< "into first before ++begin()" << std::endl;

	list_int_sort_std->splice(++list_int_sort_std->begin(),
			*list_int_unsort_std, ++list_int_unsort_std->begin(),
			--list_int_unsort_std->end());
	list_int_sort_ft->splice(++list_int_sort_ft->begin(),
			*list_int_unsort_ft, ++list_int_unsort_ft->begin(),
			--list_int_unsort_ft->end());

	std::cout << "std_first after:"; print_container(*list_int_sort_std);
	std::cout << " ft_first after:"; print_container(*list_int_sort_ft);
	std::cout << "std_first size after: " << list_int_sort_std->size()
		<< std::endl;
	std::cout << " ft_first size after: " << list_int_sort_ft->size()
		<< std::endl;
	std::cout << std::endl;
	std::cout << "std_second after:"; print_container(*list_int_unsort_std);
	std::cout << " ft_second after:"; print_container(*list_int_unsort_ft);
	std::cout << "std_second size after: " << list_int_unsort_std->size()
		<< std::endl;
	std::cout << " ft_second size after: " << list_int_unsort_ft->size()
		<< std::endl;
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(*list_int_unsort_std->begin(), *list_int_unsort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
	EXPECT_EQ(list_int_unsort_std->size(), list_int_unsort_ft->size());
}

TEST_F(Test_List, Operations_remove) {
	std::cout << "----- REMOVE -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_sort_std);
	std::cout << " ft before:"; print_container(*list_int_sort_ft);
	std::cout << "std size before: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size before: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Remove elements with values 1 and 4" << std::endl;
	list_int_sort_std->remove(1);
	list_int_sort_std->remove(4);
	list_int_sort_ft->remove(1);
	list_int_sort_ft->remove(4);

	std::cout << "std after:";
	print_container(*list_int_sort_std);
	std::cout << " ft after:";
	print_container(*list_int_sort_ft);
	std::cout << "std size after: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size after: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

bool	is_odd(const int& val) {
	return (val % 2) == 1;
}

TEST_F(Test_List, Operations_remove_if) {
	std::cout << "----- REMOVE_IF -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_sort_std);
	std::cout << " ft before:"; print_container(*list_int_sort_ft);
	std::cout << "std size before: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size before: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());

	std::cout << std::endl;
	std::cout << "Remove odd elements" << std::endl;
	list_int_sort_std->remove_if(is_odd);
	list_int_sort_ft->remove_if(is_odd);

	std::cout << "std after:";
	print_container(*list_int_sort_std);
	std::cout << " ft after:";
	print_container(*list_int_sort_ft);
	std::cout << "std size after: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size after: " << list_int_sort_ft->size() << std::endl;
	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

TEST_F(Test_List, Operations_unique_no_args_sorted) {
	std::cout << "----- UNIQUE (no arguments sorted) -----" << std::endl;
	std::list<int>	lst_std;
	ft::List<int>	lst_ft;

	int int_array[] = { 1, 1, 2, 3, 3, 3, 4, 4, 5};
	for (int i = 0; i < 9; ++i) { lst_std.push_back(int_array[i]); }
	for (int i = 0; i < 9; ++i) { lst_ft.push_back(int_array[i]); }

	std::cout << "std before:"; print_container(lst_std);
	std::cout << " ft before:"; print_container(lst_ft);
	std::cout << "std size before: " << lst_std.size() << std::endl;
	std::cout << " ft size before: " << lst_ft.size() << std::endl;
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());

	std::cout << std::endl;
	std::cout << "Filter unique values" << std::endl;
	lst_std.unique();
	lst_ft.unique();

	std::cout << "std after:"; print_container(lst_std);
	std::cout << " ft after:"; print_container(lst_ft);
	std::cout << "std size after: " << lst_std.size() << std::endl;
	std::cout << " ft size after: " << lst_ft.size() << std::endl;
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

TEST_F(Test_List, Operations_unique_no_args_unsorted) {
	std::cout << "----- UNIQUE (no arguments unsorted) -----" << std::endl;
	std::list<int>	lst_std;
	ft::List<int>	lst_ft;

	int int_array[] = { 1, 2, 3, 3, 1, 3, 4, 4, 5 };
	for (int i = 0; i < 9; ++i) { lst_std.push_back(int_array[i]); }
	for (int i = 0; i < 9; ++i) { lst_ft.push_back(int_array[i]); }

	std::cout << "std before:"; print_container(lst_std);
	std::cout << " ft before:"; print_container(lst_ft);
	std::cout << "std size before: " << lst_std.size() << std::endl;
	std::cout << " ft size before: " << lst_ft.size() << std::endl;
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());

	std::cout << std::endl;
	std::cout << "Filter unique values" << std::endl;
	lst_std.unique();
	lst_ft.unique();

	std::cout << "std after:"; print_container(lst_std);
	std::cout << " ft after:"; print_container(lst_ft);
	std::cout << "std size after: " << lst_std.size() << std::endl;
	std::cout << " ft size after: " << lst_ft.size() << std::endl;
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

// a binary predicate implemented as a function:
bool	same_integral_part(double first, double second) {
	return ( int(first)==int(second) );
}

TEST_F(Test_List, Operations_unique_binary_pred) {
	std::cout << "----- UNIQUE (binary predicate) -----" << std::endl;
	std::list<double>	lst_std;
	ft::List<double>	lst_ft;

	double dbl_array[] = { 1.01, 1.05, 2.15, 2.25, 2.25, 3.40, 3.50, 4.70 };
	for (int i = 0; i < 8; ++i) { lst_std.push_back(dbl_array[i]); }
	for (int i = 0; i < 8; ++i) { lst_ft.push_back(dbl_array[i]); }

	std::cout << "std before:"; print_container(lst_std);
	std::cout << " ft before:"; print_container(lst_ft);
	std::cout << "std size before: " << lst_std.size() << std::endl;
	std::cout << " ft size before: " << lst_ft.size() << std::endl;
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());

	std::cout << std::endl;
	std::cout << "Filter values with same integral part" << std::endl;
	lst_std.unique(same_integral_part);
	lst_ft.unique(same_integral_part);

	std::cout << "std after:"; print_container(lst_std);
	std::cout << " ft after:"; print_container(lst_ft);
	std::cout << "std size after: " << lst_std.size() << std::endl;
	std::cout << " ft size after: " << lst_ft.size() << std::endl;
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

TEST_F(Test_List, Operations_merge_no_args_sort_small_in_big) {
	std::cout << "----- MERGE (no args sorted smaller into bigger) -----"
		<< std::endl;

	std::list<int>	lst_std_first;
	std::list<int>	lst_std_second;
	ft::List<int>	lst_ft_first;
	ft::List<int>	lst_ft_second;

	int int_array_first[] = { 1, 3, 4, 7, 9 };
	for (int i = 0; i < 5; ++i) { lst_std_first.push_back(int_array_first[i]); }
	for (int i = 0; i < 5; ++i) { lst_ft_first.push_back(int_array_first[i]); }

	int int_array_second[] = { 2, 5, 6, 8 };
	for (int i = 0; i < 4; ++i) {
		lst_std_second.push_back(int_array_second[i]);
	}
	for (int i = 0; i < 4; ++i) {
		lst_ft_second.push_back(int_array_second[i]);
	}

	std::cout << "std_first before:"; print_container(lst_std_first);
	std::cout << " ft_first before:"; print_container(lst_ft_first);
	std::cout << "std_first size before: " << lst_std_first.size() << std::endl;
	std::cout << " ft_first size before: " << lst_ft_first.size() << std::endl;
	std::cout << std::endl;
	std::cout << "std_second before:"; print_container(lst_std_second);
	std::cout << " ft_second before:"; print_container(lst_ft_second);
	std::cout << "std_second size before: " << lst_std_second.size()
		<< std::endl;
	std::cout << " ft_second size before: " << lst_ft_second.size()
		<< std::endl;

	std::list<int>::iterator it_std_first = ++lst_std_first.begin();
	std::list<int>::iterator it_std_second = ++lst_std_second.begin();
	ft::List<int>::iterator it_ft_first = ++lst_ft_first.begin();
	ft::List<int>::iterator it_ft_second = ++lst_ft_second.begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

	EXPECT_EQ(*lst_std_first.begin(), *lst_ft_first.begin());
	EXPECT_EQ(*lst_std_second.begin(), *lst_ft_second.begin());
	EXPECT_EQ(lst_std_first.size(), lst_ft_first.size());
	EXPECT_EQ(lst_std_second.size(), lst_ft_second.size());

	std::cout << std::endl;
	std::cout << "Merge second object into first" << std::endl;

	lst_std_first.merge(lst_std_second);
	lst_ft_first.merge(lst_ft_second);

	std::cout << "std_first after:"; print_container(lst_std_first);
	std::cout << " ft_first after:"; print_container(lst_ft_first);
	std::cout << "std_first size after: " << lst_std_first.size() << std::endl;
	std::cout << " ft_first size after: " << lst_ft_first.size() << std::endl;
	std::cout << std::endl;
	std::cout << "std_second after:"; print_container(lst_std_second);
	std::cout << " ft_second after:"; print_container(lst_ft_second);
	std::cout << "std_second size after: " << lst_std_second.size()
		<< std::endl;
	std::cout << " ft_second size after: " << lst_ft_second.size() << std::endl;
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*lst_std_first.begin(), *lst_ft_first.begin());
	EXPECT_EQ(*lst_std_second.begin(), *lst_ft_second.begin());
	EXPECT_EQ(lst_std_first.size(), lst_ft_first.size());
	EXPECT_EQ(lst_std_second.size(), lst_ft_second.size());
}

TEST_F(Test_List, Operations_merge_no_args_unsort_big_in_small) {
	std::cout << "----- MERGE (no args unsorted bigger into smaller) -----"
		<< std::endl;

	std::list<int>	lst_std_first;
	std::list<int>	lst_std_second;
	ft::List<int>	lst_ft_first;
	ft::List<int>	lst_ft_second;

	int int_array_first[] = { 1, 4, 3 };
	for (int i = 0; i < 3; ++i) { lst_std_first.push_back(int_array_first[i]); }
	for (int i = 0; i < 3; ++i) { lst_ft_first.push_back(int_array_first[i]); }

	int int_array_second[] = { 2, 9, 5, 7, 6, 8 };
	for (int i = 0; i < 6; ++i) {
		lst_std_second.push_back(int_array_second[i]);
	}
	for (int i = 0; i < 6; ++i) {
		lst_ft_second.push_back(int_array_second[i]);
	}

	std::cout << "std_first before:"; print_container(lst_std_first);
	std::cout << " ft_first before:"; print_container(lst_ft_first);
	std::cout << "std_first size before: " << lst_std_first.size() << std::endl;
	std::cout << " ft_first size before: " << lst_ft_first.size() << std::endl;
	std::cout << std::endl;
	std::cout << "std_second before:"; print_container(lst_std_second);
	std::cout << " ft_second before:"; print_container(lst_ft_second);
	std::cout << "std_second size before: " << lst_std_second.size()
		<< std::endl;
	std::cout << " ft_second size before: " << lst_ft_second.size()
		<< std::endl;

	std::list<int>::iterator it_std_first = ++lst_std_first.begin();
	std::list<int>::iterator it_std_second = ++lst_std_second.begin();
	ft::List<int>::iterator it_ft_first = ++lst_ft_first.begin();
	ft::List<int>::iterator it_ft_second = ++lst_ft_second.begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

	EXPECT_EQ(*lst_std_first.begin(), *lst_ft_first.begin());
	EXPECT_EQ(*lst_std_second.begin(), *lst_ft_second.begin());
	EXPECT_EQ(lst_std_first.size(), lst_ft_first.size());
	EXPECT_EQ(lst_std_second.size(), lst_ft_second.size());

	std::cout << std::endl;
	std::cout << "Merge second object into first" << std::endl;

	lst_std_first.merge(lst_std_second);
	lst_ft_first.merge(lst_ft_second);

	std::cout << "std_first after:"; print_container(lst_std_first);
	std::cout << " ft_first after:"; print_container(lst_ft_first);
	std::cout << "std_first size after: " << lst_std_first.size() << std::endl;
	std::cout << " ft_first size after: " << lst_ft_first.size() << std::endl;
	std::cout << std::endl;
	std::cout << "std_second after:"; print_container(lst_std_second);
	std::cout << " ft_second after:"; print_container(lst_ft_second);
	std::cout << "std_second size after: " << lst_std_second.size()
		<< std::endl;
	std::cout << " ft_second size after: " << lst_ft_second.size() << std::endl;
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*lst_std_first.begin(), *lst_ft_first.begin());
	EXPECT_EQ(*lst_std_second.begin(), *lst_ft_second.begin());
	EXPECT_EQ(lst_std_first.size(), lst_ft_first.size());
	EXPECT_EQ(lst_std_second.size(), lst_ft_second.size());
}

// compare only integral part:
bool	mycomparison(double first, double second) {
	return ( int(first)<int(second) );
}

TEST_F(Test_List, Operations_merge_compare) {
	std::cout << "----- MERGE (compare) -----" << std::endl;

	std::list<double>	lst_std_first;
	std::list<double>	lst_std_second;
	ft::List<double>	lst_ft_first;
	ft::List<double>	lst_ft_second;

	double dbl_array_first[] = { 1.01, 1.05, 2.15, 3.75 };
	for (int i = 0; i < 4; ++i) { lst_std_first.push_back(dbl_array_first[i]); }
	for (int i = 0; i < 4; ++i) { lst_ft_first.push_back(dbl_array_first[i]); }

	double dbl_array_second[] = { 2.25, 3.40, 3.50, 4.70 };
	for (int i = 0; i < 4; ++i) {
		lst_std_second.push_back(dbl_array_second[i]);
	}
	for (int i = 0; i < 4; ++i) {
		lst_ft_second.push_back(dbl_array_second[i]);
	}

	std::cout << "std_first before:"; print_container(lst_std_first);
	std::cout << " ft_first before:"; print_container(lst_ft_first);
	std::cout << "std_first size before: " << lst_std_first.size() << std::endl;
	std::cout << " ft_first size before: " << lst_ft_first.size() << std::endl;
	std::cout << std::endl;
	std::cout << "std_second before:"; print_container(lst_std_second);
	std::cout << " ft_second before:"; print_container(lst_ft_second);
	std::cout << "std_second size before: " << lst_std_second.size()
		<< std::endl;
	std::cout << " ft_second size before: " << lst_ft_second.size()
		<< std::endl;

	std::list<double>::iterator it_std_first = ++lst_std_first.begin();
	std::list<double>::iterator it_std_second = ++lst_std_second.begin();
	ft::List<double>::iterator it_ft_first = ++lst_ft_first.begin();
	ft::List<double>::iterator it_ft_second = ++lst_ft_second.begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

	EXPECT_EQ(*lst_std_first.begin(), *lst_ft_first.begin());
	EXPECT_EQ(*lst_std_second.begin(), *lst_ft_second.begin());
	EXPECT_EQ(lst_std_first.size(), lst_ft_first.size());
	EXPECT_EQ(lst_std_second.size(), lst_ft_second.size());

	std::cout << std::endl;
	std::cout
		<< "Merge second object into first with comparing elements by function"
		<< std::endl;

	lst_std_first.merge(lst_std_second, mycomparison);
	lst_ft_first.merge(lst_ft_second, mycomparison);

	std::cout << "std_first after:"; print_container(lst_std_first);
	std::cout << " ft_first after:"; print_container(lst_ft_first);
	std::cout << "std_first size after: " << lst_std_first.size() << std::endl;
	std::cout << " ft_first size after: " << lst_ft_first.size() << std::endl;
	std::cout << std::endl;
	std::cout << "std_second after:"; print_container(lst_std_second);
	std::cout << " ft_second after:"; print_container(lst_ft_second);
	std::cout << "std_second size after: " << lst_std_second.size()
		<< std::endl;
	std::cout << " ft_second size after: " << lst_ft_second.size() << std::endl;
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*lst_std_first.begin(), *lst_ft_first.begin());
	EXPECT_EQ(*lst_std_second.begin(), *lst_ft_second.begin());
	EXPECT_EQ(lst_std_first.size(), lst_ft_first.size());
	EXPECT_EQ(lst_std_second.size(), lst_ft_second.size());
}

TEST_F(Test_List, Operations_sort_no_args) {
	std::cout << "----- SORT (no args) -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_unsort_std);
	std::cout << " ft before:"; print_container(*list_int_unsort_ft);

	EXPECT_EQ(*list_int_unsort_std->begin(), *list_int_unsort_ft->begin());
	EXPECT_EQ(*(--list_int_unsort_std->end()), *(--list_int_unsort_ft->end()));

	std::cout << std::endl;
	std::cout << "Sort without arguments" << std::endl;
	list_int_unsort_std->sort();
	list_int_unsort_ft->sort();

	std::cout << "std after:"; print_container(*list_int_unsort_std);
	std::cout << " ft after:"; print_container(*list_int_unsort_ft);
	EXPECT_EQ(*list_int_unsort_std->begin(), *list_int_unsort_ft->begin());
	EXPECT_EQ(*(--list_int_unsort_std->end()), *(--list_int_unsort_ft->end()));
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
	std::list<std::string>	lst_std;
	lst_std.push_back ("one");
	lst_std.push_back ("two");
	lst_std.push_back ("Three");
	std::list<std::string>::iterator it_std = ++lst_std.begin();

	ft::List<std::string>	lst_ft;
	lst_ft.push_back ("one");
	lst_ft.push_back ("two");
	lst_ft.push_back ("Three");
	ft::List<std::string>::iterator it_ft = ++lst_ft.begin();

	std::cout << "std before:"; print_container(lst_std);
	std::cout << " ft before:"; print_container(lst_ft);
	std::cout << "it_std before: " << *it_std << std::endl;
	std::cout << "it_ft  before: " << *it_ft << std::endl;

	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(*(--lst_std.end()), *(--lst_ft.end()));

	std::cout << std::endl;
	std::cout << "Sort with function compare_nocase" << std::endl;
	lst_std.sort(compare_nocase);
	lst_ft.sort(compare_nocase);

	std::cout << "std after:"; print_container(lst_std);
	std::cout << " ft after:"; print_container(lst_ft);
	std::cout << "it_std after: " << *it_std << std::endl;
	std::cout << "it_ft  after: " << *it_ft << std::endl;

	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(*(--lst_std.end()), *(--lst_ft.end()));
}

TEST_F(Test_List, Operations_reverse) {
	std::cout << "----- Reverse -----" << std::endl;
	std::cout << "std before:"; print_container(*list_int_sort_std);
	std::cout << " ft before:"; print_container(*list_int_sort_ft);

	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::list<int>::iterator it_std = --list_int_sort_std->end();
	ft::List<int>::iterator it_ft = --list_int_sort_ft->end();

	std::cout << "it_std: " << *it_std << std::endl;
	std::cout << "it_ft : " << *it_ft << std::endl;

	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(*(--list_int_sort_std->end()), *(--list_int_sort_ft->end()));

	std::cout << std::endl;
	std::cout << "Reverse elements in container" << std::endl;
	list_int_sort_std->reverse();
	list_int_sort_ft->reverse();

	std::cout << "std after:"; print_container(*list_int_sort_std);
	std::cout << " ft after:"; print_container(*list_int_sort_ft);

	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std: " << *it_std << std::endl;
	std::cout << "it_ft : " << *it_ft << std::endl;

	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(*(--list_int_sort_std->end()), *(--list_int_sort_ft->end()));
}

TEST_F(Test_List, Capacity_size) {
	std::cout << "----- SIZE -----" << std::endl;
	std::cout << "std:"; print_container(*list_int_sort_std);
	std::cout << " ft:"; print_container(*list_int_sort_ft);
	std::cout << "std size: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size: " << list_int_sort_ft->size() << std::endl;

	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
}

TEST_F(Test_List, Capacity_max_size) {
	std::cout << "----- MAX SIZE -----" << std::endl;
	ft::List<int>	lst_ft;
	std::cout << " ft max_size: " << lst_ft.max_size() << std::endl;
}

TEST_F(Test_List, Capacity_empty) {
	std::cout << "----- EMPTY -----" << std::endl;
	std::cout << "std:"; print_container(*list_int_sort_std);
	std::cout << " ft:"; print_container(*list_int_sort_ft);
	std::cout << "std size: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size: " << list_int_sort_ft->size() << std::endl;
	std::cout << "std empty: " << std::boolalpha << list_int_sort_std->empty()
		<< std::endl;
	std::cout << " ft empty: " << std::boolalpha << list_int_sort_ft->empty()
		<< std::endl;

	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
	EXPECT_EQ(list_int_sort_std->empty(), list_int_sort_ft->empty());

	std::cout << std::endl;
	std::cout << "Clear containers" << std::endl;
	list_int_sort_std->clear();
	list_int_sort_ft->clear();

	std::cout << "std:"; print_container(*list_int_sort_std);
	std::cout << " ft:"; print_container(*list_int_sort_ft);
	std::cout << "std size: " << list_int_sort_std->size() << std::endl;
	std::cout << " ft size: " << list_int_sort_ft->size() << std::endl;
	std::cout << "std empty: " << std::boolalpha << list_int_sort_std->empty()
		<< std::endl;
	std::cout << " ft empty: " << std::boolalpha << list_int_sort_ft->empty()
		<< std::endl;

	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
	EXPECT_EQ(list_int_sort_std->empty(), list_int_sort_ft->empty());
}

TEST_F(Test_List, Non_member_overload_swap) {
	std::cout << "----- NON-MEMBER OVERLOAD SWAP -----" << std::endl;
	std::cout << "std_first before:"; print_container(*list_int_sort_std);
	std::cout << " ft_first before:"; print_container(*list_int_sort_ft);
	std::cout << std::endl;
	std::cout << "std_second before:"; print_container(*list_int_unsort_std);
	std::cout << " ft_second before:"; print_container(*list_int_unsort_ft);

	std::list<int>::iterator it_std_first = ++list_int_sort_std->begin();
	std::list<int>::iterator it_std_second = ++list_int_unsort_std->begin();
	ft::List<int>::iterator it_ft_first = ++list_int_sort_ft->begin();
	ft::List<int>::iterator it_ft_second = ++list_int_unsort_ft->begin();
	std::cout << std::endl;
	std::cout << "Create iterators" << std::endl;
	std::cout << "it_std_first before: " << *it_std_first << std::endl;
	std::cout << "it_ft_first before:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second before:" << *it_std_second << std::endl;
	std::cout << "it_ft_second before: " << *it_ft_second << std::endl;

	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(*list_int_unsort_std->begin(), *list_int_unsort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
	EXPECT_EQ(list_int_unsort_std->size(), list_int_unsort_ft->size());

	std::cout << std::endl;
	std::cout << "Swap first and second objects" << std::endl;

	std::swap(*list_int_sort_std, *list_int_unsort_std);
	ft::swap(*list_int_sort_ft, *list_int_unsort_ft);

	std::cout << "std_first after:"; print_container(*list_int_sort_std);
	std::cout << " ft_first after:"; print_container(*list_int_sort_ft);
	std::cout << std::endl;
	std::cout << "std_second after:"; print_container(*list_int_unsort_std);
	std::cout << " ft_second after:"; print_container(*list_int_unsort_ft);
	std::cout << std::endl;
	std::cout << "Check iterators (should be the same)" << std::endl;
	std::cout << "it_std_first after: " << *it_std_first << std::endl;
	std::cout << "it_ft_first after:  " << *it_ft_first << std::endl;
	std::cout << "it_std_second after:" << *it_std_second << std::endl;
	std::cout << "it_ft_second after: " << *it_ft_second << std::endl;

	EXPECT_EQ(*list_int_sort_std->begin(), *list_int_sort_ft->begin());
	EXPECT_EQ(*list_int_unsort_std->begin(), *list_int_unsort_ft->begin());
	EXPECT_EQ(list_int_sort_std->size(), list_int_sort_ft->size());
	EXPECT_EQ(list_int_unsort_std->size(), list_int_unsort_ft->size());
}

TEST_F(Test_List, relational_operators_equal) {
	{
		std::cout << "----- RELATIONAL OPERATORS == -----" << std::endl;
		std::cout << "std_first:"; print_container(*list_int_sort_std);
		std::cout << " ft_first:"; print_container(*list_int_sort_ft);
		std::cout << std::endl;
		std::cout << "std_second:"; print_container(*list_int_unsort_std);
		std::cout << " ft_second:"; print_container(*list_int_unsort_ft);

		std::cout << std::endl;
		std::cout << "std_first == std_second: " << std::boolalpha
			<< (list_int_sort_std == list_int_unsort_std) << std::endl;
		std::cout << " ft_first ==  ft_second: " << std::boolalpha
			<< (list_int_sort_ft == list_int_unsort_ft) << std::endl;

		EXPECT_EQ((*list_int_sort_std == *list_int_unsort_std), 0);
		EXPECT_EQ((*list_int_sort_ft == *list_int_unsort_ft), 0);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS == -----" << std::endl;
		std::cout << "std_first:"; print_container(*list_int_sort_std);
		std::cout << " ft_first:"; print_container(*list_int_sort_ft);
		std::cout << std::endl;

		std::list<int>	lst_std_copy(*list_int_sort_std);
		ft::List<int>	lst_ft_copy(*list_int_sort_ft);

		std::cout << "std_first_copy:"; print_container(lst_std_copy);
		std::cout << " ft_first_copy:"; print_container(lst_ft_copy);

		std::cout << std::endl;
		std::cout << "std_first == std_second: " << std::boolalpha
			<< (*list_int_sort_std == lst_std_copy) << std::endl;
		std::cout << " ft_first ==  ft_second: " << std::boolalpha
			<< (*list_int_sort_ft == lst_ft_copy) << std::endl;

		EXPECT_EQ((*list_int_sort_std == lst_std_copy), 1);
		EXPECT_EQ((*list_int_sort_ft == lst_ft_copy), 1);
	}
}

TEST_F(Test_List, relational_operators_not_equal) {
	{
		std::cout << "----- RELATIONAL OPERATORS != -----" << std::endl;
		std::cout << "std_first:"; print_container(*list_int_sort_std);
		std::cout << " ft_first:"; print_container(*list_int_sort_ft);
		std::cout << std::endl;
		std::cout << "std_second:"; print_container(*list_int_unsort_std);
		std::cout << " ft_second:"; print_container(*list_int_unsort_ft);

		std::cout << std::endl;
		std::cout << "std_first != std_second: " << std::boolalpha
			<< (list_int_sort_std != list_int_unsort_std) << std::endl;
		std::cout << " ft_first !=  ft_second: " << std::boolalpha
			<< (list_int_sort_ft != list_int_unsort_ft) << std::endl;

		EXPECT_EQ((*list_int_sort_std != *list_int_unsort_std), 1);
		EXPECT_EQ((*list_int_sort_ft != *list_int_unsort_ft), 1);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS != -----" << std::endl;
		std::cout << "std_first:"; print_container(*list_int_sort_std);
		std::cout << " ft_first:"; print_container(*list_int_sort_ft);
		std::cout << std::endl;

		std::list<int>	lst_std_copy(*list_int_sort_std);
		ft::List<int>	lst_ft_copy(*list_int_sort_ft);

		std::cout << "std_first_copy:"; print_container(lst_std_copy);
		std::cout << " ft_first_copy:"; print_container(lst_ft_copy);

		std::cout << std::endl;
		std::cout << "std_first != std_second: " << std::boolalpha
			<< (*list_int_sort_std != lst_std_copy) << std::endl;
		std::cout << " ft_first !=  ft_second: " << std::boolalpha
			<< (*list_int_sort_ft != lst_ft_copy) << std::endl;

		EXPECT_EQ((*list_int_sort_std != lst_std_copy), 0);
		EXPECT_EQ((*list_int_sort_ft != lst_ft_copy), 0);
	}
}

TEST_F(Test_List, relational_operators_less) {
	{
		std::cout << "----- RELATIONAL OPERATORS < -----" << std::endl;
		std::cout << "std_first:"; print_container(*list_int_sort_std);
		std::cout << " ft_first:"; print_container(*list_int_sort_ft);
		std::cout << std::endl;
		std::cout << "std_second:"; print_container(*list_int_unsort_std);
		std::cout << " ft_second:"; print_container(*list_int_unsort_ft);

		std::cout << std::endl;
		std::cout << "std_first < std_second: " << std::boolalpha
			<< (list_int_sort_std < list_int_unsort_std) << std::endl;
		std::cout << " ft_first <  ft_second: " << std::boolalpha
			<< (list_int_sort_ft < list_int_unsort_ft) << std::endl;

		EXPECT_EQ((*list_int_sort_std < *list_int_unsort_std), 1);
		EXPECT_EQ((*list_int_sort_ft < *list_int_unsort_ft), 1);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS < -----" << std::endl;
		std::cout << "std_first:"; print_container(*list_int_sort_std);
		std::cout << " ft_first:"; print_container(*list_int_sort_ft);
		std::cout << std::endl;

		std::list<int>	lst_std_copy(*list_int_sort_std);
		ft::List<int>	lst_ft_copy(*list_int_sort_ft);

		std::cout << "std_first_copy:"; print_container(lst_std_copy);
		std::cout << " ft_first_copy:"; print_container(lst_ft_copy);

		std::cout << std::endl;
		std::cout << "std_first < std_second: " << std::boolalpha
			<< (*list_int_sort_std < lst_std_copy) << std::endl;
		std::cout << " ft_first <  ft_second: " << std::boolalpha
			<< (*list_int_sort_ft < lst_ft_copy) << std::endl;

		EXPECT_EQ((*list_int_sort_std < lst_std_copy), 0);
		EXPECT_EQ((*list_int_sort_ft < lst_ft_copy), 0);
	}
}

TEST_F(Test_List, relational_operators_less_or_equal) {
	{
		std::cout << "----- RELATIONAL OPERATORS <= -----" << std::endl;
		std::cout << "std_first:"; print_container(*list_int_sort_std);
		std::cout << " ft_first:"; print_container(*list_int_sort_ft);
		std::cout << std::endl;
		std::cout << "std_second:"; print_container(*list_int_unsort_std);
		std::cout << " ft_second:"; print_container(*list_int_unsort_ft);

		std::cout << std::endl;
		std::cout << "std_first <= std_second: " << std::boolalpha
			<< (list_int_sort_std <= list_int_unsort_std) << std::endl;
		std::cout << " ft_first <=  ft_second: " << std::boolalpha
			<< (list_int_sort_ft <= list_int_unsort_ft) << std::endl;

		EXPECT_EQ((*list_int_sort_std <= *list_int_unsort_std), 1);
		EXPECT_EQ((*list_int_sort_ft <= *list_int_unsort_ft), 1);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS <= -----" << std::endl;
		std::cout << "std_first:"; print_container(*list_int_sort_std);
		std::cout << " ft_first:"; print_container(*list_int_sort_ft);
		std::cout << std::endl;

		std::list<int>	lst_std_copy(*list_int_sort_std);
		ft::List<int>	lst_ft_copy(*list_int_sort_ft);

		std::cout << "std_first_copy:"; print_container(lst_std_copy);
		std::cout << " ft_first_copy:"; print_container(lst_ft_copy);

		std::cout << std::endl;
		std::cout << "std_first <= std_second: " << std::boolalpha
			<< (*list_int_sort_std <= lst_std_copy) << std::endl;
		std::cout << " ft_first <=  ft_second: " << std::boolalpha
			<< (*list_int_sort_ft <= lst_ft_copy) << std::endl;

		EXPECT_EQ((*list_int_sort_std <= lst_std_copy), 1);
		EXPECT_EQ((*list_int_sort_ft <= lst_ft_copy), 1);
	}
}

TEST_F(Test_List, relational_operators_more) {
	{
		std::cout << "----- RELATIONAL OPERATORS > -----" << std::endl;
		std::cout << "std_first:"; print_container(*list_int_sort_std);
		std::cout << " ft_first:"; print_container(*list_int_sort_ft);
		std::cout << std::endl;
		std::cout << "std_second:"; print_container(*list_int_unsort_std);
		std::cout << " ft_second:"; print_container(*list_int_unsort_ft);

		std::cout << std::endl;
		std::cout << "std_first > std_second: " << std::boolalpha
			<< (list_int_sort_std > list_int_unsort_std) << std::endl;
		std::cout << " ft_first >  ft_second: " << std::boolalpha
			<< (list_int_sort_ft > list_int_unsort_ft) << std::endl;

		EXPECT_EQ((*list_int_sort_std > *list_int_unsort_std), 0);
		EXPECT_EQ((*list_int_sort_ft > *list_int_unsort_ft), 0);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS > -----" << std::endl;
		std::cout << "std_first:"; print_container(*list_int_sort_std);
		std::cout << " ft_first:"; print_container(*list_int_sort_ft);
		std::cout << std::endl;

		std::list<int>	lst_std_copy(*list_int_sort_std);
		ft::List<int>	lst_ft_copy(*list_int_sort_ft);

		std::cout << "std_first_copy:"; print_container(lst_std_copy);
		std::cout << " ft_first_copy:"; print_container(lst_ft_copy);

		std::cout << std::endl;
		std::cout << "std_first > std_second: " << std::boolalpha
			<< (*list_int_sort_std > lst_std_copy) << std::endl;
		std::cout << " ft_first >  ft_second: " << std::boolalpha
			<< (*list_int_sort_ft > lst_ft_copy) << std::endl;

		EXPECT_EQ((*list_int_sort_std > lst_std_copy), 0);
		EXPECT_EQ((*list_int_sort_ft > lst_ft_copy), 0);
	}
}

TEST_F(Test_List, relational_operators_more_or_equal) {
	{
		std::cout << "----- RELATIONAL OPERATORS > -----" << std::endl;
		std::cout << "std_first:"; print_container(*list_int_sort_std);
		std::cout << " ft_first:"; print_container(*list_int_sort_ft);
		std::cout << std::endl;
		std::cout << "std_second:"; print_container(*list_int_unsort_std);
		std::cout << " ft_second:"; print_container(*list_int_unsort_ft);

		std::cout << std::endl;
		std::cout << "std_first > std_second: " << std::boolalpha
			<< (list_int_sort_std > list_int_unsort_std) << std::endl;
		std::cout << " ft_first >  ft_second: " << std::boolalpha
			<< (list_int_sort_ft > list_int_unsort_ft) << std::endl;

		EXPECT_EQ((*list_int_sort_std > *list_int_unsort_std), 0);
		EXPECT_EQ((*list_int_sort_ft > *list_int_unsort_ft), 0);
	}
	{
		std::cout << "----- RELATIONAL OPERATORS >= -----" << std::endl;
		std::cout << "std_first:"; print_container(*list_int_sort_std);
		std::cout << " ft_first:"; print_container(*list_int_sort_ft);
		std::cout << std::endl;

		std::list<int>	lst_std_copy(*list_int_sort_std);
		ft::List<int>	lst_ft_copy(*list_int_sort_ft);

		std::cout << "std_first_copy:"; print_container(lst_std_copy);
		std::cout << " ft_first_copy:"; print_container(lst_ft_copy);

		std::cout << std::endl;
		std::cout << "std_first >= std_second: " << std::boolalpha
			<< (*list_int_sort_std >= lst_std_copy) << std::endl;
		std::cout << " ft_first >=  ft_second: " << std::boolalpha
			<< (*list_int_sort_ft >= lst_ft_copy) << std::endl;

		EXPECT_EQ((*list_int_sort_std >= lst_std_copy), 1);
		EXPECT_EQ((*list_int_sort_ft >= lst_ft_copy), 1);
	}
}

//TEST(INF_LOOP, Loop) {
//	while (1) {}
//}
