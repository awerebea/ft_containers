/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 11:21:50 by awerebea          #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <iostream>
#include <limits>

namespace ft {

#ifdef __APPLE__
	template <bool, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> { typedef T type; };
#endif

	template < class Key, class T, class Compare = std::less<Key>,
			class Alloc = std::allocator<std::pair<const Key, T> > > class Map {

		public:

		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef std::ptrdiff_t								difference_type;
		typedef std::size_t									size_type;

		private:

		class value_compare {

			public:

			Compare comp;

			explicit value_compare(Compare c) : comp(c) {}

			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator() (const value_type& x, const value_type& y) const {
				return comp(x.first, y.first);
			}
		};

		class RBTree {

			public:

			typedef struct	s_node {
				pointer			data;
				s_node*			left;
				s_node*			right;
				s_node*			parent;
				bool			is_black;
			}				t_node;


			typedef typename allocator_type::template rebind<t_node>::other
															node_allocator;

			size_type		m_size;
			t_node*			root;
			t_node*			start_node;
			t_node*			end_node;

			allocator_type	alloc;
			node_allocator	alloc_rebind;
			Compare			compare;

			explicit	RBTree(const Compare& comp = Compare(),
					const allocator_type& data_alloc = allocator_type(),
					const node_allocator& node_alloc = node_allocator())
					:	root(NULL), alloc(data_alloc), alloc_rebind(node_alloc),
						compare(comp) {
				start_node = alloc_rebind.allocate(1);
				start_node->data = alloc.allocate(1);
				alloc.construct(start_node->data, value_type());
				end_node = alloc_rebind.allocate(1);
				end_node->data = alloc.allocate(1);
				alloc.construct(end_node->data, value_type());
				init_extreme_nodes();
				m_size = 0;
				}

			~RBTree() {}

			void		init_extreme_nodes() {
				start_node->parent = end_node;
				start_node->left = NULL;
				start_node->right = NULL;
				end_node->parent = start_node;
				end_node->left = NULL;
				end_node->right = NULL;
			}

			std::pair<t_node*, bool>	insert_node(const value_type& val) {
				t_node* node = root;
				t_node* parent = NULL;
				unbind_extreme_nodes();
				while (node != NULL) {
					parent = node;
					// INFO avoid insertion nodes with already existed keys
					if (is_equal(val.first, node->data->first)) {
						bind_extreme_nodes();
						return std::make_pair(node, false);
					}
					if (compare(val.first, node->data->first)) {
						node = node->left;
					} else {
						node = node->right;
					}
				}
				node = alloc_rebind.allocate(1);
				node->data = alloc.allocate(1);
				alloc.construct(node->data, val);
				node->parent = parent;
				node->left = NULL;
				node->right = NULL;
				node->is_black = false;
				if (!parent) { root = node; }
				else {
					if (compare(val.first, parent->data->first)) {
						parent->left = node;
					} else {
						parent->right = node;
					}
				}
				insert_fixup(node);
				bind_extreme_nodes();
				m_size++;
				return std::make_pair(node, true);
			}

			void		insert_fixup(t_node* node) {
				t_node* tmp = NULL;
				while (node != root && !node->parent->is_black) {
					if (node->parent == node->parent->parent->left) {
						tmp = node->parent->parent->right;
						if (tmp && !tmp->is_black) {
							node->parent->is_black = true;
							tmp->is_black = true;
							node->parent->parent->is_black = false;
							node = node->parent->parent;
						} else {
							if (node == node->parent->right) {
								node = node->parent;
								rotate_left(node);
							}
							node->parent->is_black = true;
							node->parent->parent->is_black = false;
							rotate_right(node->parent->parent);
						}
					} else {
						tmp = node->parent->parent->left;
						if (tmp && !tmp->is_black) {
							node->parent->is_black = true;
							tmp->is_black = true;
							node->parent->parent->is_black = false;
							node = node->parent->parent;
						} else {
							if (node == node->parent->left) {
								node = node->parent;
								rotate_right(node);
							}
							node->parent->is_black = true;
							node->parent->parent->is_black = false;
							rotate_left(node->parent->parent);
						}
					}
				}
				root->is_black = true;
			}

