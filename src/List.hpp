/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:47:36 by awerebea          #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_HPP
#define FT_LIST_HPP

#include <iostream>
#include <limits>

namespace ft {

#ifdef __APPLE__
	template <bool, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> { typedef T type; };
#endif

	template <class T, class Alloc = std::allocator<T> > class List {
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef std::ptrdiff_t								difference_type;
		typedef std::size_t									size_type;

	private:
		typedef struct	s_node {
			pointer			data;
			s_node*			prev;
			s_node*			next;
		}				t_node;

		typedef typename allocator_type::template rebind<t_node>::other
																node_allocator;

		size_type		m_size;
		t_node*			end_node;
		node_allocator	alloc_rebind;
		allocator_type	alloc;

		void			end_node_init() {
			end_node = alloc_rebind.allocate(1);
			end_node->data = alloc.allocate(1);
			alloc.construct(end_node->data, value_type());
			end_node->next = end_node;
			end_node->prev = end_node;
			m_size = 0;
		}

		t_node*			new_node_init(const value_type& val) {
			t_node* new_node = alloc_rebind.allocate(1);
			new_node->data = alloc.allocate(1);
			alloc.construct(new_node->data, val);
			m_size += 1;
			return new_node;
		}

		void			del_node(t_node* node) {
			alloc.destroy(node->data);
			alloc.deallocate(node->data, 1);
			alloc_rebind.deallocate(node, 1);
			m_size = m_size - 1;
		}

		void			swap_with_prev(t_node* node) {
			t_node* new_prev = NULL;
			t_node* new_next = NULL;
			new_next = node->prev;
			node->prev->next = node->next;
			node->next->prev = new_next;
			new_prev = node->prev->prev;
			node->prev->prev = node;
			node->prev = new_prev;
			node->prev->next = node;
			node->next = new_next;
		}

	public:

		/* Iterators */

		class const_iterator;

		class iterator :
			public std::iterator<std:: bidirectional_iterator_tag, value_type> {
			t_node* node;
		public:
			iterator(): node(NULL) {}

			explicit iterator(t_node* node): node(node) {}

			iterator(const iterator& other) { *this = other; }

			~iterator() {}

			iterator&			operator=(const iterator& other) {
				if (this != &other) { node = other.node; }
				return *this;
			}

			bool				operator==(const iterator& other) const {
				return node == other.node;
			};

			bool				operator==(const const_iterator& other) const {
				return node == other.getNode();
			};

			bool				operator!=(const iterator& other) const {
				return node != other.node;
			};

			bool				operator!=(const const_iterator& other) const {
				return node != other.getNode();
			};

			reference			operator*() const {
				return *node->data;
			};

			pointer				operator->() const {
				return node->data;
			};

			iterator&			operator++() {
				node = node->next;
				return *this;
			};

			iterator			operator++(int) {
				iterator ret = *this;
				node = node->next;
				return ret;
			};

			iterator&			operator--() {
				node = node->prev;
				return *this;
			};

			iterator			operator--(int) {
				iterator ret = *this;
				node = node->prev;
				return ret;
			};

			t_node*				getNode() const { return node; }
		}; // class iterator

		class const_iterator :
			public std::iterator<std:: bidirectional_iterator_tag, value_type> {
			t_node* node;
		public:
			const_iterator(): node(NULL) {}

			explicit const_iterator(t_node* node): node(node) {}

			const_iterator(const const_iterator& other) { *this = other; }

			~const_iterator() {}

			const_iterator&		operator=(const const_iterator& other) {
				if (this != &other) { node = other.node; }
				return *this;
			}

			bool				operator==(const const_iterator& other) const {
				return node == other.node;
			};

			bool				operator==(const iterator& other) const {
				return node == other.getNode();
			};

			bool				operator!=(const const_iterator& other) const {
				return node != other.node;
			};

			bool				operator!=(const iterator& other) const {
				return node != other.getNode();
			};

			const_reference		operator*() const {
				return *node->data;
			};

			const_pointer		operator->() const {
				return node->data;
			};

			const_iterator&		operator++() {
				node = node->next;
				return *this;
			};

			const_iterator		operator++(int) {
				const_iterator ret = *this;
				node = node->next;
				return ret;
			};

			const_iterator&		operator--() {
				node = node->prev;
				return *this;
			};

			const_iterator		operator--(int) {
				const_iterator ret = *this;
				node = node->prev;
				return ret;
			};

			t_node*				getNode() const { return node; }
		}; // class const_iterator

		class const_reverse_iterator;

		class reverse_iterator :
			public std::iterator<std:: bidirectional_iterator_tag, value_type> {
			t_node* node;
		public:
			reverse_iterator(): node(NULL) {}

			explicit reverse_iterator(t_node* node): node(node) {}

			reverse_iterator(const reverse_iterator& other) { *this = other; }

			~reverse_iterator() {}

			reverse_iterator&	operator=(const reverse_iterator& other) {
				if (this != &other) { node = other.node; }
				return *this;
			}

			bool		operator==(const reverse_iterator& other) const {
				return node == other.node;
			};

			bool		operator==(const const_reverse_iterator& other) const {
				return node == other.getNode();
			};

			bool		operator!=(const reverse_iterator& other) const {
				return node != other.node;
			};

			bool		operator!=(const const_reverse_iterator& other) const {
				return node != other.getNode();
			};

			reference			operator*() const {
				return *node->data;
			};

			pointer				operator->() const {
				return node->data;
			};

			reverse_iterator&	operator++() {
				node = node->prev;
				return *this;
			};

			reverse_iterator	operator++(int) {
				reverse_iterator ret = *this;
				node = node->prev;
				return ret;
			};

			reverse_iterator&	operator--() {
				node = node->next;
				return *this;
			};

			reverse_iterator	operator--(int) {
				reverse_iterator ret = *this;
				node = node->next;
				return ret;
			};

			t_node*				getNode() const { return node; }
		}; // class reverse_iterator

		class const_reverse_iterator :
			public std::iterator<std:: bidirectional_iterator_tag, value_type> {
			t_node* node;
		public:
			const_reverse_iterator(): node(NULL) {}

			explicit const_reverse_iterator(t_node* node): node(node) {}

			const_reverse_iterator(const const_reverse_iterator& other)
			{ *this = other; }

			~const_reverse_iterator() {}

			const_reverse_iterator&	operator=(const const_reverse_iterator&
																		other) {
				if (this != &other) { node = other.node; }
				return *this;
			}

			bool		operator==(const const_reverse_iterator& other) const {
				return node == other.node;
			};

			bool		operator==(const reverse_iterator& other) const {
				return node == other.getNode();
			};

			bool		operator!=(const const_reverse_iterator& other) const {
				return node != other.node;
			};

			bool		operator!=(const reverse_iterator& other)
				const {
				return node != other.getNode();
			};

			const_reference			operator*() const {
				return *node->data;
			};

			const_pointer			operator->() const {
				return node->data;
			};

			const_reverse_iterator&	operator++() {
				node = node->prev;
				return *this;
			};

			const_reverse_iterator	operator++(int) {
				const_reverse_iterator ret = *this;
				node = node->prev;
				return ret;
			};

			const_reverse_iterator&	operator--() {
				node = node->next;
				return *this;
			};

			const_reverse_iterator	operator--(int) {
				const_reverse_iterator ret = *this;
				node = node->next;
				return ret;
			}; // class const_reverse_iterator

			t_node*		getNode() const { return node; }
		}; // class const_reverse_iterator

		/* Constructors: */

		/* default (1) */
		explicit	List(const allocator_type& alloc = allocator_type())
							: alloc(alloc) {
			end_node_init();
		}

		/* fill (2) */
		explicit	List(size_type n, const_reference val = value_type(),
						const allocator_type& alloc = allocator_type())
							: alloc(alloc) {
			end_node_init();
			for (size_type i = 0; i < n; ++i) {
				insert(end(), val);
			}
		}

		/* range (3) */
#ifdef __APPLE__
		template <class InputIterator>
		List(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<std::__is_input_iterator<InputIterator>::
				value>::type* = 0)
#elif __linux__
		List(iterator first, iterator last,
				const allocator_type& alloc = allocator_type())
#endif
		: alloc(alloc)
		{
			end_node_init();
			while (first != last) { insert(end(), *first++); }
		}

#ifdef __linux__
		List(reverse_iterator first, reverse_iterator last,
				const allocator_type& alloc = allocator_type()) : alloc(alloc) {
			end_node_init();
			while (first != last) { insert(end(), *first++); }
		}
#endif

		/* copy (4) */
		List(const List& other) {
			end_node_init();
			*this = other;
		}

		~List() {
			clear();
			alloc.destroy(end_node->data);
			alloc.deallocate(end_node->data, 1);
			alloc_rebind.deallocate(end_node, 1);
		}

		List&			operator=(const List& other) {
			if (this == &other) { return *this; }
			assign(other.begin(), other.end());
			return *this;
		}

		/* Iterators */

		iterator		begin() { return iterator(end_node->next); }

		const_iterator	begin() const { return const_iterator(end_node->next); }

		iterator		end() { return iterator(end_node); }

		const_iterator	end() const { return const_iterator(end_node); }

		reverse_iterator		rbegin() {
			return reverse_iterator(end_node->prev);
		}

		const_reverse_iterator	rbegin() const {
			return const_reverse_iterator(end_node->prev);
		}

		reverse_iterator		rend() {
			return reverse_iterator(end_node);
		}

		const_reverse_iterator	rend() const {
			return const_reverse_iterator(end_node);
		}

		/* Capacity */

		bool			empty() const { return m_size == 0; }

		size_type		size() const { return m_size; }

		size_type		max_size(void) const {
			return node_allocator().max_size();
		}

		/* Element access */

		reference		front() { return *begin(); }

		const_reference	front() const { return *begin(); }

		reference		back() { return *(--end()); }

		const_reference	back() const { return *(--end()); }

		/* Modifiers */

#ifdef __APPLE__
		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last,
				typename ft::enable_if<std::__is_input_iterator<InputIterator>::
				value>::type* = 0)
#elif __linux__
		void	assign(iterator first, iterator last)
#endif
		{
			if (m_size) { clear(); }
			while (first != last) { insert(end(), *first++); }
		}

#ifdef __linux__
		void	assign(const_iterator first, const_iterator last) {
			if (m_size) { clear(); }
			while (first != last) { insert(end(), *first++); }
		}
#endif

