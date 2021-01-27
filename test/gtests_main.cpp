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
#include "List.h"
#include <list>

TEST(List, Constructor_Default) {
	std::list<int> lst_std;
	ft::List<int> lst_ft;
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
}

TEST(List, Constructor_Fill) {
	{
		std::list<int> lst_std(2);
		ft::List<int> lst_ft(2);
		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	}
	{
		std::list<int> lst_std(2, 5);
		ft::List<int> lst_ft(2, 5);
		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	}
}

TEST(List, Constructor_Copy) {
	std::list<int>	lst_std;
	lst_std.push_back(1);
	lst_std.push_back(2);
	lst_std.push_back(3);
	std::list<int>	lst_std_copy = lst_std;

	ft::List<int>	lst_ft;
	lst_ft.push_back(1);
	lst_ft.push_back(2);
	lst_ft.push_back(3);
	ft::List<int>	lst_ft_copy = lst_ft;
	EXPECT_EQ(*lst_std_copy.begin(), *lst_ft_copy.begin());
}

TEST(List, Destructor) {
	std::list<int>	* lst_std = new std::list<int>(5, 5);
	ft::List<int>	* lst_ft = new ft::List<int>(5, 5);

	delete(lst_std);
	delete(lst_ft);
}

TEST(List, Operator_Assign) {
	ft::List<int>	lst_1(2, 1);
	ft::List<int>	lst_2(5, 2);
	lst_2 = lst_1;
	EXPECT_EQ(*lst_1.begin(), *lst_2.begin());
}

TEST(List, Iterators) {
	std::list<int>	lst_std(2, 1);
	ft::List<int>	lst_ft(2, 1);
	// Begin
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
}

TEST(List, Modifiers_Clear) {
	std::list<int>	lst_std(2, 5);
	ft::List<int>	lst_ft(2, 5);
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	lst_std.clear();
	lst_ft.clear();
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
}

TEST(List, Modifiers_Erase) {
	std::list<int>	lst_std;
	lst_std.push_back(1);
	lst_std.push_back(2);
	lst_std.push_back(3);
	lst_std.erase(lst_std.begin());

	ft::List<int>	lst_ft;
	lst_ft.push_back(1);
	lst_ft.push_back(2);
	lst_ft.push_back(3);
	lst_ft.erase(lst_ft.begin());

	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
}

TEST(List, Modifiers_Erase_Range) {
	std::list<int>	lst_std;
	lst_std.push_back(1);
	lst_std.push_back(2);
	lst_std.push_back(3);
	std::list<int>::iterator	it_std1 = lst_std.begin();
	std::list<int>::iterator	it_std2 = it_std1;
	lst_std.erase(it_std1, ++it_std2);

	ft::List<int>	lst_ft;
	lst_ft.push_back(1);
	lst_ft.push_back(2);
	lst_ft.push_back(3);
	ft::List<int>::iterator	it_ft1 = lst_ft.begin();
	ft::List<int>::iterator	it_ft2 = it_ft1;
	lst_ft.erase(it_ft1, ++it_ft2);

	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
}