			void		rotate_left(t_node* node) {
				t_node* tmp = node->right;
				node->right = tmp->left;
				if (tmp->left) { tmp->left->parent = node; }
				if (tmp) { tmp->parent = node->parent; }
				if (node->parent) {
					if (node == node->parent->left) {
						node->parent->left = tmp;
					} else {
						node->parent->right = tmp;
					}
				} else {
					root = tmp;
				}
				if (tmp) { tmp->left = node; }
				if (node) { node->parent = tmp; }
			}

			void		rotate_right(t_node* node) {
				t_node* tmp = node->left;
					node->left = tmp->right;
				if (tmp->right) { tmp->right->parent = node; }
				if (tmp) { tmp->parent = node->parent; }
				if (node->parent) {
					if (node == node->parent->right) {
						node->parent->right = tmp;
					} else {
						node->parent->left = tmp;
					}
				} else {
					root = tmp;
				}
				if (tmp) { tmp->right = node; }
				if (node) { node->parent = tmp; }
			}

			void		delete_last_node() {
				alloc.destroy(root->data);
				alloc.deallocate(root->data, 1);
				alloc_rebind.deallocate(root, 1);
				init_extreme_nodes();
				root = NULL;
				m_size = 0;
			}

			void		delete_node(t_node* node) {
				if (node == root && m_size == 1) { return delete_last_node(); }

				if (!node || node == start_node || node == end_node) {
					return ;
				}

				t_node* dealloc_node = node;

				alloc.destroy(node->data);
				alloc.deallocate(node->data, 1);

				t_node* x_node = NULL;
				t_node* y_node = NULL;

				t_node tmp;
				tmp.data = NULL;
				tmp.parent = NULL;
				tmp.left = &tmp;
				tmp.right = &tmp;
				tmp.is_black = true;

				unbind_extreme_nodes();
				if (!node->left || !node->right) { y_node = node; }
				else {
					y_node = node->right;
					while (y_node->left) { y_node = y_node->left; }
				}
				if (y_node->left) { x_node = y_node->left; }
				else if (y_node->right) { x_node = y_node->right; }
				else { x_node = &tmp; }
				x_node->parent = y_node->parent;
				if (y_node->parent) {
					if (y_node == y_node->parent->left) {
						y_node->parent->left = x_node;
					} else {
						y_node->parent->right = x_node;
					}
				} else {
					root = x_node;
				}
				if (y_node != node) {
					node->data = y_node->data;
					dealloc_node = y_node;
				}
				if (y_node->is_black) {
					delete_fixup(x_node);
				}
				alloc_rebind.deallocate(dealloc_node, 1);
				if (tmp.parent && tmp.parent->left == &tmp) {
					tmp.parent->left = NULL;
				}
				if (tmp.parent && tmp.parent->right == &tmp) {
					tmp.parent->right = NULL;
				}
				bind_extreme_nodes();
				m_size--;
			}

			void		delete_fixup(t_node* node) {
				t_node empty_node;
				empty_node.data = NULL;
				empty_node.parent = NULL;
				empty_node.left = &empty_node;
				empty_node.right = &empty_node;
				empty_node.is_black = true;

				t_node* tmp = NULL;
				while (node != root && node->is_black) {
					if (node == node->parent->left) {
						tmp = (node->parent->right) ?
								node->parent->right : &empty_node;
						if (tmp && !tmp->is_black) {
							tmp->is_black = true;
							node->parent->is_black = false;
							rotate_left(node->parent);
							tmp = node->parent->right;
						}
						if ((!tmp->left || tmp->left->is_black) &&
								(!tmp->right || tmp->right->is_black)) {
							tmp->is_black = false;
							node = node->parent;
						} else {
							if (tmp->right && tmp->right->is_black) {
								if (tmp->left) { tmp->left->is_black = true; }
								tmp->is_black = false;
								rotate_right(tmp);
								tmp = node->parent->right;
							}
							tmp->is_black = node->parent->is_black;
							node->parent->is_black = true;
							if (tmp->right) { tmp->right->is_black = true; }
							rotate_left(node->parent);
							node = root;
						}
					} else {
						tmp = (node->parent->left) ?
								node->parent->left : &empty_node;
						if (tmp && !tmp->is_black) {
							tmp->is_black = true;
							node->parent->is_black = false;
							rotate_right(node->parent);
							tmp = node->parent->left;
						}
						if ((!tmp->left || tmp->left->is_black) &&
								(!tmp->right || tmp->right->is_black)) {
							tmp->is_black = false;
							node = node->parent;
						} else {
							if (tmp->left && tmp->left->is_black) {
								if (tmp->right) { tmp->right->is_black = true; }
								tmp->is_black = false;
								rotate_left(tmp);
								tmp = node->parent->left;
							}
							tmp->is_black = node->parent->is_black;
							node->parent->is_black = true;
							if (tmp->left) { tmp->left->is_black = true; }
							rotate_right(node->parent);
							node = root;
						}
					}
				}
				node->is_black = true;
			}