		void		assign(size_type n, const value_type& val) {
			if (m_size) { clear(); }
			for (size_type i = 0; i < n; ++i) { insert(end(), val); }
		}

		void		push_front(const value_type &val) { insert(begin(), val); }

		void		pop_front() { erase(begin()); }

		void		push_back(const value_type &val) { insert(end(), val); }

		void		pop_back() { erase(--end()); }

		iterator	insert(iterator position, const value_type& val) {
			t_node* tmp = position.getNode();
			t_node* new_node = new_node_init(val);
			tmp->prev->next = new_node;
			new_node->prev = tmp->prev;
			tmp->prev = new_node;
			new_node->next = tmp;
			return iterator(new_node);
		}

		void	insert(iterator position, size_type n, const value_type& val) {
			for (size_type i = 0; i < n; ++i) { insert(position, val); }
		}

#ifdef __APPLE__
		template <class InputIterator>
		void	insert(iterator position,
				InputIterator first, InputIterator last,
				typename ft::enable_if<std::__is_input_iterator<InputIterator>::
				value>::type* = 0)
#elif __linux__
		void	insert(iterator position, iterator first, iterator last)
#endif
		{
			while (first != last) { insert(position, *first++); }
		}

#ifdef __linux__
		void	insert(reverse_iterator position, reverse_iterator first,
																iterator last) {
			while (first != last) { insert(position, *first++); }
		}
#endif

