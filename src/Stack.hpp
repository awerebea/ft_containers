/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:38:25 by awerebea          #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include <iostream>
#include <deque>
#include <limits>

namespace ft {

	template <class T, class Container = std::deque<T> > class Stack;

	/* Relational operators */

	template <class T, class Container>
	bool operator==(const Stack<T, Container>& lhs,
											const Stack<T, Container>& rhs) {
		return lhs.ctnr == rhs.ctnr;
	}

	template <class T, class Container>
	bool operator!=(const Stack<T, Container>& lhs,
											const Stack<T, Container>& rhs) {
		return lhs.ctnr != rhs.ctnr;
	}

	template <class T, class Container>
	bool operator<(const Stack<T, Container>& lhs,
											const Stack<T, Container>& rhs) {
		return lhs.ctnr < rhs.ctnr;
	}

	template <class T, class Container>
	bool operator<=(const Stack<T, Container>& lhs,
											const Stack<T, Container>& rhs) {
		return lhs.ctnr <= rhs.ctnr;
	}

	template <class T, class Container>
	bool operator>(const Stack<T, Container>& lhs,
											const Stack<T, Container>& rhs) {
		return lhs.ctnr > rhs.ctnr;
	}

	template <class T, class Container>
	bool operator>=(const Stack<T, Container>& lhs,
											const Stack<T, Container>& rhs) {
		return lhs.ctnr >= rhs.ctnr;
	}

	template <class T, class Container> class Stack {

		public:

		typedef		T				value_type;
		typedef		Container		container_type;
		typedef		std::size_t		size_type;

		private:

		container_type	ctnr;

		public:

		explicit	Stack(const container_type& ctnr = container_type())
			: ctnr(ctnr) {}

					~Stack() {}

		bool				empty() const { return ctnr.empty(); }

		size_type			size() const { return ctnr.size(); }

		value_type&			top() { return ctnr.back(); }

		const value_type&	top() const { return ctnr.back(); }

		void				push(const value_type& val) { ctnr.push_back(val); }

		void				pop() { ctnr.pop_back(); }

		friend bool operator== <>(const Stack<T, Container>& lhs,
												const Stack<T, Container>& rhs);

		friend bool operator!= <>(const Stack<T, Container>& lhs,
												const Stack<T, Container>& rhs);

		friend bool operator< <>(const Stack<T, Container>& lhs,
												const Stack<T, Container>& rhs);

		friend bool operator<= <>(const Stack<T, Container>& lhs,
												const Stack<T, Container>& rhs);

		friend bool operator> <>(const Stack<T, Container>& lhs,
												const Stack<T, Container>& rhs);

		friend bool operator>= <>(const Stack<T, Container>& lhs,
												const Stack<T, Container>& rhs);

	}; // class Stack

} // namespace ft

#endif //FT_CONTAINERS_FT_STACK_HPP
