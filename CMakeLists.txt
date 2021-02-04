cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(googletest)

include_directories(googletest/googletest/include
        src
        test
        )

set(SOURCE_FILES
        test/test_list.cpp
        test/test_vector.cpp
        )

add_executable(ft_containers ${SOURCE_FILES})

target_link_libraries(ft_containers gtest gtest_main)