		iterator		erase(iterator position) {
			t_node* tmp = position.getNode();
			iterator ret = ++position;
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			del_node(tmp);
			return ret;
		}

		iterator		erase(iterator first, iterator last) {
			iterator ret = first;
			while (first != last) { ret = erase(first++); }
			return ret;
		}

		const_iterator	erase(const_iterator position) {
			t_node* tmp = position.getNode();
			const_iterator ret = ++position;
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			del_node(tmp);
			return ret;
		}

		const_iterator	erase(const_iterator first, const_iterator last) {
			const_iterator ret = first;
			while (first != last) { ret = erase(first++); }
			return ret;
		}

		void			swap(List& other) {
			t_node*	tmp_node = other.end_node;
			other.end_node = this->end_node;
			this->end_node = tmp_node;

			size_type	tmp_size = other.m_size;
			other.m_size = this->m_size;
			this->m_size = tmp_size;
		}

		void			resize(size_type n, value_type val = value_type()) {
			while (m_size < n) { insert(end(), val); }
			while (m_size > n) { erase(--end()); }
		}

		void			clear() {
			t_node* tmp;
			for ( ; m_size > 0; ) {
				tmp = end_node->next->next;
				del_node(end_node->next);
				end_node->next = tmp;
			}
			end_node->prev = end_node;
		}

		/* Operations */

		void			splice(iterator position, List& other) {
			splice(position, other, other.begin(), other.end());
		}

