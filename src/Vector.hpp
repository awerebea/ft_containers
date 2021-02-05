/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:19:41 by awerebea          #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>
#include <stdexcept>  // std::out_of_range
#include <string>     // std::string, std::to_string
#include <limits>

namespace ft {

#ifdef __APPLE__
	template <bool, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> { typedef T type; };
#endif

	template <class T, class Alloc = std::allocator<T> > class Vector {
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

		allocator_type	m_alloc;
		pointer			start_elem;
		size_type		m_size;
		size_type		m_capacity;

		void		range_check(const size_type& n) const {
			if (n >= m_size) {
				throw (std::out_of_range("Vector::range_check: n (which is "
							+ std::to_string(n) + ") >= this->size() (which is "
							+ std::to_string(m_size) + ")"));
			}
		}

	public:

		/* Iterators */

		class const_iterator;

		class iterator :
			public std::iterator<std::random_access_iterator_tag, value_type> {
			pointer elem;
		public:
			iterator(): elem(NULL) {}

			explicit iterator(pointer elem): elem(elem) {}

			iterator(const iterator& other) { *this = other; }

			~iterator() {}

			iterator&			operator=(const iterator& other) {
				if (this != &other) { elem = other.elem; }
				return *this;
			}

			bool				operator==(const iterator& other) const {
				return elem == other.elem;
			};

			bool				operator==(const const_iterator& other) const {
				return elem == other.getElem();
			};

			bool				operator!=(const iterator& other) const {
				return elem != other.elem;
			};

			bool				operator!=(const const_iterator& other) const {
				return elem != other.getElem();
			};

			reference			operator*() const {
				return *elem;
			};

			pointer				operator->() const {
				return elem;
			};

			iterator&			operator++() {
				elem++;
				return *this;
			};

			iterator			operator++(int) {
				iterator ret = *this;
				elem++;
				return ret;
			};

			iterator&			operator--() {
				elem--;
				return *this;
			};

			iterator			operator--(int) {
				iterator ret = *this;
				elem--;
				return ret;
			};

			iterator			operator+(difference_type n) const {
				return iterator(elem + n);
			}

			iterator			operator-(difference_type n) const {
				return iterator(elem - n);
			}

			bool				operator<(const iterator& other) const {
				return elem < other.elem;
			};

			bool				operator<(const const_iterator& other) const {
				return elem < other.getElem();
			};

			bool				operator>(const iterator& other) const {
				return elem > other.elem;
			};

			bool				operator>(const const_iterator& other) const {
				return elem > other.getElem();
			};

			bool				operator<=(const iterator& other) const {
				return elem <= other.elem;
			};

			bool				operator<=(const const_iterator& other) const {
				return elem <= other.getElem();
			};

			bool				operator>=(const iterator& other) const {
				return elem >= other.elem;
			};

			bool				operator>=(const const_iterator& other) const {
				return elem >= other.getElem();
			};

			iterator&			operator+=(difference_type n) {
				elem += n;
				return *this;
			}

			iterator&			operator-=(difference_type n) {
				elem -= n;
				return *this;
			}

			pointer				getElem() const { return elem; }
		}; // class iterator

		class const_iterator :
			public std::iterator<std::random_access_iterator_tag, value_type> {
			pointer elem;
		public:
			const_iterator(): elem(NULL) {}

			explicit const_iterator(pointer elem): elem(elem) {}

			const_iterator(const const_iterator& other) { *this = other; }

			~const_iterator() {}

			const_iterator&			operator=(const const_iterator& other) {
				if (this != &other) { elem = other.elem; }
				return *this;
			}

			bool				operator==(const const_iterator& other) const {
				return elem == other.elem;
			};

			bool				operator==(const iterator& other) const {
				return elem == other.getElem();
			};

			bool				operator!=(const const_iterator& other) const {
				return elem != other.elem;
			};

			bool				operator!=(const iterator& other) const {
				return elem != other.getElem();
			};

			reference			operator*() const {
				return *elem;
			};

			pointer				operator->() const {
				return elem;
			};

			const_iterator&			operator++() {
				elem++;
				return *this;
			};

			const_iterator			operator++(int) {
				const_iterator ret = *this;
				elem++;
				return ret;
			};

			const_iterator&			operator--() {
				elem--;
				return *this;
			};

			const_iterator			operator--(int) {
				const_iterator ret = *this;
				elem--;
				return ret;
			};

			const_iterator			operator+(difference_type n) const {
				return const_iterator(elem + n);
			}

			const_iterator			operator-(difference_type n) const {
				return const_iterator(elem - n);
			}

			bool				operator<(const const_iterator& other) const {
				return elem < other.elem;
			};

			bool				operator<(const iterator& other) const {
				return elem < other.getElem();
			};

			bool				operator>(const const_iterator& other) const {
				return elem > other.elem;
			};

			bool				operator>(const iterator& other) const {
				return elem > other.getElem();
			};

			bool				operator<=(const const_iterator& other) const {
				return elem <= other.elem;
			};

			bool				operator<=(const iterator& other) const {
				return elem <= other.getElem();
			};

			bool				operator>=(const const_iterator& other) const {
				return elem >= other.elem;
			};

			bool				operator>=(const iterator& other) const {
				return elem >= other.getElem();
			};

			const_iterator&			operator+=(difference_type n) {
				elem += n;
				return *this;
			}

			const_iterator&			operator-=(difference_type n) {
				elem -= n;
				return *this;
			}

			pointer				getElem() const { return elem; }
		}; // class const_iterator

		class const_reverse_iterator;

		class reverse_iterator :
			public std::iterator<std::random_access_iterator_tag, value_type> {
			pointer elem;
		public:
			reverse_iterator(): elem(NULL) {}

			explicit reverse_iterator(pointer elem): elem(elem) {}

			reverse_iterator(const reverse_iterator& other) { *this = other; }

			~reverse_iterator() {}

			reverse_iterator&	operator=(const reverse_iterator& other) {
				if (this != &other) { elem = other.elem; }
				return *this;
			}

			bool	operator==(const reverse_iterator& other) const {
				return elem == other.elem;
			};

			bool	operator==(const const_reverse_iterator& other) const {
				return elem == other.getElem();
			};

			bool	operator!=(const reverse_iterator& other) const {
				return elem != other.elem;
			};

			bool	operator!=(const const_reverse_iterator& other) const {
				return elem != other.getElem();
			};

			reference			operator*() const {
				return *elem;
			};

			pointer				operator->() const {
				return elem;
			};

			reverse_iterator&	operator++() {
				elem--;
				return *this;
			};

			reverse_iterator	operator++(int) {
				reverse_iterator ret = *this;
				elem--;
				return ret;
			};

			reverse_iterator&	operator--() {
				elem++;
				return *this;
			};

			reverse_iterator	operator--(int) {
				reverse_iterator ret = *this;
				elem++;
				return ret;
			};

			reverse_iterator	operator+(difference_type n) const {
				return reverse_iterator(elem + n);
			}

			reverse_iterator	operator-(difference_type n) const {
				return reverse_iterator(elem - n);
			}

			bool	operator<(const reverse_iterator& other) const {
				return elem < other.elem;
			};

			bool	operator<(const const_reverse_iterator& other) const {
				return elem < other.getElem();
			};

			bool	operator>(const reverse_iterator& other) const {
				return elem > other.elem;
			};

			bool	operator>(const const_reverse_iterator& other) const {
				return elem > other.getElem();
			};

			bool	operator<=(const reverse_iterator& other) const {
				return elem <= other.elem;
			};

			bool	operator<=(const const_reverse_iterator& other) const {
				return elem <= other.getElem();
			};

			bool	operator>=(const reverse_iterator& other) const {
				return elem >= other.elem;
			};

			bool	operator>=(const const_reverse_iterator& other) const {
				return elem >= other.getElem();
			};

			reverse_iterator&	operator+=(difference_type n) {
				elem += n;
				return *this;
			}

			reverse_iterator&	operator-=(difference_type n) {
				elem -= n;
				return *this;
			}

			pointer				getElem() const { return elem; }
		}; // class reverse_iterator

		class const_reverse_iterator :
			public std::iterator<std::random_access_iterator_tag, value_type> {
			pointer elem;
		public:
			const_reverse_iterator(): elem(NULL) {}

			explicit const_reverse_iterator(pointer elem): elem(elem) {}

			const_reverse_iterator(const const_reverse_iterator& other) {
				*this = other;
			}

			~const_reverse_iterator() {}

			const_reverse_iterator&	operator=(const const_reverse_iterator&
																		other) {
				if (this != &other) { elem = other.elem; }
				return *this;
			}

			bool	operator==(const const_reverse_iterator& other) const {
				return elem == other.elem;
			};

			bool	operator==(const reverse_iterator& other) const {
				return elem == other.getElem();
			};

			bool	operator!=(const const_reverse_iterator& other) const {
				return elem != other.elem;
			};

			bool	operator!=(const reverse_iterator& other) const {
				return elem != other.getElem();
			};

			reference				operator*() const {
				return *elem;
			};

			pointer					operator->() const {
				return elem;
			};

			const_reverse_iterator&	operator++() {
				elem--;
				return *this;
			};

			const_reverse_iterator	operator++(int) {
				const_reverse_iterator ret = *this;
				elem--;
				return ret;
			};

			const_reverse_iterator&	operator--() {
				elem++;
				return *this;
			};

			const_reverse_iterator	operator--(int) {
				const_reverse_iterator ret = *this;
				elem++;
				return ret;
			};

			const_reverse_iterator	operator+(difference_type n) const {
				return const_reverse_iterator(elem + n);
			}

			const_reverse_iterator	operator-(difference_type n) const {
				return const_reverse_iterator(elem - n);
			}

			bool	operator<(const const_reverse_iterator& other) const {
				return elem < other.elem;
			};

			bool	operator<(const reverse_iterator& other) const {
				return elem < other.getElem();
			};

			bool	operator>(const const_reverse_iterator& other) const {
				return elem > other.elem;
			};

			bool	operator>(const reverse_iterator& other) const {
				return elem > other.getElem();
			};

			bool	operator<=(const const_reverse_iterator& other) const {
				return elem <= other.elem;
			};

			bool	operator<=(const reverse_iterator& other) const {
				return elem <= other.getElem();
			};

			bool	operator>=(const const_reverse_iterator& other) const {
				return elem >= other.elem;
			};

			bool	operator>=(const reverse_iterator& other) const {
				return elem >= other.getElem();
			};

			const_reverse_iterator&	operator+=(difference_type n) {
				elem += n;
				return *this;
			}

			const_reverse_iterator&	operator-=(difference_type n) {
				elem -= n;
				return *this;
			}

			pointer					getElem() const { return elem; }
		}; // class const_reverse_iterator

		/* Constructors: */

		/* default (1) */
		explicit	Vector(const allocator_type& alloc = allocator_type())
			: m_alloc(alloc), start_elem(NULL) {
			m_size = 0;
			m_capacity = 0;
		}

		/* fill (2) */
		explicit	Vector(size_type n, const_reference val = value_type(),
						const allocator_type& alloc = allocator_type())
			: m_alloc(alloc) {
			start_elem = m_alloc.allocate(n);
			m_size = 0;
			m_capacity = n;
			while (m_size < n) {
				m_alloc.construct(start_elem + m_size, val);
				m_size++;
			}
		}

		/* range (3) */
#ifdef __APPLE__
		template <class InputIterator>
		Vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<std::__is_input_iterator<InputIterator>::
				value>::type* = 0)
#elif __linux__
		Vector(iterator first, iterator last,
				const allocator_type& alloc = allocator_type())
#endif
			: m_alloc(alloc), start_elem(NULL) {
			m_size = 0;
			m_capacity = 0;
			assign(first, last);
		}

#ifdef __linux__
		Vector(reverse_iterator first, reverse_iterator last,
				const allocator_type& alloc = allocator_type())
			: m_alloc(alloc), start_elem(NULL) {
			m_size = 0;
			m_capacity = 0;
			assign(first, last);
		}
#endif

