/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_queue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:44:04 by awerebea          #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <queue>
#include "all_test_utils.hpp"
#include "Queue.hpp"

class Test_Queue : public ::testing::Test {
protected:
	void SetUp() {
		int_sort_std = new std::queue<int>;
		for (int i = 0; i < 5; ++i) {
			int_sort_std->push(i + 1);
		}
		int_sort_ft = new ft::Queue<int>;
		for (int i = 0; i < 5; ++i) {
			int_sort_ft->push(i + 1);
		}
		int unsort_int_arr[] = { 8, 0, 6, 9, 7, 33, 44, 11, 22 };
		int_unsort_std = new std::queue<int>;
		for (int i = 0; i < 9; ++i) {
			int_unsort_std->push(unsort_int_arr[i]);
		}
		int_unsort_ft = new ft::Queue<int>;
		for (int i = 0; i < 9; ++i) {
			int_unsort_ft->push(unsort_int_arr[i]);
		}
	}
	void TearDown() {
		delete int_sort_std;
		delete int_sort_ft;

		delete int_unsort_std;
		delete int_unsort_ft;
	}
	std::queue<int> * int_sort_std;
	ft::Queue<int> * int_sort_ft;

	std::queue<int> * int_unsort_std;
	ft::Queue<int> * int_unsort_ft;
};

TEST_F(Test_Queue, Constructor) {
	std::cout << "----- CONSTRUCTOR (default) -----" << std::endl;
	std::queue<int> ctnr_std;
	ft::Queue<int> ctnr_ft;
	compare_size(ctnr_std, ctnr_ft);

	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
}

TEST_F(Test_Queue, Empty) {
	std::cout << "----- EMPTY (non-empty container) -----" << std::endl;
	compare_size(*int_sort_std, *int_sort_ft);
	std::cout << "std empty: " << std::boolalpha << int_sort_std->empty()
		<< std::endl;
	std::cout << " ft empty: " << std::boolalpha << int_sort_ft->empty()
		<< std::endl;

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->empty(), int_sort_ft->empty());

	std::cout << "----- EMPTY (empty container) -----" << std::endl;
	std::queue<int> ctnr_std;
	ft::Queue<int> ctnr_ft;
	compare_size(ctnr_std, ctnr_ft);
	std::cout << "std empty: " << std::boolalpha << ctnr_std.empty()
		<< std::endl;
	std::cout << " ft empty: " << std::boolalpha << ctnr_ft.empty()
		<< std::endl;

	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
	EXPECT_EQ(ctnr_std.empty(), ctnr_ft.empty());
}

TEST_F(Test_Queue, Size) {
	std::cout << "----- SIZE (non-empty container) -----" << std::endl;
	compare_size(*int_sort_std, *int_sort_ft);

	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());

	std::cout << "----- SIZE (empty container) -----" << std::endl;
	std::queue<int> ctnr_std;
	ft::Queue<int> ctnr_ft;
	compare_size(ctnr_std, ctnr_ft);

	EXPECT_EQ(ctnr_std.size(), ctnr_ft.size());
}

TEST_F(Test_Queue, Front) {
	std::cout << "----- FRONT -----" << std::endl;
	compare_elements(int_sort_std->front(), int_sort_ft->front());
	EXPECT_EQ(int_sort_std->front(), int_sort_ft->front());
}

TEST_F(Test_Queue, Back) {
	std::cout << "----- ELEMENT ACCESS BACK -----" << std::endl;
	compare_elements(int_sort_std->back(), int_sort_ft->back());
	EXPECT_EQ(int_sort_std->back(), int_sort_ft->back());
}