		void			splice(iterator position, List& other, iterator i) {
			if (other.m_size) {
				t_node* pos_node = position.getNode();
				t_node* other_node = i.getNode();
				other_node->prev->next = other_node->next;
				other_node->next->prev = other_node->prev;

				pos_node->prev->next = other_node;
				other_node->prev = pos_node->prev;
				pos_node->prev = other_node;
				other_node->next = pos_node;
				other.m_size--;
				m_size++;
			}
		}

		void			splice(iterator position, List& other,
											iterator first, iterator last) {
			for (iterator it = first; it != last; ) {
				splice(position, other, it++);
			}
		}

		void			remove(const value_type& val) {
			for (iterator it = begin(); it != end(); ) {
				if (*it == val) { erase(it); }
				++it;
			}
		}

		template <class Predicate>
		void			remove_if(Predicate pred) {
			for (iterator it = begin(); it != end(); ) {
				if ((*pred)(*it)) { erase(it); }
				++it;
			}
		}

		void			unique() {
			iterator it_prev = begin();
			for (iterator it = ++begin(); it != end(); ) {
				if (*it == *it_prev) { erase(it); }
				else { ++it_prev; }
				++it;
			}
		}

		template <class BinaryPredicate>
		void			unique(BinaryPredicate binary_pred) {
			iterator it_prev = begin();
			for (iterator it = ++begin(); it != end(); ) {
				if ((*binary_pred)(*it, *it_prev)) { erase(it); }
				else { ++it_prev; }
				++it;
			}
		}

		void			merge(List& other) {
			if (this == &other) { return ; }
			iterator it_other = other.begin();
			if (it_other == other.end()) { return ; };
			for (iterator it = begin(); it != end(); ) {
				if (*it_other < *it) {
					splice(it, other, it_other++);
					if (it_other == other.end()) { return ; };
				}
				else { ++it; }
			}
			splice(end(), other, it_other, other.end());
		}

		template <class Compare>
		void			merge(List& other, Compare comp) {
			if (this == &other) { return ; }
			iterator it_other = other.begin();
			for (iterator it = begin(); it != end(); ) {
				if ((*comp)(*it_other, *it)) {
					splice(it, other, it_other++);
					if (it_other == other.end()) { return ; };
				}
				else { ++it; }
			}
			splice(end(), other, it_other, other.end());
		}

		void			sort() { // INFO bubble sort used
			if (m_size < 2) { return ; }
			size_type is_changed = 1;
			iterator it_first;
			iterator it_second;
			iterator it_stop = end();
			while (it_stop != begin()) {
				if (!is_changed) { return ; }
				is_changed = 0;
				it_second = begin();
				while (it_second != it_stop) {
					it_first = it_second++;
					if (it_second == it_stop) { break ; }
					if (*it_second < *it_first) {
						swap_with_prev(it_second.getNode());
						is_changed = 1;
					}
				}
				--it_stop;
			}
		}

		template <class Compare>
		void			sort(Compare comp) { // INFO bubble sort used
			if (m_size < 2) { return ; }
			size_type is_changed = 1;
			iterator it_first;
			iterator it_second;
			iterator it_stop = end();
			while (it_stop != begin()) {
				if (!is_changed) { return ; }
				is_changed = 0;
				it_second = begin();
				while (it_second != it_stop) {
					it_first = it_second++;
					if (it_second == it_stop) { break ; }
					if ((*comp)(*it_second, *it_first)) {
						swap_with_prev(it_second.getNode());
						is_changed = 1;
					}
				}
				--it_stop;
			}
		}

		void			reverse() {
			if (m_size < 2) { return ; }
			iterator it;
			iterator it_stop = end();
			while (it_stop != begin()) {
				it = begin();
				while (++it != it_stop) {
					swap_with_prev(it.getNode());
					++it;
				}
				--it_stop;
			}
		}

	}; // class List

	template <class T, class Alloc>
	void	swap(List<T,Alloc>& x, List<T,Alloc>& y) {
		x.swap(y);
	}

	/* Relational operators */

	template <class T, class Alloc>
	bool	operator==(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size()) {
			return false;
		}
		typename List<T,Alloc>::const_iterator it_lhs = lhs.begin();
		typename List<T,Alloc>::const_iterator it_rhs = rhs.begin();
		for ( ; it_lhs != lhs.end(); ) {
			if (*it_lhs++ != *it_rhs++) { return false; }
		}
		return true;
	}

	template <class T, class Alloc>
	bool	operator!=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1) { return false; }
			else if (*first1 < *first2) { return true; }
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <class T, class Alloc>
	bool	operator<(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
					rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool	operator<=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}

} // namespace ft

#endif //FT_CONTAINERS_FT_LIST_HPP