		/* copy (4) */
		Vector(const Vector& other): m_alloc(other.m_alloc), start_elem(NULL) {
			m_size = 0;
			m_capacity = 0;
			*this = other;
		}

		~Vector() {
			clear();
			m_alloc.deallocate(start_elem, m_capacity);
		}

		Vector&			operator=(const Vector& other) {
			if (this == &other) { return *this; }
			assign(other.begin(), other.end());
			return *this;
		}

		/* Iterators */

		iterator		begin() { return iterator(start_elem); }

		const_iterator	begin() const { return const_iterator(start_elem); }

		iterator		end() { return iterator(start_elem + m_size); }

		const_iterator	end() const {
			return const_iterator(start_elem + m_size);
		}

		reverse_iterator		rbegin() {
			return reverse_iterator(start_elem + m_size - 1);
		}

		const_reverse_iterator	rbegin() const {
			return const_reverse_iterator(start_elem + m_size - 1);
		}

		reverse_iterator		rend() {
			return reverse_iterator(start_elem - 1);
		}

		const_reverse_iterator	rend() const {
			return const_reverse_iterator(start_elem - 1);
		}

		/* Element access */

		reference		operator[](size_type n) { return *(start_elem + n); }

		const_reference	operator[](size_type n) const {
			return *(start_elem + n);
		}