			void		unbind_extreme_nodes() {
				if (start_node->parent) {
					start_node->parent->left = NULL;
					start_node->parent = NULL;
				}
				if (end_node->parent) {
					end_node->parent->right = NULL;
					end_node->parent = NULL;
				}
			}

			void		bind_extreme_nodes() {
				if (!start_node->parent) {
					t_node* tmp = root;
					while (tmp->left) {
						tmp = tmp->left;
					}
					tmp->left = start_node;
					start_node->parent = tmp;
				}
				if (!end_node->parent) {
					t_node* tmp = root;
					while (tmp->right) {
						tmp = tmp->right;
					}
					tmp->right = end_node;
					end_node->parent = tmp;
				}
			}

			bool		is_equal(const key_type& a, const key_type& b) {
				return (!compare(a, b) && !compare(b, a));
			}

			t_node*		search_node(const key_type& k) {
				t_node* node = root;
				unbind_extreme_nodes();
				while (node) {
					if (is_equal(k, node->data->first)) {
						bind_extreme_nodes();
						return node;
					} else {
						if (compare(k, node->data->first)) {
							node = node->left;
						} else {
							node = node->right;
						}
					}
				}
				bind_extreme_nodes();
				return NULL;
			}

		}; // class RBTree

		typedef typename allocator_type::template
			rebind<typename RBTree::t_node>::other			node_allocator;

		RBTree	tree;
		allocator_type	alloc;
		Compare comp;

		public:

		/* Iterators */

		typedef typename RBTree::t_node t_node;

		class const_iterator;

		class iterator : public std::iterator<std::bidirectional_iterator_tag,
				value_type> {
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
				return node == other.get_node();
			};

			bool				operator!=(const iterator& other) const {
				return node != other.node;
			};

			bool				operator!=(const const_iterator& other) const {
				return node != other.get_node();
			};

			reference			operator*() const {
				return *node->data;
			};

			pointer				operator->() const {
				return node->data;
			};

			iterator&			operator++() {
				if (node->right) {
					node = node->right;
					while (node->left) {
						node = node->left;
					}
				} else {
					t_node* tmp = node->parent;
					while (node == tmp->right) {
						node = tmp;
						tmp = tmp->parent;
					}
					node = tmp;
				}
				return *this;
			};

			iterator			operator++(int) {
				iterator ret = *this;
				operator++();
				return ret;
			};

			iterator&			operator--() {
				if (node->left) {
					node = node->left;
					while (node->right) {
						node = node->right;
					}
				} else {
					t_node* tmp = node->parent;
					while (node == tmp->left) {
						node = tmp;
						tmp = tmp->parent;
					}
					node = tmp;
				}
				return *this;
			};

			iterator			operator--(int) {
				iterator ret = *this;
				operator--();
				return ret;
			};

			t_node*				get_node() const { return node; }
		}; // class iterator

