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
		std::list<std::string> lst_std(2, "test");
		ft::List<std::string> lst_ft(2, "test");

		std::cout << "----- CONSTRUCTOR (fill) -----" << std::endl;
		std::cout << "std before:";
		for (std::list<std::string>::iterator it = lst_std.begin();
				it != lst_std.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;
		std::cout << "ft before:";
		for (ft::List<std::string>::iterator it = lst_ft.begin();
				it != lst_ft.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;
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

TEST(List, Operations_Splice_entire_list) {
	std::list<int>	lst_std_1;
	lst_std_1.push_back(1);
	lst_std_1.push_back(2);
	lst_std_1.push_back(3);
	std::list<int>::iterator it_pos_std = ++lst_std_1.begin();
	std::list<int>	lst_std_2;
	lst_std_2.push_back(7);
	lst_std_2.push_back(8);

	ft::List<int>	lst_ft_1;
	lst_ft_1.push_back(1);
	lst_ft_1.push_back(2);
	lst_ft_1.push_back(3);
	ft::List<int>::iterator it_pos_ft = ++lst_ft_1.begin();
	ft::List<int>	lst_ft_2;
	lst_ft_2.push_back(7);
	lst_ft_2.push_back(8);

	std::cout << "----- SPLICE (entire_list) -----" << std::endl;
	std::cout << "List 1 std before splice:";
	for (std::list<int>::iterator it = lst_std_1.begin();
			it != lst_std_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 std before splice:";
	for (std::list<int>::iterator it = lst_std_2.begin();
			it != lst_std_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 std pos iterator (data) before splice: ";
	std::cout << *it_pos_std << std::endl;
	std::cout << "List 1 ft before splice:";
	for (ft::List<int>::iterator it = lst_ft_1.begin();
			it != lst_ft_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 ft before splice:";
	for (ft::List<int>::iterator it = lst_ft_2.begin();
			it != lst_ft_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 ft pos iterator (data) before splice: ";
	std::cout << *it_pos_ft << std::endl;

	lst_std_1.splice(it_pos_std, lst_std_2);
	lst_ft_1.splice(it_pos_ft, lst_ft_2);

	std::cout << std::endl;
	std::cout << "List 1 std after splice:";
	for (std::list<int>::iterator it = lst_std_1.begin();
			it != lst_std_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 std after splice:";
	for (std::list<int>::iterator it = lst_std_2.begin();
			it != lst_std_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 std pos iterator (data) after splice: ";
	std::cout << *it_pos_std << std::endl;
	std::cout << "List 1 ft after splice:";
	for (ft::List<int>::iterator it = lst_ft_1.begin();
			it != lst_ft_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 ft after splice:";
	for (ft::List<int>::iterator it = lst_ft_2.begin();
			it != lst_ft_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 ft pos iterator (data) after splice: ";
	std::cout << *it_pos_ft << std::endl;

	EXPECT_EQ(*lst_std_1.begin(), *lst_ft_1.begin());
	EXPECT_EQ(*lst_std_2.begin(), *lst_ft_2.begin());
	EXPECT_EQ(lst_std_1.size(), lst_ft_1.size());
	EXPECT_EQ(lst_std_2.size(), lst_ft_2.size());
}

TEST(List, Operations_Splice_range) {
	std::list<int>	lst_std_1;
	lst_std_1.push_back(1);
	lst_std_1.push_back(2);
	lst_std_1.push_back(3);
	lst_std_1.push_back(4);
	std::list<int>::iterator it_pos_std = ++lst_std_1.begin();
	std::list<int>	lst_std_2;
	lst_std_2.push_back(7);
	lst_std_2.push_back(8);
	lst_std_2.push_back(9);
	lst_std_2.push_back(10);
	std::list<int>::iterator it_first_std = ++lst_std_2.begin();
	std::list<int>::iterator it_last_std = it_first_std;
	++it_last_std;
	++it_last_std;

	ft::List<int>	lst_ft_1;
	lst_ft_1.push_back(1);
	lst_ft_1.push_back(2);
	lst_ft_1.push_back(3);
	lst_ft_1.push_back(4);
	ft::List<int>::iterator it_pos_ft = ++lst_ft_1.begin();
	ft::List<int>	lst_ft_2;
	lst_ft_2.push_back(7);
	lst_ft_2.push_back(8);
	lst_ft_2.push_back(9);
	lst_ft_2.push_back(10);
	ft::List<int>::iterator it_first_ft = ++lst_ft_2.begin();
	ft::List<int>::iterator it_last_ft = it_first_ft;
	++it_last_ft;
	++it_last_ft;

	std::cout << "----- SPLICE (range) -----" << std::endl;
	std::cout << "List 1 std before splice:";
	for (std::list<int>::iterator it = lst_std_1.begin();
			it != lst_std_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 std before splice:";
	for (std::list<int>::iterator it = lst_std_2.begin();
			it != lst_std_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 std pos iterator (data) before splice: ";
	std::cout << *it_pos_std << std::endl;
	std::cout << "List 1 ft before splice:";
	for (ft::List<int>::iterator it = lst_ft_1.begin();
			it != lst_ft_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 ft before splice:";
	for (ft::List<int>::iterator it = lst_ft_2.begin();
			it != lst_ft_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 ft pos iterator (data) before splice: ";
	std::cout << *it_pos_ft << std::endl;

	lst_std_1.splice(it_pos_std, lst_std_2, it_first_std, it_last_std);
	lst_ft_1.splice(it_pos_ft, lst_ft_2, it_first_ft, it_last_ft);

	std::cout << std::endl;
	std::cout << "List 1 std after splice:";
	for (std::list<int>::iterator it = lst_std_1.begin();
			it != lst_std_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 std after splice:";
	for (std::list<int>::iterator it = lst_std_2.begin();
			it != lst_std_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 std pos iterator (data) after splice: ";
	std::cout << *it_pos_std << std::endl;
	std::cout << "List 1 ft after splice:";
	for (ft::List<int>::iterator it = lst_ft_1.begin();
			it != lst_ft_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 ft after splice:";
	for (ft::List<int>::iterator it = lst_ft_2.begin();
			it != lst_ft_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 ft pos iterator (data) after splice: ";
	std::cout << *it_pos_ft << std::endl;

	EXPECT_EQ(*lst_std_1.begin(), *lst_ft_1.begin());
	EXPECT_EQ(*lst_std_2.begin(), *lst_ft_2.begin());
	EXPECT_EQ(lst_std_1.size(), lst_ft_1.size());
	EXPECT_EQ(lst_std_2.size(), lst_ft_2.size());
}

TEST(List, Operations_Splice_single_element) {
	std::list<int>	lst_std_1;
	lst_std_1.push_back(1);
	lst_std_1.push_back(2);
	lst_std_1.push_back(3);
	std::list<int>::iterator it_pos_std = ++lst_std_1.begin();
	std::list<int>	lst_std_2;
	lst_std_2.push_back(7);
	lst_std_2.push_back(8);

	ft::List<int>	lst_ft_1;
	lst_ft_1.push_back(1);
	lst_ft_1.push_back(2);
	lst_ft_1.push_back(3);
	ft::List<int>::iterator it_pos_ft = ++lst_ft_1.begin();
	ft::List<int>	lst_ft_2;
	lst_ft_2.push_back(7);
	lst_ft_2.push_back(8);

	std::cout << "----- SPLICE (single_element) -----" << std::endl;
	std::cout << "List 1 std before splice:";
	for (std::list<int>::iterator it = lst_std_1.begin();
			it != lst_std_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 std before splice:";
	for (std::list<int>::iterator it = lst_std_2.begin();
			it != lst_std_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 std pos iterator (data) before splice: ";
	std::cout << *it_pos_std << std::endl;
	std::cout << "List 1 ft before splice:";
	for (ft::List<int>::iterator it = lst_ft_1.begin();
			it != lst_ft_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 ft before splice:";
	for (ft::List<int>::iterator it = lst_ft_2.begin();
			it != lst_ft_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 ft pos iterator (data) before splice: ";
	std::cout << *it_pos_ft << std::endl;

	lst_std_2.splice(lst_std_2.begin(), lst_std_1, it_pos_std);
	lst_ft_2.splice(lst_ft_2.begin(), lst_ft_1, it_pos_ft);

	std::cout << std::endl;
	std::cout << "List 1 std after splice:";
	for (std::list<int>::iterator it = lst_std_1.begin();
			it != lst_std_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 std after splice:";
	for (std::list<int>::iterator it = lst_std_2.begin();
			it != lst_std_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 std pos iterator (data) after splice: ";
	std::cout << *it_pos_std << std::endl;
	std::cout << "List 1 ft after splice:";
	for (ft::List<int>::iterator it = lst_ft_1.begin();
			it != lst_ft_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 2 ft after splice:";
	for (ft::List<int>::iterator it = lst_ft_2.begin();
			it != lst_ft_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List 1 ft pos iterator (data) after splice: ";
	std::cout << *it_pos_ft << std::endl;

	EXPECT_EQ(*lst_std_1.begin(), *lst_ft_1.begin());
	EXPECT_EQ(*lst_std_2.begin(), *lst_ft_2.begin());
	EXPECT_EQ(lst_std_1.size(), lst_ft_1.size());
	EXPECT_EQ(lst_std_2.size(), lst_ft_2.size());
}

TEST(List, Operations_Remove) {
	std::list<int>	lst_std;
	for (int i = 0; i < 10; NULL) {
		lst_std.push_back(++i);
	}

	ft::List<int>	lst_ft;
	for (int i = 0; i < 10; NULL) {
		lst_ft.push_back(++i);
	}

	std::cout << "----- Remove -----" << std::endl;
	std::cout << "List std before remove:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List std size before remove: " << lst_std.size() << std::endl;
	std::cout << "List ft before remove:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List ft size before remove: " << lst_ft.size() << std::endl;

	lst_std.remove(3);
	lst_std.remove(6);
	lst_std.remove(9);
	lst_ft.remove(3);
	lst_ft.remove(6);
	lst_ft.remove(9);

	std::cout << std::endl;
	std::cout << "List std after remove:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List std size after remove: " << lst_std.size() << std::endl;
	std::cout << "List ft after remove:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List ft size after remove: " << lst_ft.size() << std::endl;

	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

bool	is_odd(const int& val) {
	return (val % 2) == 1;
}

TEST(List, Operations_Remove_if) {
	std::list<int>	lst_std;
	for (int i = 0; i < 10; NULL) {
		lst_std.push_back(++i);
	}

	ft::List<int>	lst_ft;
	for (int i = 0; i < 10; NULL) {
		lst_ft.push_back(++i);
	}

	std::cout << "----- Remove_if -----" << std::endl;
	std::cout << "List std before remove_if:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List std size before remove_if: " << lst_std.size()
		<< std::endl;
	std::cout << "List ft before remove_if:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List ft size before remove_if: " << lst_ft.size()
		<< std::endl;

	lst_std.remove_if(is_odd);
	lst_ft.remove_if(is_odd);

	std::cout << std::endl;
	std::cout << "List std after remove_if:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "std size after: " << lst_std.size()
		<< std::endl;
	std::cout << "ft after:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "List ft size after remove_if: " << lst_ft.size() << std::endl;

	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

TEST(List, Operations_Unique_no_args) {
	std::list<int>	lst_std;
	lst_std.push_back(1);
	lst_std.push_back(2);
	lst_std.push_back(2);
	lst_std.push_back(3);
	lst_std.push_back(3);
	lst_std.push_back(3);
	lst_std.push_back(4);
	lst_std.push_back(4);

	ft::List<int>	lst_ft;
	lst_ft.push_back(1);
	lst_ft.push_back(2);
	lst_ft.push_back(2);
	lst_ft.push_back(3);
	lst_ft.push_back(3);
	lst_ft.push_back(3);
	lst_ft.push_back(4);
	lst_ft.push_back(4);

	std::cout << "----- UNIQUE (no arguments) -----" << std::endl;
	std::cout << "std before:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "std size before: " << lst_std.size() << std::endl;
	std::cout << "ft before:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "ft size before: " << lst_ft.size() << std::endl;

	lst_std.unique();
	lst_ft.unique();

	std::cout << std::endl;
	std::cout << "std after:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "std size after: " << lst_std.size() << std::endl;
	std::cout << "ft after:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "ft size after: " << lst_ft.size() << std::endl;

	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

// a binary predicate implemented as a function:
bool	same_integral_part(double first, double second) {
	return ( int(first)==int(second) );
}

TEST(List, Operations_Unique_binary_pred) {
	std::list<double>	lst_std;
	lst_std.push_back(1.01);
	lst_std.push_back(1.05);
	lst_std.push_back(2.15);
	lst_std.push_back(2.25);
	lst_std.push_back(2.25);
	lst_std.push_back(3.40);
	lst_std.push_back(3.50);
	lst_std.push_back(4.70);

	ft::List<double>	lst_ft;
	lst_ft.push_back(1.01);
	lst_ft.push_back(1.05);
	lst_ft.push_back(2.15);
	lst_ft.push_back(2.25);
	lst_ft.push_back(2.25);
	lst_ft.push_back(3.40);
	lst_ft.push_back(3.50);
	lst_ft.push_back(4.70);

	std::cout << "----- UNIQUE (binary predicate) -----" << std::endl;
	std::cout << "std before:";
	for (std::list<double>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "std size before: " << lst_std.size() << std::endl;
	std::cout << "ft before:";
	for (ft::List<double>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "ft size before: " << lst_ft.size() << std::endl;

	lst_std.unique(same_integral_part);
	lst_ft.unique(same_integral_part);

	std::cout << std::endl;
	std::cout << "std after:";
	for (std::list<double>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "std size after: " << lst_std.size() << std::endl;
	std::cout << "ft after:";
	for (ft::List<double>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "ft size after: " << lst_ft.size() << std::endl;

	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
}

TEST(List, Operations_Merge_no_args) {
	std::list<int>	lst_std_1;
	lst_std_1.push_back(1);
	lst_std_1.push_back(3);
	lst_std_1.push_back(6);
	lst_std_1.push_back(7);
	lst_std_1.push_back(10);
	std::list<int>	lst_std_2;
	lst_std_2.push_back(2);
	lst_std_2.push_back(4);
	lst_std_2.push_back(5);
	lst_std_2.push_back(8);
	lst_std_2.push_back(9);

	ft::List<int>	lst_ft_1;
	lst_ft_1.push_back(1);
	lst_ft_1.push_back(3);
	lst_ft_1.push_back(6);
	lst_ft_1.push_back(7);
	lst_ft_1.push_back(10);
	ft::List<int>	lst_ft_2;
	lst_ft_2.push_back(2);
	lst_ft_2.push_back(4);
	lst_ft_2.push_back(5);
	lst_ft_2.push_back(8);
	lst_ft_2.push_back(9);

	std::cout << "----- MERGE (no arguments) -----" << std::endl;
	std::cout << "1 std before:";
	for (std::list<int>::iterator it = lst_std_1.begin();
			it != lst_std_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "2 std before:";
	for (std::list<int>::iterator it = lst_std_2.begin();
			it != lst_std_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "1 ft before:";
	for (ft::List<int>::iterator it = lst_ft_1.begin();
			it != lst_ft_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "2 ft before:";
	for (ft::List<int>::iterator it = lst_ft_2.begin();
			it != lst_ft_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;

	lst_std_1.merge(lst_std_2);
	lst_ft_1.merge(lst_ft_2);

	std::cout << std::endl;
	std::cout << "1 std after:";
	for (std::list<int>::iterator it = lst_std_1.begin();
			it != lst_std_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "2 std after:";
	for (std::list<int>::iterator it = lst_std_2.begin();
			it != lst_std_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "1 ft after:";
	for (ft::List<int>::iterator it = lst_ft_1.begin();
			it != lst_ft_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "2 ft after:";
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

// compare only integral part:
bool	mycomparison(double first, double second) {
	return ( int(first)<int(second) );
}

TEST(List, Operations_Merge_compare) {
	std::list<double>	lst_std_1;
	lst_std_1.push_back(1.01);
	lst_std_1.push_back(1.05);
	lst_std_1.push_back(2.15);
	lst_std_1.push_back(2.25);
	std::list<double>	lst_std_2;
	lst_std_2.push_back(2.25);
	lst_std_2.push_back(3.40);
	lst_std_2.push_back(3.50);
	lst_std_2.push_back(4.70);

	ft::List<double>	lst_ft_1;
	lst_ft_1.push_back(1.01);
	lst_ft_1.push_back(1.05);
	lst_ft_1.push_back(2.15);
	lst_ft_1.push_back(2.25);
	ft::List<double>	lst_ft_2;
	lst_ft_2.push_back(2.25);
	lst_ft_2.push_back(3.40);
	lst_ft_2.push_back(3.50);
	lst_ft_2.push_back(4.70);


	std::cout << "----- MERGE (compare) -----" << std::endl;
	std::cout << "1 std before:";
	for (std::list<double>::iterator it = lst_std_1.begin();
			it != lst_std_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "2 std before:";
	for (std::list<double>::iterator it = lst_std_2.begin();
			it != lst_std_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "1 ft before:";
	for (ft::List<double>::iterator it = lst_ft_1.begin();
			it != lst_ft_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "2 ft before:";
	for (ft::List<double>::iterator it = lst_ft_2.begin();
			it != lst_ft_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;

	lst_std_1.merge(lst_std_2, mycomparison);
	lst_ft_1.merge(lst_ft_2, mycomparison);

	std::cout << std::endl;
	std::cout << "1 std after:";
	for (std::list<double>::iterator it = lst_std_1.begin();
			it != lst_std_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "2 std after:";
	for (std::list<double>::iterator it = lst_std_2.begin();
			it != lst_std_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "1 ft after:";
	for (ft::List<double>::iterator it = lst_ft_1.begin();
			it != lst_ft_1.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "2 ft after:";
	for (ft::List<double>::iterator it = lst_ft_2.begin();
			it != lst_ft_2.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;

	EXPECT_EQ(*lst_std_1.begin(), *lst_ft_1.begin());
	EXPECT_EQ(*lst_std_2.begin(), *lst_ft_2.begin());
	EXPECT_EQ(lst_std_1.size(), lst_ft_1.size());
	EXPECT_EQ(lst_std_2.size(), lst_ft_2.size());
}

TEST(List, Operations_Sort_no_args) {
	std::list<int>	lst_std;
	lst_std.push_back(3);
	lst_std.push_back(2);
	lst_std.push_back(5);
	lst_std.push_back(4);
	lst_std.push_back(1);
	std::list<int>::iterator it_std = lst_std.begin();

	ft::List<int>	lst_ft;
	lst_ft.push_back(3);
	lst_ft.push_back(2);
	lst_ft.push_back(5);
	lst_ft.push_back(4);
	lst_ft.push_back(1);
	ft::List<int>::iterator it_ft = lst_ft.begin();

	std::cout << "----- SORT (no arguments) -----" << std::endl;
	std::cout << "std before:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "std size before: " << lst_std.size() << std::endl;
	std::cout << "it_std before: " << *it_std << std::endl;
	std::cout << "ft before:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "ft size before: " << lst_ft.size() << std::endl;
	std::cout << "it_ft before: " << *it_ft << std::endl;

	lst_std.sort();
	lst_ft.sort();

	std::cout << std::endl;
	std::cout << "std after:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "std size after: " << lst_std.size() << std::endl;
	std::cout << "it_std after: " << *it_std << std::endl;
	std::cout << "ft after:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "ft size after: " << lst_ft.size() << std::endl;
	std::cout << "it_ft after: " << *it_ft << std::endl;

	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());
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

TEST(List, Operations_Sort_compare) {
	std::list<std::string>	lst_std;
	lst_std.push_back ("one");
	lst_std.push_back ("two");
	lst_std.push_back ("Three");
	std::list<std::string>::iterator it_std = lst_std.begin();

	ft::List<std::string>	lst_ft;
	lst_ft.push_back ("one");
	lst_ft.push_back ("two");
	lst_ft.push_back ("Three");
	ft::List<std::string>::iterator it_ft = lst_ft.begin();

	std::cout << "----- SORT (compare) -----" << std::endl;
	std::cout << "std before:";
	for (std::list<std::string>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "std size before: " << lst_std.size() << std::endl;
	std::cout << "it_std before: " << *it_std << std::endl;
	std::cout << "ft before:";
	for (ft::List<std::string>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "ft size before: " << lst_ft.size() << std::endl;
	std::cout << "it_ft before: " << *it_ft << std::endl;

	lst_std.sort(compare_nocase);
	lst_ft.sort(compare_nocase);

	std::cout << std::endl;
	std::cout << "std after:";
	for (std::list<std::string>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "std size after: " << lst_std.size() << std::endl;
	std::cout << "it_std after: " << *it_std << std::endl;
	std::cout << "ft after:";
	for (ft::List<std::string>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "ft size after: " << lst_ft.size() << std::endl;
	std::cout << "it_ft after: " << *it_ft << std::endl;

	EXPECT_EQ(*(--lst_std.end()), *(--lst_ft.end()));
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

TEST(List, Operations_Reverse) {
	std::list<int>	lst_std;
	lst_std.push_back(1);
	lst_std.push_back(2);
	lst_std.push_back(3);
	lst_std.push_back(4);
	lst_std.push_back(5);
	std::list<int>::iterator it_std = lst_std.begin();

	ft::List<int>	lst_ft;
	lst_ft.push_back(1);
	lst_ft.push_back(2);
	lst_ft.push_back(3);
	lst_ft.push_back(4);
	lst_ft.push_back(5);
	ft::List<int>::iterator it_ft = lst_ft.begin();

	std::cout << "----- REVERSE -----" << std::endl;
	std::cout << "std before:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "std size before: " << lst_std.size() << std::endl;
	std::cout << "it_std before: " << *it_std << std::endl;
	std::cout << "ft before:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "ft size before: " << lst_ft.size() << std::endl;
	std::cout << "it_ft before: " << *it_ft << std::endl;

	lst_std.reverse();
	lst_ft.reverse();

	std::cout << std::endl;
	std::cout << "std after:";
	for (std::list<int>::iterator it = lst_std.begin();
			it != lst_std.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "std size after: " << lst_std.size() << std::endl;
	std::cout << "it_std after: " << *it_std << std::endl;
	std::cout << "ft after:";
	for (ft::List<int>::iterator it = lst_ft.begin();
			it != lst_ft.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
	std::cout << "ft size after: " << lst_ft.size() << std::endl;
	std::cout << "it_ft after: " << *it_ft << std::endl;

	EXPECT_EQ(*lst_std.begin(), *lst_ft.begin());
	EXPECT_EQ(lst_std.size(), lst_ft.size());
}

TEST(List, Observers_Get_allocator) {
	std::list<int> mylist_std;
	int * p_std;

	// allocate an array of 5 elements using mylist's allocator:
	p_std = mylist_std.get_allocator().allocate(5);

	// assign some values to array
	for (int i = 0; i < 5; ++i) p_std[i] = i;

	std::cout << "----- GET_ALLOCATOR -----" << std::endl;
	std::cout << "std The allocated array contains:";
	for (int i = 0; i < 5; ++i) std::cout << ' ' << p_std[i];
	std::cout << '\n';


	ft::List<int> mylist_ft;
	int * p_ft;

	// allocate an array of 5 elements using mylist's allocator:
	p_ft = mylist_ft.get_allocator().allocate(5);

	// assign some values to array
	for (int i = 0; i < 5; ++i) p_ft[i] = i;

	std::cout << "ft The allocated array contains:";
	for (int i = 0; i < 5; ++i) std::cout << ' ' << p_ft[i];
	std::cout << '\n';

	EXPECT_EQ(p_std[0], p_ft[0]);
	EXPECT_EQ(mylist_std.size(), mylist_ft.size());

	mylist_std.get_allocator().deallocate(p_std,5);
	mylist_ft.get_allocator().deallocate(p_ft,5);
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

//TEST(INF_LOOP, Loop) {
//	while (1) {}
//}