		reference		at(size_type n) {
			range_check(n);
			return *(start_elem + n);
		}

		const_reference	at(size_type n) const {
			if (n >= m_size) {
				throw (std::out_of_range("out of range"));
			}
			return *(start_elem + n);
		}

		reference		front() { return *begin(); }

		const_reference	front() const { return *begin(); }

		reference		back() { return *(--end()); }

		const_reference	back() const { return *(--end()); }

		/* Modifiers */

#ifdef __APPLE__
		template <class InputIterator>
		void		assign(iterator position,
					InputIterator first, InputIterator last,
				typename ft::enable_if<std::__is_input_iterator<InputIterator>::
					value>::type* = 0)
#elif __linux__
		void		assign(iterator first, iterator last)
#endif
		{
			if (m_size) { clear(); }
			size_type range_len = &(*last) - &(*first);
			if (range_len > m_capacity) { reserve(range_len); }
			for (size_type i = 0; i < range_len; ++i) {
				m_alloc.construct(start_elem + i, *first++);
				m_size++;
			}
		}

#ifdef __linux__
		void		assign(const_iterator first, const_iterator last) {
			if (m_size) { clear(); }
			size_type range_len = &(*last) - &(*first);
			if (range_len > m_capacity) { reserve(range_len); }
			for (size_type i = 0; i < range_len; ++i) {
				m_alloc.construct(start_elem + i, *first++);
				m_size++;
			}
		}
#endif