		class const_iterator :
				public std::iterator<std::bidirectional_iterator_tag,
				value_type> {
			t_node* node;

			public:

			const_iterator(): node(NULL) {}

			explicit const_iterator(t_node* node): node(node) {}

			const_iterator(const const_iterator& other) { *this = other; }

			~const_iterator() {}

			const_iterator&			operator=(const const_iterator& other) {
				if (this != &other) { node = other.node; }
				return *this;
			}

			bool				operator==(const const_iterator& other) const {
				return node == other.node;
			};

			bool				operator==(const iterator& other) const {
				return node == other.get_node();
			};

			bool				operator!=(const const_iterator& other) const {
				return node != other.node;
			};

			bool				operator!=(const iterator& other) const {
				return node != other.get_node();
			};

			reference			operator*() const {
				return *node->data;
			};

			pointer				operator->() const {
				return node->data;
			};

			const_iterator&			operator++() {
				if (node->right) {
					node = node->right;
					while (node->left) {
						node = node->left;
					}
				} else {
					t_node* tmp = node->parent;
					while (node == tmp->right) {
						node = tmp;
						tmp = tmp->parent;
					}
					node = tmp;
				}
				return *this;
			};

			const_iterator			operator++(int) {
				const_iterator ret = *this;
				operator++();
				return ret;
			};

			const_iterator&			operator--() {
				if (node->left) {
					node = node->left;
					while (node->right) {
						node = node->right;
					}
				} else {
					t_node* tmp = node->parent;
					while (node == tmp->left) {
						node = tmp;
						tmp = tmp->parent;
					}
					node = tmp;
				}
				return *this;
			};

			const_iterator			operator--(int) {
				const_iterator ret = *this;
				operator--();
				return ret;
			};

			t_node*				get_node() const { return node; }
		}; // class const_iterator

		class const_reverse_iterator;

		class reverse_iterator :
				public std::iterator<std::bidirectional_iterator_tag,
				value_type> {
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

			bool	operator==(const reverse_iterator& other) const {
				return node == other.node;
			};

			bool	operator==(const const_reverse_iterator& other) const {
				return node == other.get_node();
			};

			bool	operator!=(const reverse_iterator& other) const {
				return node != other.node;
			};

			bool	operator!=(const const_reverse_iterator& other) const {
				return node != other.get_node();
			};

			reference			operator*() const {
				return *node->data;
			};

			pointer				operator->() const {
				return node->data;
			};

			reverse_iterator&	operator++() {
				if (node->left) {
					node = node->left;
					while (node->right) {
						node = node->right;
					}
				} else {
					t_node* tmp = node->parent;
					while (node == tmp->left) {
						node = tmp;
						tmp = tmp->parent;
					}
					node = tmp;
				}
				return *this;
			};

			reverse_iterator	operator++(int) {
				reverse_iterator ret = *this;
				operator++();
				return ret;
			};

			reverse_iterator&	operator--() {
				if (node->right) {
					node = node->right;
					while (node->left) {
						node = node->left;
					}
				} else {
					t_node* tmp = node->parent;
					while (node == tmp->right) {
						node = tmp;
						tmp = tmp->parent;
					}
					node = tmp;
				}
				return *this;
			};

			reverse_iterator	operator--(int) {
				reverse_iterator ret = *this;
				operator--();
				return ret;
			};

			t_node*				get_node() const { return node; }
		}; // class reverse_iterator

