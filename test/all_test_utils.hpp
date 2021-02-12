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
void compare_content(S& std, F& ft, const std::string& txt = "") {
	std::cout << "std" << txt << ":"; print_container(std);
	std::cout << " ft" << txt << ":"; print_container(ft);
}

template <typename S, typename F>
void compare_capacity(const S& std, const F& ft, const std::string& txt = "") {
	std::cout << "std" << txt << " (capacity): " << std.capacity() << std::endl;
	std::cout << " ft" << txt << " (capacity): " << ft.capacity() << std::endl;
}

template <typename S, typename F>
void compare_iterators(const S& std, const F& ft, const std::string& txt = "") {
	std::cout << "std" << txt << " (iterator): " << *std << std::endl;
	std::cout << " ft" << txt << " (iterator): " << *ft << std::endl;
}

template <typename S, typename F>
void compare_elements(const S& std, const F& ft, const std::string& txt = "") {
	std::cout << "std" << txt << " (element value): " << std << std::endl;
	std::cout << " ft" << txt << " (element value): " << ft << std::endl;
}

template <typename S, typename F>
void compare_size(const S& std, const F& ft, const std::string& txt = "") {
	std::cout << "std" << txt << " (size): " << std.size() << std::endl;
	std::cout << " ft" << txt << " (size): " << ft.size() << std::endl;
}





template <typename T>
void print_container_pair(T& obj) {
	for (typename T::iterator it = obj.begin(); it != obj.end(); ++it) {
		std::cout << " " << it->first << " (" << it->second << ")";
	}
	std::cout << std::endl;
}

template <typename S, typename F>
void compare_content_pair(S& std, F& ft, const std::string& txt = "") {
	std::cout << "std" << txt << ":"; print_container_pair(std);
	std::cout << " ft" << txt << ":"; print_container_pair(ft);
}

template <typename S, typename F>
void compare_iterators_pair(const S& std, const F& ft,
							const std::string& txt = "") {
	std::cout << "std" << txt << " (iterator): " << *std->first
		<< " (" << *std->second << ")" << std::endl;
	std::cout << " ft" << txt << " (iterator): k: " << *ft->first
		<< " (" << *ft->second << ")" << std::endl;
}

#endif //FT_CONTAINERS_ALL_TEST_UTILS_HPP