TEST_F(Test_Queue, Push) {
	std::cout << "----- PUSH -----" << std::endl;
	compare_size(*int_sort_std, *int_sort_ft, " before");
	compare_elements(int_sort_std->back(), int_sort_ft->back(),
			" back() before");
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->back(), int_sort_ft->back());

	std::cout << std::endl;
	std::cout << "push(7)" << std::endl;

	int_sort_std->push(7);
	int_sort_ft->push(7);

	compare_size(*int_sort_std, *int_sort_ft, " after");
	compare_elements(int_sort_std->back(), int_sort_ft->back(),
			" back() after");
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->back(), int_sort_ft->back());
}

TEST_F(Test_Queue, Pop) {
	std::cout << "----- POP -----" << std::endl;
	compare_size(*int_sort_std, *int_sort_ft, " before");
	compare_elements(int_sort_std->front(), int_sort_ft->front(),
			" front() before");
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->front(), int_sort_ft->front());

	std::cout << std::endl;
	std::cout << "pop()" << std::endl;

	int_sort_std->pop();
	int_sort_ft->pop();

	compare_size(*int_sort_std, *int_sort_ft, " after");
	compare_elements(int_sort_std->front(), int_sort_ft->front(),
			" front() after");
	EXPECT_EQ(int_sort_std->size(), int_sort_ft->size());
	EXPECT_EQ(int_sort_std->front(), int_sort_ft->front());
}

TEST_F(Test_Queue, Relational_operators_Equal) {
	std::cout << "----- RELATIONAL OPERATORS == -----" << std::endl;
	std::cout << "Comparsion (1,2,3,4,5) and (8,0,6,9,7,33,44,11,22) containers"
		<< std::endl;

	std::cout << "std_first == std_second: " << std::boolalpha
		<< (*int_sort_std == *int_unsort_std) << std::endl;
	std::cout << " ft_first ==  ft_second: " << std::boolalpha
		<< (*int_sort_ft == *int_unsort_ft) << std::endl;
	std::cout << std::endl;

	EXPECT_EQ((*int_sort_std == *int_unsort_std), 0);
	EXPECT_EQ((*int_sort_ft == *int_unsort_ft), 0);

	std::cout << "Comparsion (1,2,3,4,5) and (1,2,3,4,5) containers"
		<< std::endl;

	std::queue<int> ctnr_std;
	ft::Queue<int> ctnr_ft;

	ctnr_std.push(1);
	ctnr_std.push(2);
	ctnr_std.push(3);
	ctnr_std.push(4);
	ctnr_std.push(5);

	ctnr_ft.push(1);
	ctnr_ft.push(2);
	ctnr_ft.push(3);
	ctnr_ft.push(4);
	ctnr_ft.push(5);

	std::cout << "std_first == std_second: " << std::boolalpha
		<< (*int_sort_std == ctnr_std) << std::endl;
	std::cout << " ft_first ==  ft_second: " << std::boolalpha
		<< (*int_sort_ft == ctnr_ft) << std::endl;

	EXPECT_EQ((*int_sort_std == ctnr_std), 1);
	EXPECT_EQ((*int_sort_ft == ctnr_ft), 1);
}

TEST_F(Test_Queue, Relational_operators_Not_equal) {
	std::cout << "----- RELATIONAL OPERATORS != -----" << std::endl;
	std::cout << "Comparsion (1,2,3,4,5) and (8,0,6,9,7,33,44,11,22) containers"
		<< std::endl;

	std::cout << "std_first != std_second: " << std::boolalpha
		<< (*int_sort_std != *int_unsort_std) << std::endl;
	std::cout << " ft_first !=  ft_second: " << std::boolalpha
		<< (*int_sort_ft != *int_unsort_ft) << std::endl;
	std::cout << std::endl;

	EXPECT_EQ((*int_sort_std != *int_unsort_std), 1);
	EXPECT_EQ((*int_sort_ft != *int_unsort_ft), 1);

	std::cout << "Comparsion (1,2,3,4,5) and (1,2,3,4,5) containers"
		<< std::endl;

	std::queue<int> ctnr_std;
	ft::Queue<int> ctnr_ft;

	ctnr_std.push(1);
	ctnr_std.push(2);
	ctnr_std.push(3);
	ctnr_std.push(4);
	ctnr_std.push(5);

	ctnr_ft.push(1);
	ctnr_ft.push(2);
	ctnr_ft.push(3);
	ctnr_ft.push(4);
	ctnr_ft.push(5);

	std::cout << "std_first != std_second: " << std::boolalpha
		<< (*int_sort_std != ctnr_std) << std::endl;
	std::cout << " ft_first !=  ft_second: " << std::boolalpha
		<< (*int_sort_ft != ctnr_ft) << std::endl;

	EXPECT_EQ((*int_sort_std != ctnr_std), 0);
	EXPECT_EQ((*int_sort_ft != ctnr_ft), 0);
}