		class const_reverse_iterator :
				public std::iterator<std::bidirectional_iterator_tag,
				value_type> {
			t_node* node;

			public:

			const_reverse_iterator(): node(NULL) {}

			explicit const_reverse_iterator(t_node* node): node(node) {}

			const_reverse_iterator(const const_reverse_iterator& other) {
				*this = other;
			}

			~const_reverse_iterator() {}

			const_reverse_iterator&	operator=(const
					const_reverse_iterator& other) {
				if (this != &other) { node = other.node; }
				return *this;
			}

			bool	operator==(const const_reverse_iterator& other) const {
				return node == other.node;
			};

			bool	operator==(const reverse_iterator& other) const {
				return node == other.get_node();
			};

			bool	operator!=(const const_reverse_iterator& other) const {
				return node != other.node;
			};

			bool	operator!=(const reverse_iterator& other) const {
				return node != other.get_node();
			};

			reference			operator*() const {
				return *node->data;
			};

			pointer				operator->() const {
				return node->data;
			};

			const_reverse_iterator&		operator++() {
				if (node->left) {
					node = node->left;
					while (node->right) {
						node = node->right;
					}
				} else {
					t_node* tmp = node->parent;
					while (node == tmp->left) {
						node = tmp;
						tmp = tmp->parent;
					}
					node = tmp;
				}
				return *this;
			};

			const_reverse_iterator		operator++(int) {
				const_reverse_iterator ret = *this;
				operator++();
				return ret;
			};

			const_reverse_iterator&		operator--() {
				if (node->right) {
					node = node->right;
					while (node->left) {
						node = node->left;
					}
				} else {
					t_node* tmp = node->parent;
					while (node == tmp->right) {
						node = tmp;
						tmp = tmp->parent;
					}
					node = tmp;
				}
				return *this;
			};

			const_reverse_iterator		operator--(int) {
				const_reverse_iterator ret = *this;
				operator--();
				return ret;
			};

			t_node*				get_node() const { return node; }
		}; // class const_reverse_iterator

		/* Constructors: */