		void		assign(size_type n, const_reference val) {
			if (m_size) { clear(); }
			if (n > m_capacity) { reserve(n); }
			for (size_type i = 0; i < n; ++i) {
				m_alloc.construct(start_elem + i, val);
				m_size++;
			}
		}

		void		push_back(const value_type &val) { insert(end(), val); }

		void		pop_back() {
			if (m_size) { m_alloc.destroy(start_elem + --m_size); }
		}

		iterator	insert(iterator position, const_reference val) {
			insert(position, 1, val);
			return iterator(position);
		}

		void	insert(iterator position, size_type n, const_reference val) {
			size_type new_elem_ind = &(*position) - start_elem;
			if (m_capacity < m_size + n) {
				pointer old_start = start_elem;
				size_type new_capacity;
				if (n == 1) {
					new_capacity = (m_capacity > 0) ? m_capacity * 2 : 1;
				} else if (m_size * 2 > m_size + n) {
					new_capacity = m_size * 2;
				} else {
					new_capacity = m_size + n;
				}
				start_elem = m_alloc.allocate(new_capacity);
				for (size_type i = 0; i < new_elem_ind; ++i) {
					m_alloc.construct(start_elem + i, *(old_start + i));
					m_alloc.destroy(old_start + i);
				}
				for (size_type i = 0; i < n; ++i) {
					m_alloc.construct(start_elem + new_elem_ind + i, val);
				}
				for (size_type i = m_size; i != new_elem_ind; --i) {
					m_alloc.construct(start_elem + n + i - 1,
														*(old_start + i - 1));
					m_alloc.destroy(old_start + i - 1);
				}
				m_alloc.deallocate(old_start, m_capacity);
				m_capacity = new_capacity;
				m_size += n;
			} else {
				for (size_type i = m_size; i != new_elem_ind; --i) {
					m_alloc.construct(start_elem + n + i - 1,
														*(start_elem + i - 1));
				}
				for (size_type i = 0; i < n; ++i) {
					m_alloc.construct(start_elem + new_elem_ind + i, val);
				}
				m_size += n;
			}
		}

#ifdef __APPLE__
		template <class InputIterator>
		void	insert(iterator position,
				InputIterator first, InputIterator last,
				typename ft::enable_if<std::__is_input_iterator<InputIterator>::
				value>::type* = 0)
#elif __linux__
		void		insert(iterator position, iterator first, iterator last)
#endif
		{
			size_type new_elem_ind = &(*position) - start_elem;
			size_type n = &(*last) - &(*first);
			if (m_capacity < m_size + n) {
				pointer old_start = start_elem;
				size_type new_capacity;
				if (n == 1) {
					new_capacity = (m_capacity > 0) ? m_capacity * 2 : 1;
				} else if (m_size * 2 > m_size + n) {
					new_capacity = m_size * 2;
				} else {
					new_capacity = m_size + n;
				}
				start_elem = m_alloc.allocate(new_capacity);
				for (size_type i = 0; i < new_elem_ind; ++i) {
					m_alloc.construct(start_elem + i, *(old_start + i));
					m_alloc.destroy(old_start + i);
				}
				for (size_type i = 0; i < n; ++i) {
					m_alloc.construct(start_elem + new_elem_ind + i, *first++);
				}
				for (size_type i = m_size; i != new_elem_ind; --i) {
					m_alloc.construct(start_elem + n + i - 1,
														*(old_start + i - 1));
					m_alloc.destroy(old_start + i - 1);
				}
				m_alloc.deallocate(old_start, m_capacity);
				m_capacity = new_capacity;
				m_size += n;
			} else {
				for (size_type i = m_size; i != new_elem_ind; --i) {
					m_alloc.construct(start_elem + n + i - 1,
														*(start_elem + i - 1));
				}
				for (size_type i = 0; i < n; ++i) {
					m_alloc.construct(start_elem + new_elem_ind + i, *first++);
				}
				m_size += n;
			}
		}

#ifdef __linux__
		void		insert(reverse_iterator position, reverse_iterator first,
																iterator last) {
			size_type new_elem_ind = &(*position) - start_elem;
			size_type n = &(*last) - &(*first);
			if (m_capacity < m_size + n) {
				pointer old_start = start_elem;
				size_type new_capacity;
				if (n == 1) {
					new_capacity = (m_capacity > 0) ? m_capacity * 2 : 1;
				} else if (m_size * 2 > m_size + n) {
					new_capacity = m_size * 2;
				} else {
					new_capacity = m_size + n;
				}
				start_elem = m_alloc.allocate(new_capacity);
				for (size_type i = 0; i < new_elem_ind; ++i) {
					m_alloc.construct(start_elem + i, *(old_start + i));
					m_alloc.destroy(old_start + i);
				}
				for (size_type i = 0; i < n; ++i) {
					m_alloc.construct(start_elem + new_elem_ind + i, *first++);
				}
				for (size_type i = m_size; i != new_elem_ind; --i) {
					m_alloc.construct(start_elem + n + i - 1,
														*(old_start + i - 1));
					m_alloc.destroy(old_start + i - 1);
				}
				m_alloc.deallocate(old_start, m_capacity);
				m_capacity = new_capacity;
				m_size += n;
			} else {
				for (size_type i = m_size; i != new_elem_ind; --i) {
					m_alloc.construct(start_elem + n + i - 1,
														*(start_elem + i - 1));
				}
				for (size_type i = 0; i < n; ++i) {
					m_alloc.construct(start_elem + new_elem_ind + i, *first++);
				}
				m_size += n;
			}
		}
#endif

