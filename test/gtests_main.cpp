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

//class Test_List : public ::testing::Test {
//protected:
//	void SetUp() {
//		list_empty_std = new std::list<int>;
//		list_empty_ft = new ft::List<int>;
//
//		list_filled_std = new std::list<int>(5, 1);
//		list_filled_ft = new ft::List<int>(5, 1);
//
//		list_range_std = new std::list<int>;
//		list_range_std->push_back(1);
//		list_range_std->push_back(2);
//		list_range_std->push_back(3);
//		list_range_std->push_back(4);
//		list_range_std->push_back(5);
//
//		list_range_ft = new ft::List<int>;
//		list_range_ft->push_back(1);
//		list_range_ft->push_back(2);
//		list_range_ft->push_back(3);
//		list_range_ft->push_back(4);
//		list_range_ft->push_back(5);
//	}
//	void TearDown() {
//		delete list_empty_std;
//		delete list_empty_ft;
//
//		delete list_filled_std;
//		delete list_filled_ft;
//
//		delete list_range_std;
//		delete list_range_ft;
//	}
//	std::list<int> * list_empty_std;
//	ft::List<int> * list_empty_ft;
//
//	std::list<int> * list_filled_std;
//	ft::List<int> * list_filled_ft;
//
//	std::list<int> * list_range_std;
//	ft::List<int> * list_range_ft;
//};
//
//TEST_F(Test_List, Constructor_Default) {
//	EXPECT_EQ(*list_empty_std->begin(), *list_empty_ft->begin());
//}
//
//TEST_F(Test_List, Constructor_Fill) {
//	EXPECT_EQ(*list_filled_std->begin(), *list_filled_ft->begin());
//}

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
	EXPECT_EQ(*(--lst_std_copy.end()), *(--lst_ft_copy.end()));
}

