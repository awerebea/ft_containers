# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/13 21:40:29 by awerebea          #+#    #+#              #
#                                                     ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# A sample Makefile for building Google Test and using it in user
# tests.  Please tweak it to suit your environment and project.  You
# may want to move it to your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.

# Please tweak the following variable definitions as needed by your
# project, except GTEST_HEADERS, which you can use in your own targets
# but shouldn't modify.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR=googletest/googletest

# Where to find user code.
USER_DIR=test

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -Werror -pthread

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = ft_containers

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS =	$(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

HEADERS = -I src/ -I test/

all : $(TESTS)

clean:
	rm -f	gtest_main.a gtest.a *.o

fclean:	clean
	rm -f	$(TESTS)
	rm -f	test_list
	rm -f	test_vector
	rm -f	test_map
	rm -f	test_queue
	rm -f	test_stack
	rm -f	test_set

run_all: all
	./$(TESTS)

test_valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(TESTS)

re:	fclean all

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
	$(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
	$(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

test_list.o : $(USER_DIR)/test_list.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(HEADERS) $(CXXFLAGS) -c $(USER_DIR)/test_list.cpp

test_list : test_list.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(HEADERS) $(CXXFLAGS) -lpthread $^ -o $@
	./test_list

test_vector.o : $(USER_DIR)/test_vector.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(HEADERS) $(CXXFLAGS) -c $(USER_DIR)/test_vector.cpp

test_vector : test_vector.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(HEADERS) $(CXXFLAGS) -lpthread $^ -o $@
	./test_vector

test_map.o : $(USER_DIR)/test_map.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(HEADERS) $(CXXFLAGS) -c $(USER_DIR)/test_map.cpp

test_map : test_map.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(HEADERS) $(CXXFLAGS) -lpthread $^ -o $@
	./test_map

test_queue.o : $(USER_DIR)/test_queue.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(HEADERS) $(CXXFLAGS) -c $(USER_DIR)/test_queue.cpp

test_queue : test_queue.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(HEADERS) $(CXXFLAGS) -lpthread $^ -o $@
	./test_queue

test_stack.o : $(USER_DIR)/test_stack.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(HEADERS) $(CXXFLAGS) -c $(USER_DIR)/test_stack.cpp

test_stack : test_stack.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(HEADERS) $(CXXFLAGS) -lpthread $^ -o $@
	./test_stack

test_set.o : $(USER_DIR)/test_set.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(HEADERS) $(CXXFLAGS) -c $(USER_DIR)/test_set.cpp

test_set : test_set.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(HEADERS) $(CXXFLAGS) -lpthread $^ -o $@
	./test_set

$(TESTS) :	test_list.o test_vector.o test_map.o test_queue.o test_stack.o \
			gtest_main.a
	$(CXX) $(CPPFLAGS) $(HEADERS) $(CXXFLAGS) -lpthread $^ -o $@

.PHONY:	all \
		clean \
		debug \
		fclean \
		re \
		run \
		test_valgrind