		iterator	erase(iterator position) {
			iterator last = position;
			return erase(position, ++last);
		}

		iterator	erase(iterator first, iterator last) {
			if (first == end()) { return end(); }
			size_type del_elem_ind = &(*first) - start_elem;
			size_type n = &(*last) - &(*first);
			for (size_type i = 0; i < m_size - del_elem_ind - n; ++i) {
				m_alloc.construct(start_elem + del_elem_ind + i, *last++);
			}
			for (size_type i = 0; i < n; ++i) {
				m_alloc.destroy(start_elem + m_size - i - 1);
			}
			m_size -= n;
			return iterator(start_elem + del_elem_ind);
		}

		void		swap(Vector& other) {
			pointer tmp_ptr = start_elem;
			start_elem = other.start_elem;
			other.start_elem = tmp_ptr;

			size_type tmp_size = m_size;
			m_size = other.m_size;
			other.m_size = tmp_size;

			size_type tmp_capacity = m_capacity;
			m_capacity = other.m_capacity;
			other.m_capacity = tmp_capacity;
		}

		void		clear() {
			while (m_size) {
				--m_size;
				m_alloc.destroy(start_elem + m_size);
			}
		}

		/* Capacity */

		size_type		size() const { return m_size; }

		size_type		capacity() const { return m_capacity; }

