/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_test_utils.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:15:02 by awerebea          #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_ALL_TEST_UTILS_HPP
#define FT_CONTAINERS_ALL_TEST_UTILS_HPP

#include <iostream>

template <typename T>
void print_container(T& obj) {
	for (typename T::iterator it = obj.begin(); it != obj.end(); ++it) {
		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

template <typename S, typename F>
void compare_content(S& std, F& ft, const std::string& text = "") {
	std::cout << "std" << text << ":"; print_container(std);
	std::cout << " ft" << text << ":"; print_container(ft);
}

template <typename S, typename F>
void compare_capacity(const S& std, const F& ft, const std::string& text = "") {
	std::cout << "std" << text << " (capacity): " << std.capacity() << std::endl;
	std::cout << " ft" << text << " (capacity): " << ft.capacity() << std::endl;
}

template <typename S, typename F>
void compare_size(const S& std, const F& ft, const std::string& text = "") {
	std::cout << "std" << text << " (size): " << std.size() << std::endl;
	std::cout << " ft" << text << " (size): " << ft.size() << std::endl;
}

#endif //FT_CONTAINERS_ALL_TEST_UTILS_HPP