		/* empty (1) */
		explicit Map(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			: alloc(alloc), comp(comp) {}

		/* range (2) */
#ifdef __APPLE__
		template <class InputIterator>
		Map(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				const key_compare& comp = key_compare(),
				typename ft::enable_if<std::__is_input_iterator<InputIterator>::
				value>::type* = 0)
#elif __linux__
		Map(iterator first, iterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
#endif
		: alloc(alloc), comp(comp)
		{
			insert(first, last);
		}

#ifdef __linux__
		Map(const_iterator first, const_iterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			: alloc(alloc), comp(comp) {
			insert(first, last);
		}
#endif

#ifdef __linux__
		Map(reverse_iterator first, reverse_iterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			: alloc(alloc), comp(comp) {
			insert(first, last);
		}
#endif

		/* copy (3) */
		Map(const Map& other) { *this = other; }

		Map&			operator=(const Map& other) {
			if (this == &other) { return *this; }
			if (tree.m_size) { clear(); }
			insert(other.begin(), other.end());
			return *this;
		}

		~Map() {
			if (tree.m_size) { clear(); }
			allocator_type().destroy(tree.start_node->data);
			allocator_type().deallocate(tree.start_node->data, 1);
			node_allocator().deallocate(tree.start_node, 1);
			allocator_type().destroy(tree.end_node->data);
			allocator_type().deallocate(tree.end_node->data, 1);
			node_allocator().deallocate(tree.end_node, 1);
		}

		/* Iterators */

		iterator				begin() {
			return iterator(tree.start_node->parent);
		}

		const_iterator			begin() const {
			return const_iterator(tree.start_node->parent);
		}

		iterator				end() {
			return iterator(tree.end_node);
		}

		const_iterator			end() const {
			return const_iterator(tree.end_node);
		}

		reverse_iterator		rbegin() {
			return reverse_iterator(tree.end_node->parent);
		}

		const_reverse_iterator	rbegin() const {
			return const_reverse_iterator(tree.end_node->parent);
		}

		reverse_iterator		rend() {
			return reverse_iterator(tree.start_node);
		}

		const_reverse_iterator	rend() const {
			return const_reverse_iterator(tree.start_node);
		}

		/* Capacity */

		bool			empty() const { return tree.m_size == 0; }

		size_type		size() const { return tree.m_size; }

		size_type		max_size(void) const {
			return node_allocator().max_size();
		}

		/* Element access */

		mapped_type&	operator[](const key_type& k) {
			return (*((insert(std::make_pair(k,mapped_type()))).first)).second;
		}

		/* Modifiers */

		std::pair<iterator, bool>	insert(const value_type& val) {
			std::pair<t_node*, bool> ret = tree.insert_node(val);
			return std::make_pair(iterator(ret.first), ret.second);
		}

		iterator	insert(iterator position, const value_type& val) {
			(void)position;
			return iterator(tree.insert_node(val).first);
		}

#ifdef __APPLE__
		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last,
				typename ft::enable_if<std::__is_input_iterator<InputIterator>::
				value>::type* = 0)
#elif __linux__
		void	insert(iterator first, iterator last)
#endif
		{
			while (first != last) { insert(*first++); }
		}

#ifdef __linux__
		void	insert(const_iterator first, const_iterator last) {
			while (first != last) { insert(*first++); }
		}
#endif

#ifdef __linux__
		void	insert(reverse_iterator first, reverse_iterator last) {
			while (first != last) { insert(*first++); }
		}
#endif

		void			erase(iterator position) {
			tree.delete_node(position.get_node());
		}

		void			erase(const_iterator position) {
			tree.delete_node(position.get_node());
		}

		size_type		erase(const key_type& k) {
			t_node* tmp = (tree.search_node(k));
			if (!tmp) { return 0; }
			tree.delete_node(tmp);
			return 1;
		}

		void			erase(iterator first, iterator last) {
			size_t key = first.get_node()->data->first;
			size_t next_key = (++first).get_node()->data->first;
			size_t last_key = (--last).get_node()->data->first;
			iterator it;
			while (key != last_key) {
				erase(key);
				key = next_key;
				it = iterator(tree.search_node(next_key));
				next_key = (++it).get_node()->data->first;
			}
			erase(key);
		}

		void			erase(const_iterator first, const_iterator last) {
			while (first != last) { erase(first++); }
		}

		void			swap(Map& other) {
			t_node*	tmp_node = other.tree.root;
			other.tree.root = this->tree.root;
			this->tree.root = tmp_node;

			tmp_node = other.tree.start_node;
			other.tree.start_node = this->tree.start_node;
			this->tree.start_node = tmp_node;

			tmp_node = other.tree.end_node;
			other.tree.end_node = this->tree.end_node;
			this->tree.end_node = tmp_node;

			size_type	tmp_size = other.tree.m_size;
			other.tree.m_size = this->tree.m_size;
			this->tree.m_size = tmp_size;
		}

		void			clear() {
			erase(begin(), end());
		}

		/* Observers */

		key_compare		key_comp() const {
			return key_compare();
		}

		value_compare	value_comp() const {
			return value_compare(key_compare());
		}

		/* Operations */

		iterator		find(const key_type& k) {
			t_node* ret = tree.search_node(k);
			return (ret) ? iterator(ret) : end();
		}

		const_iterator	find(const key_type& k) const {
			t_node* ret = tree.search_node(k);
			return (ret) ? const_iterator(ret) : end();
		}

		size_type		count(const key_type& k) { // FIXME should be const
			t_node* ret = tree.search_node(k);
			return (ret) ? 1 : 0;
		}

		iterator		lower_bound(const key_type& k) {
			for (iterator it = begin(); it != end(); ++it) {
				if (tree.compare(k, it->first) || tree.is_equal(k, it->first)) {
					return it;
				}
			}
			return end();
		}

		const_iterator	lower_bound(const key_type& k) const {
			for (const_iterator it = begin(); it != end(); ++it) {
				if (tree.compare(k, it->first) || tree.is_equal(k, it->first)) {
					return it;
				}
			}
			return end();
		}

		iterator		upper_bound(const key_type& k) {
			for (iterator it = begin(); it != end(); ++it) {
				if (tree.compare(k, it->first)) {
					return it;
				}
			}
			return end();
		}

		const_iterator	upper_bound(const key_type& k) const {
			for (const_iterator it = begin(); it != end(); ++it) {
				if (tree.compare(k, it->first)) {
					return it;
				}
			}
			return end();
		}

		std::pair<const_iterator, const_iterator>	equal_range(const
															key_type& k) const {
			return std::make_pair(lower_bound(k), upper_bound(k));
		}

		std::pair<iterator,iterator>				equal_range(const
															key_type& k) {
			return std::make_pair(lower_bound(k), upper_bound(k));
		}

	}; // class Map

} // namespace ft

#endif //FT_CONTAINERS_FT_MAP_HPP