		size_type		max_size(void) const {
			return allocator_type().max_size();
		}

		void			resize(size_type n, value_type val = value_type()) {
			if (n < m_size) {
				for ( ; m_size > n; ) {
					m_alloc.destroy(start_elem + --m_size);
				}
			} else if (n > m_size) {
				if (n <= m_capacity) { insert(end(), n - m_size, val); }
				else {
					reserve(n);
					insert(end(), n - m_size, val);
				}
			}
		}

		bool			empty() const { return m_size == 0; }

		void			reserve(size_type new_capacity) {
			if (new_capacity <= m_capacity) { return ; }
			pointer old_start = start_elem;
			start_elem = m_alloc.allocate(new_capacity);
			for (size_type i = 0; i < m_size; i++) {
				m_alloc.construct(start_elem + i, *(old_start + i));
				m_alloc.destroy(old_start + i);
			}
			m_alloc.deallocate(old_start, m_capacity);
			m_capacity = new_capacity;
		}

	}; // class Vector

	template <class T, class Alloc>
	void	swap(Vector<T,Alloc>& x, Vector<T,Alloc>& y) {
		x.swap(y);
	}

	/* relational operators */

	template <class T, class Alloc>
	bool	operator==(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size()) {
			return false;
		}
		typename Vector<T,Alloc>::const_iterator it_lhs = lhs.begin();
		typename Vector<T,Alloc>::const_iterator it_rhs = rhs.begin();
		for ( ; it_lhs != lhs.end(); ) {
			if (*it_lhs++ != *it_rhs++) { return false; }
		}
		return true;
	}

	template <class T, class Alloc>
	bool	operator!=(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
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
	bool	operator<(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
					rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool	operator<=(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>=(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}

} // namespace ft

#endif //FT_CONTAINERS_FT_VECTOR_HPP