TEST_F(Test_Queue, Relational_operators_Less) {
	std::cout << "----- RELATIONAL OPERATORS < -----" << std::endl;
	std::cout << "Comparsion (1,2,3,4,5) and (8,0,6,9,7,33,44,11,22) containers"
		<< std::endl;

	std::cout << "std_first < std_second: " << std::boolalpha
		<< (*int_sort_std < *int_unsort_std) << std::endl;
	std::cout << " ft_first <  ft_second: " << std::boolalpha
		<< (*int_sort_ft < *int_unsort_ft) << std::endl;
	std::cout << std::endl;

	EXPECT_EQ((*int_sort_std < *int_unsort_std), 1);
	EXPECT_EQ((*int_sort_ft < *int_unsort_ft), 1);

	std::cout << "Comparsion (1,2,3,4,5) and (1,2,3,4,5) containers"
		<< std::endl;

	std::queue<int> ctnr_std;
	ft::Queue<int> ctnr_ft;

	ctnr_std.push(1);
	ctnr_std.push(2);
	ctnr_std.push(3);
	ctnr_std.push(4);
	ctnr_std.push(5);

	ctnr_ft.push(1);
	ctnr_ft.push(2);
	ctnr_ft.push(3);
	ctnr_ft.push(4);
	ctnr_ft.push(5);

	std::cout << "std_first < std_second: " << std::boolalpha
		<< (*int_sort_std < ctnr_std) << std::endl;
	std::cout << " ft_first <  ft_second: " << std::boolalpha
		<< (*int_sort_ft < ctnr_ft) << std::endl;

	EXPECT_EQ((*int_sort_std < ctnr_std), 0);
	EXPECT_EQ((*int_sort_ft < ctnr_ft), 0);
}

TEST_F(Test_Queue, Relational_operators_Less_or_equal) {
	std::cout << "----- RELATIONAL OPERATORS <= -----" << std::endl;
	std::cout << "Comparsion (1,2,3,4,5) and (8,0,6,9,7,33,44,11,22) containers"
		<< std::endl;

	std::cout << "std_first <= std_second: " << std::boolalpha
		<< (*int_sort_std <= *int_unsort_std) << std::endl;
	std::cout << " ft_first <=  ft_second: " << std::boolalpha
		<< (*int_sort_ft <= *int_unsort_ft) << std::endl;
	std::cout << std::endl;

	EXPECT_EQ((*int_sort_std <= *int_unsort_std), 1);
	EXPECT_EQ((*int_sort_ft <= *int_unsort_ft), 1);

	std::cout << "Comparsion (1,2,3,4,5) and (1,2,3,4,5) containers"
		<< std::endl;

	std::queue<int> ctnr_std;
	ft::Queue<int> ctnr_ft;

	ctnr_std.push(1);
	ctnr_std.push(2);
	ctnr_std.push(3);
	ctnr_std.push(4);
	ctnr_std.push(5);

	ctnr_ft.push(1);
	ctnr_ft.push(2);
	ctnr_ft.push(3);
	ctnr_ft.push(4);
	ctnr_ft.push(5);

	std::cout << "std_first <= std_second: " << std::boolalpha
		<< (*int_sort_std <= ctnr_std) << std::endl;
	std::cout << " ft_first <=  ft_second: " << std::boolalpha
		<< (*int_sort_ft <= ctnr_ft) << std::endl;

	EXPECT_EQ((*int_sort_std <= ctnr_std), 1);
	EXPECT_EQ((*int_sort_ft <= ctnr_ft), 1);
}

