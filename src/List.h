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
# include <limits>

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

		size_type		m_size;
		t_node *		end_node;
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

		t_node *		new_node_init(const value_type& val) {
			t_node * new_node = alloc_rebind.allocate(1);
			new_node->data = alloc.allocate(1);
			alloc.construct(new_node->data, val);
			m_size += 1;
			return new_node;
		}

		void			del_node(t_node * node) {
			alloc.destroy(node->data);
			alloc.deallocate(node->data, 1);
			alloc_rebind.deallocate(node, 1);
			m_size = m_size - 1;
		}

	public:

		/* Iterators */

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

		class const_reverse_iterator;

		class reverse_iterator : public std::bidirectional_iterator_tag {
			t_node *	node;
		public:
			reverse_iterator(): node(NULL) {}

			explicit reverse_iterator(t_node * node): node(node) {}

			reverse_iterator(const reverse_iterator& other) { *this = other; }

			~reverse_iterator() {}

			reverse_iterator&		operator=(const reverse_iterator& other) {
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

			value_type&	operator*() const {
				return *node->data;
			};

			value_type *			operator->() const {
				return node->data;
			};

			reverse_iterator&		operator++() {
				node = node->prev;
				return *this;
			};

			reverse_iterator		operator++(int) {
				reverse_iterator	ret = *this;
				node = node->prev;
				return ret;
			};

			reverse_iterator&		operator--() {
				node = node->next;
				return *this;
			};

			reverse_iterator		operator--(int) {
				reverse_iterator	ret = *this;
				node = node->next;
				return ret;
			};

			t_node *	getNode() const { return node; }
		}; // class reverse_iterator

		class const_reverse_iterator : public std::bidirectional_iterator_tag {
			t_node *	node;
		public:
			const_reverse_iterator(): node(NULL) {}

			explicit const_reverse_iterator(t_node * node): node(node) {}

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

			const value_type&		operator*() const {
				return *node->data;
			};

			const value_type *		operator->() const {
				return node->data;
			};

			const_reverse_iterator&	operator++() {
				node = node->prev;
				return *this;
			};

			const_reverse_iterator	operator++(int) {
				const_reverse_iterator	ret = *this;
				node = node->prev;
				return ret;
			};

			const_reverse_iterator&	operator--() {
				node = node->next;
				return *this;
			};

			const_reverse_iterator	operator--(int) {
				const_reverse_iterator	ret = *this;
				node = node->next;
				return ret;
			}; // class const_reverse_iterator

			t_node *	getNode() const { return node; }
		}; // class const_reverse_iterator

		/* Constructors: */

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
		explicit	List(iterator first, iterator last,
							const allocator_type& alloc = allocator_type()) {
			end_node_init();
			while (first != last) {
				push_back(*first++);
			}
		}

		explicit	List(reverse_iterator first, reverse_iterator last,
							const allocator_type& alloc = allocator_type()) {
			end_node_init();
			while (first != last) {
				push_back(*first++);
			}
		}

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

		List&				operator=(const List& other) {
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

		/* Modifiers */

		void			assign(iterator first, iterator last) {
			if (m_size) {
				clear();
			}
			while (first != last) {
				insert(end(), *first++);
			}
		}

		void			assign(const_iterator first, const_iterator last) {
			if (m_size) {
				clear();
			}
			while (first != last) {
				insert(end(), *first++);
			}
		}

		void			assign(size_type n, const value_type& val) {
			if (m_size) {
				clear();
			}
			for (size_type i = 0; i < n; ++i) {
				insert(end(), val);
			}
		}

		void		push_back(const value_type &val) { insert(end(), val); }

		void		push_front(const value_type &val) { insert(begin(), val); }

		void			clear() {
			t_node * tmp;
			for (; m_size > 0;) {
				tmp = end_node->next->next;
				del_node(end_node->next);
				end_node->next = tmp;
			}
			end_node->prev = end_node;
		}

		iterator		insert(iterator position, const value_type& val) {
			t_node * tmp = position.getNode();
			t_node * new_node = new_node_init(val);
			tmp->prev->next = new_node;
			new_node->prev = tmp->prev;
			tmp->prev = new_node;
			new_node->next = tmp;
			return iterator(new_node);
		}

		void	insert(iterator position, size_type n, const value_type& val) {
			for (size_type i = 0; i < n; ++i) {
				insert(position, val);
			}
		}

		void	insert(iterator position, iterator first, iterator last) {
			while (first != last) {
				insert(position, *first++);
			}
		}

		void	insert(iterator position,
									const_iterator first, const_iterator last) {
			while (first != last) {
				insert(position, *first++);
			}
		}

		iterator		erase(iterator position) {
			t_node * tmp = position.getNode();
			iterator ret = ++position;
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			del_node(tmp);
			return ret;
		}

		iterator		erase(iterator first, iterator last) {
			iterator ret = first;
			while (first != last) {
				ret = erase(first++);
			}
			return ret;
		}

		const_iterator	erase(const_iterator position) {
			t_node * tmp = position.getNode();
			const_iterator ret = ++position;
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			del_node(tmp);
			return ret;
		}

		const_iterator	erase(const_iterator first, const_iterator last) {
			const_iterator ret = first;
			while (first != last) {
				ret = erase(first++);
			}
			return ret;
		}

		void			pop_front() { erase(begin()); }

		void			pop_back() { erase(--end()); }

		/* Element access */

		reference		front() { return *begin(); }

		const_reference	front() const { return *begin(); }

		reference		back() { return *(--end()); }

		const_reference	back() const { return *(--end()); }

		/* Capacity */

		size_type		size() const { return m_size; }

		// TODO formula adjusted to std list behavior
		/* size_type max_size(void) const {                    */
		/*     return (std::numeric_limits<size_type>::max() / */
		/*             (sizeof(t_node) - sizeof(pointer)));    */
		/* }                                                   */

		bool			empty() const { return m_size == 0; }

	}; // class List
} // namespace ft

#endif //FT_CONTAINERS_FT_LIST_H
