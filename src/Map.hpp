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
			class Alloc = std::allocator<std::pair<const Key,T> > > class Map {

		public:

		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const key_type, mapped_type>		data_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef std::ptrdiff_t								difference_type;
		typedef std::size_t									size_type;

		private:

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
				alloc.construct(start_node->data, data_type());
				end_node = alloc_rebind.allocate(1);
				end_node->data = alloc.allocate(1);
				alloc.construct(end_node->data, data_type());
				start_node->parent = end_node;
				start_node->left = NULL;
				start_node->right = NULL;
				end_node->parent = start_node;
				end_node->left = NULL;
				end_node->right = NULL;
				m_size = 0;
				}

			~RBTree() {}

			std::pair<t_node*, bool>	insert_node(const_reference inp_data) {
				t_node* node = root;
				t_node* parent = NULL;
				unbind_extreme_nodes();
				while (node != NULL) {
					parent = node;
					// INFO avoid nodes with duplicated keys
					if (is_equal(inp_data.first, node->data->first)) {
						bind_extreme_nodes();
						return std::make_pair(node, false);
					}
					if (compare(inp_data.first, node->data->first)) {
						node = node->left;
					} else {
						node = node->right;
					}
				}
				node = alloc_rebind.allocate(1);
				node->data = alloc.allocate(1);
				alloc.construct(node->data, inp_data);
				node->parent = parent;
				node->left = NULL;
				node->right = NULL;
				node->is_black = false;
				if (!parent) { root = node; }
				else {
					if (compare(inp_data.first, parent->data->first)) {
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

			void		delete_node(t_node* node) {
				t_node* x_node = NULL;
				t_node* y_node = NULL;
				unbind_extreme_nodes();
				if (!node) { return ; }
				if (!node->left || !node->right) { y_node = node; }
				else {
					y_node = node->right;
					while (y_node->left) { y_node = y_node->left; }
				}
				if (y_node->left) { x_node = y_node->left; }
				else { x_node = y_node->right; }
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
				if (y_node != node) { node->data = y_node->data; }
				if (y_node->is_black) { delete_fixup(x_node); }
				alloc_rebind.deallocate(y_node, 1);
			}

			void		delete_fixup(t_node* node) {
				t_node* tmp = NULL;
				while (node != root && node->is_black) {
					if (node == node->parent->left) {
						tmp = node->parent->right;
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
							tmp->right->is_black = true;
							rotate_left(node->parent);
							node = root;
						}
					} else {
						tmp = node->parent->left;
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
							tmp->left->is_black = true;
							rotate_right(node->parent);
							node = root;
						}
					}
				}
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

			t_node*		search_node(const_reference inp_data) {
				t_node* node = root;
				unbind_extreme_nodes();
				while (node) {
					if (is_equal(inp_data.first, node->data->first)) {
						bind_extreme_nodes();
						return node;
					} else {
						if (compare(inp_data.first, node->data->first)) {
							node->left = node;
						} else {
							node->right = node;
						}
					}
				}
				bind_extreme_nodes();
				return NULL;
			}

		}; // class RBTree

		RBTree	tree;

		public:

		/* Iterators */

		typedef typename RBTree::t_node t_node;

		class const_iterator;

		class iterator : public std::iterator<std::bidirectional_iterator_tag,
				data_type> {
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
					while (node->left) { node->left; }
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
				data_type> {
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
					while (node->left) { node->left; }
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
				data_type> {
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
					while (node->left) { node->left; }
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
				data_type> {
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
					while (node->left) { node->left; }
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

		/* default (1) */
		explicit Map(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) {}

		~Map() {}

		std::pair<iterator,bool>	insert(const_reference inp_data) {
			std::pair<t_node*, bool> ret = tree.insert_node(inp_data);
			return std::make_pair(iterator(ret.first), ret.second);
		}

		size_type		size() const { return tree.m_size; }

		/* Iterators */

		iterator		begin() { return iterator(tree.start_node->parent); }

		iterator		end() { return iterator(tree.end_node); }

		reverse_iterator	rbegin() {
			return reverse_iterator(tree.end_node);
		}

		reverse_iterator	rend() {
			return reverse_iterator(tree.start_node->parent);
		}

	}; // class Map

} // namespace ft

#endif //FT_CONTAINERS_FT_MAP_HPP