TEST_F(Test_Queue, Relational_operators_More) {
	std::cout << "----- RELATIONAL OPERATORS > -----" << std::endl;
	std::cout << "Comparsion (1,2,3,4,5) and (8,0,6,9,7,33,44,11,22) containers"
		<< std::endl;

	std::cout << "std_first > std_second: " << std::boolalpha
		<< (*int_sort_std > *int_unsort_std) << std::endl;
	std::cout << " ft_first >  ft_second: " << std::boolalpha
		<< (*int_sort_ft > *int_unsort_ft) << std::endl;
	std::cout << std::endl;

	EXPECT_EQ((*int_sort_std > *int_unsort_std), 0);
	EXPECT_EQ((*int_sort_ft > *int_unsort_ft), 0);

	std::cout << "Comparsion (1,2,3,4,5) and (1,2,3,4,5) containers"
		<< std::endl;

	std::queue<int> ctnr_std;
	ft::Queue<int> ctnr_ft;

	ctnr_std.push(1);
	ctnr_std.push(2);
	ctnr_std.push(3);
	ctnr_std.push(4);
	ctnr_std.push(5);

	ctnr_ft.push(1);
	ctnr_ft.push(2);
	ctnr_ft.push(3);
	ctnr_ft.push(4);
	ctnr_ft.push(5);

	std::cout << "std_first > std_second: " << std::boolalpha
		<< (*int_sort_std > ctnr_std) << std::endl;
	std::cout << " ft_first >  ft_second: " << std::boolalpha
		<< (*int_sort_ft > ctnr_ft) << std::endl;

	EXPECT_EQ((*int_sort_std > ctnr_std), 0);
	EXPECT_EQ((*int_sort_ft > ctnr_ft), 0);
}

TEST_F(Test_Queue, Relational_operators_More_or_equal) {
	std::cout << "----- RELATIONAL OPERATORS >= -----" << std::endl;
	std::cout << "Comparsion (1,2,3,4,5) and (8,0,6,9,7,33,44,11,22) containers"
		<< std::endl;

	std::cout << "std_first >= std_second: " << std::boolalpha
		<< (*int_sort_std >= *int_unsort_std) << std::endl;
	std::cout << " ft_first >=  ft_second: " << std::boolalpha
		<< (*int_sort_ft >= *int_unsort_ft) << std::endl;
	std::cout << std::endl;

	EXPECT_EQ((*int_sort_std >= *int_unsort_std), 0);
	EXPECT_EQ((*int_sort_ft >= *int_unsort_ft), 0);

	std::cout << "Comparsion (1,2,3,4,5) and (1,2,3,4,5) containers"
		<< std::endl;

	std::queue<int> ctnr_std;
	ft::Queue<int> ctnr_ft;

	ctnr_std.push(1);
	ctnr_std.push(2);
	ctnr_std.push(3);
	ctnr_std.push(4);
	ctnr_std.push(5);

	ctnr_ft.push(1);
	ctnr_ft.push(2);
	ctnr_ft.push(3);
	ctnr_ft.push(4);
	ctnr_ft.push(5);

	std::cout << "std_first >= std_second: " << std::boolalpha
		<< (*int_sort_std >= ctnr_std) << std::endl;
	std::cout << " ft_first >=  ft_second: " << std::boolalpha
		<< (*int_sort_ft >= ctnr_ft) << std::endl;

	EXPECT_EQ((*int_sort_std >= ctnr_std), 1);
	EXPECT_EQ((*int_sort_ft >= ctnr_ft), 1);
}
