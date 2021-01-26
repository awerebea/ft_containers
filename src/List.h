/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:47:36 by awerebea          #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
#define FT_LIST_H

#include <iostream>

namespace ft {
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
			value_type *	data;
			s_node *		prev;
			s_node *		next;
		}				t_node;

		typedef typename allocator_type::template rebind<t_node>::other
																node_allocator;

		size_type		size;
		t_node *		end_node;
		node_allocator	alloc_rebind;
		allocator_type	alloc;

		void			end_node_init() {
			end_node = alloc_rebind.allocate(1);
			end_node->data = alloc.allocate(1);
			alloc.construct(end_node->data, value_type());
			end_node->next = end_node;
			end_node->prev = end_node;
			size = 0;
		}

		t_node *		new_node_init(const value_type& val) {
			t_node * new_node = alloc_rebind.allocate(1);
			new_node->data = alloc.allocate(1);
			alloc.construct(new_node->data, val);
			size += 1;
			return new_node;
		}

	public:

		/*
		* Iterators
		*/

		class const_iterator;

		class iterator : public std::bidirectional_iterator_tag {
			t_node *	node;
		public:
			iterator(): node(NULL) {}

			explicit iterator(t_node * node): node(node) {}

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

			value_type&		operator*() const {
				return *node->data;
			};

			value_type *		operator->() const {
				return node->data;
			};

			iterator&			operator++() {
				node = node->next;
				return *this;
			};

			iterator			operator++(int) {
				iterator	ret = *this;
				node = node->next;
				return ret;
			};

			iterator&			operator--() {
				node = node->prev;
				return *this;
			};

			iterator			operator--(int) {
				iterator	ret = *this;
				node = node->prev;
				return ret;
			};

			t_node *			getNode() const { return node; }
		}; // class iterator

		class const_iterator : public std::bidirectional_iterator_tag {
			t_node *	node;
		public:
			const_iterator(): node(NULL) {}

			explicit const_iterator(t_node * node): node(node) {}

			const_iterator(const const_iterator& other) { *this = other; }

			~const_iterator() {}

			const_iterator&	operator=(const const_iterator& other) {
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

			const value_type&	operator*() const {
				return *node->data;
			};

			const value_type *	operator->() const {
				return node->data;
			};

			const_iterator&	operator++() {
				node = node->next;
				return *this;
			};

			const_iterator		operator++(int) {
				const_iterator	ret = *this;
				node = node->next;
				return ret;
			};

			const_iterator&	operator--() {
				node = node->prev;
				return *this;
			};

			const_iterator		operator--(int) {
				const_iterator	ret = *this;
				node = node->prev;
				return ret;
			};

			t_node *			getNode() const { return node; }
		}; // class const_iterator

		/*
		* Constructors:
		*/

		/* default (1) */
		explicit	List(const allocator_type& alloc = allocator_type()) {
			end_node_init();
		}

		/* fill (2) */
		explicit	List(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()) {
			end_node_init();
			for (size_type i = 0; i < n; ++i) {
				push_back(val);
			}
		}

		/* range (3) */
		// template <class InputIterator>
		//                     List (InputIterator first, InputIterator last,
		//                     const allocator_type& alloc = allocator_type());

		/* copy (4) */
					List(const List& other) { *this = other; }

					~List() {
						clear();
						alloc.destroy(end_node->data);
						alloc.deallocate(end_node->data, 1);
						alloc_rebind.deallocate(end_node, 1);
					}

		List&				operator=(const List& other) {
			if (this == &other) { return *this; }
			clear();
			t_node * curr_this = end_node->next;
			t_node * curr_other = other.end_node->next;
			for (size_type i = 0; i < other.size; ++i) {
				push_back(*curr_other->data);
				curr_this = curr_this->next;
				curr_other = curr_other->next;
			}
			return *this;
		}

		/*
		* Iterators
		*/

		iterator	begin() { return iterator(end_node->next); }

		iterator	end() { return iterator(end_node); }

		/*
		* Modifiers
		*/

		void		push_back(const value_type &val) {
			t_node * tmp = end_node->prev;
			t_node * new_node = new_node_init(val);
			new_node->prev = end_node->prev;
			new_node->next = end_node;
			tmp->next = new_node;
			end_node->prev = new_node;
		}

		void		push_front(const value_type &val) {
			t_node * tmp = end_node->next;
			t_node * new_node = new_node_init(val);
			new_node->prev = end_node;
			new_node->next = end_node->next;
			tmp->prev = new_node;
			end_node->next = new_node;
		}

		void		clear() {
			t_node * tmp;
			for (; size > 0; --size) {
				tmp = end_node->next->next;
				alloc.destroy(end_node->next->data);
				alloc.deallocate(end_node->next->data, 1);
				alloc_rebind.deallocate(end_node->next, 1);
				end_node->next = tmp;
			}
			end_node->prev = end_node;
		}

	}; // class List
} // namespace ft

#endif //FT_CONTAINERS_FT_LIST_H