TEST(List, Constructor_Range) {
	std::list<int>	lst_std;
	lst_std.push_back(1);
	lst_std.push_back(2);
	lst_std.push_back(3);
	lst_std.push_back(4);
	std::list<int>	lst_std_copy(++lst_std.rbegin(), --lst_std.rend());

	ft::List<int>	lst_ft;
	lst_ft.push_back(1);
	lst_ft.push_back(2);
	lst_ft.push_back(3);
	lst_ft.push_back(4);
	ft::List<int>	lst_ft_copy(++lst_ft.rbegin(), --lst_ft.rend());

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
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

TEST(List, Modifiers_Pop_front) {
	std::list<int>	lst_std;
	lst_std.push_back(1);
	lst_std.push_back(2);
	lst_std.push_back(3);

	ft::List<int>	lst_ft;
	lst_ft.push_back(1);
	lst_ft.push_back(2);
	lst_ft.push_back(3);

	std::cout << "----- POP_FRONT -----" << std::endl;
	std::cout << "First element before \'pop_front\': "
		<< *lst_std.begin() << "  " << *lst_ft.begin() << std::endl;
lst_std.pop_front();
	lst_ft.pop_front();
	std::cout << "First element after  \'pop_front\': "
		<< *lst_std.begin() << "  " << *lst_ft.begin() << std::endl;

	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

TEST(List, Modifiers_Pop_back) {
	std::list<int>	lst_std;
	lst_std.push_back(1);
	lst_std.push_back(2);
	lst_std.push_back(3);

	ft::List<int>	lst_ft;
	lst_ft.push_back(1);
	lst_ft.push_back(2);
	lst_ft.push_back(3);

	std::cout << "----- POP_BACK -----" << std::endl;
	std::cout << "Last element before \'pop_back\': "
		<< *(--lst_std.end()) << "  " << *(--lst_ft.end()) << std::endl;
	lst_std.pop_back();
	lst_ft.pop_back();
	std::cout << "Last element after \'pop_back\': "
		<< *(--lst_std.end()) << "  " << *(--lst_ft.end()) << std::endl;

	EXPECT_EQ(*(--lst_ft.end()), *(--lst_ft.end()));
	EXPECT_EQ(lst_ft.size(), lst_ft.size());
}

TEST(List, Modifiers_Element_access_Front) {
	std::list<int>	lst_std;
	lst_std.push_back(1);
	lst_std.push_back(2);
	lst_std.push_back(3);
	int & front_std = lst_std.front();

	ft::List<int>	lst_ft;
	lst_ft.push_back(1);
	lst_ft.push_back(2);
	lst_ft.push_back(3);
	int & front_ft = lst_ft.front();

	std::cout << "----- FRONT -----" << std::endl;
	std::cout << "Data of first element: "
		<< front_std << "  " << front_ft << std::endl;
front_std++;
	front_ft++;
	std::cout << "Modified data of first element: "
		<< lst_std.front() << "  " << lst_ft.front() << std::endl;

	EXPECT_EQ(lst_std.front(), lst_ft.front());
}

TEST(List, Modifiers_Element_access_Back) {
	std::list<int>	lst_std;
	lst_std.push_back(1);
	lst_std.push_back(2);
	lst_std.push_back(3);
	int & back_std = lst_std.back();

	ft::List<int>	lst_ft;
	lst_ft.push_back(1);
	lst_ft.push_back(2);
	lst_ft.push_back(3);
	int & back_ft = lst_ft.back();

	std::cout << "----- BACK -----" << std::endl;
	std::cout << "Data of last element: "
		<< back_std << "  " << back_ft << std::endl;
back_std++;
	back_ft++;
	std::cout << "Modified data of last element: "
		<< lst_std.back() << "  " << lst_ft.back() << std::endl;

	EXPECT_EQ(lst_std.back(), lst_ft.back());
}

TEST(List, Modifiers_Assign) {
	{
		std::list<int>	lst_std_first;
		lst_std_first.push_back(1);
		lst_std_first.push_back(2);
		lst_std_first.push_back(3);
		std::list<int>	lst_std_second;
		lst_std_second.assign(++lst_std_first.begin(), lst_std_first.end());

		ft::List<int>	lst_ft_first;
		lst_ft_first.push_back(1);
		lst_ft_first.push_back(2);
		lst_ft_first.push_back(3);
		std::list<int>	lst_ft_second;
		lst_ft_second.assign(++lst_std_first.begin(), lst_std_first.end());

		std::cout << "----- ASSIGN (range) -----" << std::endl;
		std::cout << "First element of assigned list: "
			<< *lst_std_second.begin() << "  " << *lst_ft_second.begin()
			<< std::endl;
		std::cout << "Size of assigned list: "
			<< lst_std_second.size() << "  " << lst_ft_second.size()
			<< std::endl;
		EXPECT_EQ(*lst_std_second.begin(), *lst_ft_second.begin());
		EXPECT_EQ(lst_std_second.size(), lst_ft_second.size());
	}
	{
		std::list<int>	lst_std;
		lst_std.assign(5, 7);

		ft::List<int>	lst_ft;
		lst_ft.assign(5, 7);

		std::cout << "----- ASSIGN (fill) -----" << std::endl;
		std::cout << "First element of assigned list: "
			<< *lst_std.begin() << "  " << *lst_ft.begin()
			<< std::endl;
		std::cout << "Size of assigned list: "
			<< lst_std.size() << "  " << lst_ft.size()
			<< std::endl;
		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
		EXPECT_EQ(lst_std.size(), lst_ft.size());
	}
}

TEST(List, Modifiers_Insert_Single_element) {
	std::list<int>	lst_std;
	lst_std.push_back(1);
	lst_std.push_back(2);
	lst_std.push_back(3);

	ft::List<int>	lst_ft;
	lst_ft.push_back(1);
	lst_ft.push_back(2);
	lst_ft.push_back(3);

	std::cout << "----- INSERT (single element) -----" << std::endl;
	std::cout << "Size of list before insert: "
		<< lst_std.size() << "  " << lst_ft.size() << std::endl;
	std::cout << "Data of inserted element: "
		<< *lst_std.insert(++lst_std.begin(), 7) << "  "
		<< *lst_ft.insert(++lst_ft.begin(), 7) << std::endl;
	std::cout << "Size of list after insert: "
		<< lst_std.size() << "  " << lst_ft.size() << std::endl;

	EXPECT_EQ(*(++lst_std.begin()), *(++lst_ft.begin()));
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

TEST(List, Modifiers_Insert_Fill) {
	std::list<int>	lst_std;
	lst_std.push_back(1);
	lst_std.push_back(2);
	lst_std.push_back(3);

	ft::List<int>	lst_ft;
	lst_ft.push_back(1);
	lst_ft.push_back(2);
	lst_ft.push_back(3);

	std::cout << "----- INSERT (fill) -----" << std::endl;
	std::cout << "List std before insert:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List ft before insert:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	lst_std.insert(++lst_std.begin(), 5, 7);
	lst_ft.insert(++lst_ft.begin(), 5, 7);
	std::cout << "List std after insert:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List ft after insert:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;

	EXPECT_EQ(*(++lst_std.begin()), *(++lst_ft.begin()));
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

TEST(List, Modifiers_Insert_Range) {
	std::list<int>	lst_std;
	lst_std.push_back(1);
	lst_std.push_back(2);
	lst_std.push_back(3);
	std::list<int>	lst_std_2;
	lst_std_2.push_back(7);
	lst_std_2.push_back(8);

	ft::List<int>	lst_ft;
	lst_ft.push_back(1);
	lst_ft.push_back(2);
	lst_ft.push_back(3);
	ft::List<int>	lst_ft_2;
	lst_ft_2.push_back(7);
	lst_ft_2.push_back(8);

	std::cout << "----- INSERT (range) -----" << std::endl;
	std::cout << "List std before insert:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List ft before insert:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	lst_std.insert(++lst_std.begin(), lst_std_2.begin(), lst_std_2.end());
	lst_ft.insert(++lst_ft.begin(), lst_ft_2.begin(), lst_ft_2.end());
	std::cout << "List std after insert:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List ft after insert:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;

	EXPECT_EQ(*(++lst_std.begin()), *(++lst_ft.begin()));
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

TEST(List, Modifiers_Swap) {
	std::list<int>	lst_std_1;
	lst_std_1.push_back(1);
	lst_std_1.push_back(2);
	lst_std_1.push_back(3);
	std::list<int>	lst_std_2;
	lst_std_2.push_back(7);
	lst_std_2.push_back(8);

	ft::List<int>	lst_ft_1;
	lst_ft_1.push_back(1);
	lst_ft_1.push_back(2);
	lst_ft_1.push_back(3);
	ft::List<int>	lst_ft_2;
	lst_ft_2.push_back(7);
	lst_ft_2.push_back(8);

	std::cout << "----- SWAP -----" << std::endl;
	std::cout << "List 1 std before swap:";
	for (std::list<int>::iterator it = lst_std_1.begin();
			it != lst_std_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 std before swap:";
	for (std::list<int>::iterator it = lst_std_2.begin();
			it != lst_std_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 ft before swap:";
	for (ft::List<int>::iterator it = lst_ft_1.begin();
			it != lst_ft_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 ft before swap:";
	for (ft::List<int>::iterator it = lst_ft_2.begin();
			it != lst_ft_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	lst_std_1.swap(lst_std_2);
	lst_ft_1.swap(lst_ft_2);
	std::cout << std::endl;
	std::cout << "List 1 std after swap:";
	for (std::list<int>::iterator it = lst_std_1.begin();
			it != lst_std_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 std after swap:";
	for (std::list<int>::iterator it = lst_std_2.begin();
			it != lst_std_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 ft after swap:";
	for (ft::List<int>::iterator it = lst_ft_1.begin();
			it != lst_ft_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 ft after swap:";
	for (ft::List<int>::iterator it = lst_ft_2.begin();
			it != lst_ft_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;

	EXPECT_EQ(*lst_std_1.begin(), *lst_ft_1.begin());
	EXPECT_EQ(*lst_std_2.begin(), *lst_ft_2.begin());
	EXPECT_EQ(lst_std_1.size(), lst_ft_1.size());
	EXPECT_EQ(lst_std_2.size(), lst_ft_2.size());
}

TEST(List, Modifiers_Resize) {
	{
		std::list<int> lst_std;
		lst_std.push_back(1);
		lst_std.push_back(2);
		lst_std.push_back(3);
		lst_std.push_back(4);
		lst_std.push_back(5);

		ft::List<int> lst_ft;
		lst_ft.push_back(1);
		lst_ft.push_back(2);
		lst_ft.push_back(3);
		lst_ft.push_back(4);
		lst_ft.push_back(5);

		std::cout << "----- RESIZE (reduce) -----" << std::endl;
		std::cout << "List std before resize:";
		for (std::list<int>::iterator it = lst_std.begin();
				it != lst_std.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;
		std::cout << "List ft before resize:";
		for (ft::List<int>::iterator it = lst_ft.begin();
				it != lst_ft.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
		EXPECT_EQ(lst_std.size(), lst_ft.size());

		lst_std.resize(2);
		lst_ft.resize(2);
		std::cout << std::endl;
		std::cout << "List std after resize:";
		for (std::list<int>::iterator it = lst_std.begin();
				it != lst_std.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;
		std::cout << "List ft after resize:";
		for (ft::List<int>::iterator it = lst_ft.begin();
				it != lst_ft.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
		EXPECT_EQ(lst_std.size(), lst_ft.size());
	}
	{
		std::list<int> lst_std;
		lst_std.push_back(1);
		lst_std.push_back(2);
		lst_std.push_back(3);

		ft::List<int> lst_ft;
		lst_ft.push_back(1);
		lst_ft.push_back(2);
		lst_ft.push_back(3);

		std::cout << "----- RESIZE (incrase default) -----" << std::endl;
		std::cout << "List std before resize:";
		for (std::list<int>::iterator it = lst_std.begin();
				it != lst_std.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;
		std::cout << "List ft before resize:";
		for (ft::List<int>::iterator it = lst_ft.begin();
				it != lst_ft.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
		EXPECT_EQ(lst_std.size(), lst_ft.size());

		lst_std.resize(5);
		lst_ft.resize(5);
		std::cout << std::endl;
		std::cout << "List std after resize:";
		for (std::list<int>::iterator it = lst_std.begin();
				it != lst_std.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;
		std::cout << "List ft after resize:";
		for (ft::List<int>::iterator it = lst_ft.begin();
				it != lst_ft.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
		EXPECT_EQ(lst_std.size(), lst_ft.size());
	}
	{
		std::list<int> lst_std;
		lst_std.push_back(1);
		lst_std.push_back(2);
		lst_std.push_back(3);

		ft::List<int> lst_ft;
		lst_ft.push_back(1);
		lst_ft.push_back(2);
		lst_ft.push_back(3);

		std::cout << "----- RESIZE (incrase fill) -----" << std::endl;
		std::cout << "List std before resize:";
		for (std::list<int>::iterator it = lst_std.begin();
				it != lst_std.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;
		std::cout << "List ft before resize:";
		for (ft::List<int>::iterator it = lst_ft.begin();
				it != lst_ft.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
		EXPECT_EQ(lst_std.size(), lst_ft.size());

		lst_std.resize(5, 7);
		lst_ft.resize(5, 7);
		std::cout << std::endl;
		std::cout << "List std after resize:";
		for (std::list<int>::iterator it = lst_std.begin();
				it != lst_std.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;
		std::cout << "List ft after resize:";
		for (ft::List<int>::iterator it = lst_ft.begin();
				it != lst_ft.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
		EXPECT_EQ(lst_std.size(), lst_ft.size());
	}
}

TEST(List, Capacity_Size) {
	std::list<int>	lst_std(2, 5);
	ft::List<int>	lst_ft(2, 5);

	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

//TEST(List, Capacity_Max_size) { // TODO
//	std::list<int>	lst_std(2);
//	ft::List<int>	lst_ft(2);
//
//	EXPECT_EQ(lst_std.max_size(), lst_ft.size());
//}

TEST(List, Capacity_Empty) {
	{
		std::list<int>	lst_std(2);
		ft::List<int>	lst_ft(2);

		EXPECT_EQ(lst_std.empty(), lst_ft.empty());
	}
	{
		std::list<int>	lst_std;
		ft::List<int>	lst_ft;

		EXPECT_EQ(lst_std.empty(), lst_ft.empty());
	}
}
