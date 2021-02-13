/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:13:24 by awerebea          #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_QUEUE_HPP
#define FT_QUEUE_HPP

#include <iostream>
#include <deque>
#include <limits>

namespace ft {

	template <class T, class Container = std::deque<T> > class Queue;

	/* Relational operators */

	template <class T, class Container>
	bool operator==(const Queue<T, Container>& lhs,
											const Queue<T, Container>& rhs) {
		return lhs.ctnr == rhs.ctnr;
	}

	template <class T, class Container>
	bool operator!=(const Queue<T, Container>& lhs,
											const Queue<T, Container>& rhs) {
		return lhs.ctnr != rhs.ctnr;
	}

	template <class T, class Container>
	bool operator<(const Queue<T, Container>& lhs,
											const Queue<T, Container>& rhs) {
		return lhs.ctnr < rhs.ctnr;
	}

	template <class T, class Container>
	bool operator<=(const Queue<T, Container>& lhs,
											const Queue<T, Container>& rhs) {
		return lhs.ctnr <= rhs.ctnr;
	}

	template <class T, class Container>
	bool operator>(const Queue<T, Container>& lhs,
											const Queue<T, Container>& rhs) {
		return lhs.ctnr > rhs.ctnr;
	}

	template <class T, class Container>
	bool operator>=(const Queue<T, Container>& lhs,
											const Queue<T, Container>& rhs) {
		return lhs.ctnr >= rhs.ctnr;
	}

	template <class T, class Container> class Queue {

		public:

		typedef		T				value_type;
		typedef		Container		container_type;
		typedef		std::size_t		size_type;

		private:

		container_type	ctnr;

		public:

		explicit	Queue(const container_type& ctnr = container_type())
			: ctnr(ctnr) {}

					~Queue() {}

		bool				empty() const { return ctnr.empty(); }

		size_type			size() const { return ctnr.size(); }

		value_type&			front() { return ctnr.front(); }

		const value_type&	front() const { return ctnr.front(); }

		value_type&			back() { return ctnr.back(); }

		const value_type&	back() const { return ctnr.back(); }

		void				push(const value_type& val) { ctnr.push_back(val); }

		void				pop() { ctnr.pop_front(); }

		friend bool operator== <>(const Queue<T, Container>& lhs,
												const Queue<T, Container>& rhs);

		friend bool operator!= <>(const Queue<T, Container>& lhs,
												const Queue<T, Container>& rhs);

		friend bool operator< <>(const Queue<T, Container>& lhs,
												const Queue<T, Container>& rhs);

		friend bool operator<= <>(const Queue<T, Container>& lhs,
												const Queue<T, Container>& rhs);

		friend bool operator> <>(const Queue<T, Container>& lhs,
												const Queue<T, Container>& rhs);

		friend bool operator>= <>(const Queue<T, Container>& lhs,
												const Queue<T, Container>& rhs);

	}; // class Queue

} // namespace ft

#endif //FT_CONTAINERS_FT_QUEUE_HPP
