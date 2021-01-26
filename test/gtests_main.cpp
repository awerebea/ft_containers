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

TEST(List, Constructors) {
	// default
	{
		std::list<int>	lst_std;
		ft::List<int>	lst_ft;
		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	}
	// fill
	{
		std::list<int>	lst_std(2);
		ft::List<int>	lst_ft(2);
		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	}
	{
		std::list<int>	lst_std(2, 5);
		ft::List<int>	lst_ft(2, 5);
		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	}

	{
		std::list<int>	* lst_std = new std::list<int>(5, 5);
		ft::List<int>	* lst_ft = new ft::List<int>(5, 5);

		delete(lst_std);
		delete(lst_ft);
	}
}

TEST(List, Clear) {
	std::list<int>	lst_std(2, 5);
	ft::List<int>	lst_ft(2, 5);
	std::cout << *lst_ft.begin() << std::endl;
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	lst_std.clear();
	lst_ft.clear();
	std::cout << *lst_ft.begin() << std::endl;
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
}

TEST(List, Iterators) {
	std::list<int>	lst_std(2, 1);
	ft::List<int>	lst_ft(2, 1);
	// Begin
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
}

TEST(List, Operator_Assign) {
	ft::List<int>	lst_1(2, 1);
	ft::List<int>	lst_2(5, 2);
	std::cout << *lst_1.begin() << std::endl;
	std::cout << *lst_2.begin() << std::endl;
	lst_2 = lst_1;
	std::cout << *lst_2.begin() << std::endl;
	EXPECT_EQ(*lst_1.begin(), *lst_2.begin());
}
