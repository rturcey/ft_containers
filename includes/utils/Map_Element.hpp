/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map_Element.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:05:58 by rturcey           #+#    #+#             */
/*   Updated: 2021/04/07 14:48:27 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ELEMENT_HPP
#define MAP_ELEMENT_HPP

#include <cstdlib>
#include <limits>
#include "Utils.hpp"

template <class Key, typename T, class Compare = std::less<Key> >
class	Map_Element
{
	public:
		Map_Element(void) : _left(NULL), _right(NULL), _parent(NULL), _val() {}
		Map_Element(const T &data) : _left(NULL), _right(NULL), _parent(NULL), _val(data) {}
		Map_Element(const T &data, Map_Element *left, Map_Element *right, Map_Element *parent) : _left(left), _right(right), _parent(parent), _val(data) {}
		Map_Element(const T &data, Map_Element *parent) : _left(NULL), _right(NULL), _parent(parent), _val(data) {}
		Map_Element(Map_Element const &src) : _left(src._left), _right(src._right), _parent(src._parent), _val(src._val) {}

		Map_Element	*find(Key key, Map_Element *root)
		{
			Map_Element		*ret = NULL;
			if (!root)
				return (ret);
			if (root->_val.first == key)
				return (root);
			if ((ret = find(key, root->_left)))
				return (ret);
			if ((ret = find(key, root->_right)))
				return (ret);
			return (NULL);
		}
		Map_Element &operator=(const Map_Element &rhs)
		{
			this->_left = rhs._left;
			this->_right = rhs._right;
			this->_parent = rhs._parent;
			this->_val = rhs._val;
		}
		ft::MapIterator<T, Map_Element>	push(Map_Element *root, Map_Element **nend, Map_Element **begin, T val)
		{
			Map_Element		*stock = root;
			Map_Element		*i = stock;
			while (stock && stock != *nend)
			{
				i = stock;
				if (_comp(val.first, stock->_val.first))
					stock = stock->left();
				else
					stock = stock->right();
			}
			if (_comp(val.first, i->_val.first))
			{
				i->_left = new Map_Element(val, i);
				stock = i->_left;
			}
			else
			{
				if (stock == *nend)
				{
					Map_Element *newelem = new Map_Element(val, i);
					newelem->_right = *nend;
					stock = newelem;
					(*nend)->_parent = stock;
					i->_right = stock;
				}
				else
				{
					i->_right = new Map_Element(val, i);
					stock = i->_right;
				}
			}
			(*begin) = beg(root);
			return (stock);
		}
		Map_Element	*beg(Map_Element *root)
		{
			Map_Element		*bg = root;
			while (bg && bg->_left)
			{
				bg = bg->_left;
			}
			return (bg);
		}
		Map_Element	*setend(Map_Element *root, Map_Element *end)
		{
			Map_Element		*ed = root;
			if (!ed)
				return (end);
			while (ed->_right && ed->_right != end)
				ed = ed->_right;
			if (!ed->_right)
			{
				ed->_right = end;
				if (end->_parent->_right && end->_parent->_right == end)
					end->_parent->_right = NULL;
				end->_parent = ed;
			}
			return (end);
		}
		void		end(Map_Element *root)
		{
			Map_Element	*last = root;
			if (root->_right && root->_right != this)
				last = root->_right;
			last->_right = this;
			this->_parent = last;
		}
		Map_Element	*next(Map_Element *e)
		{
			Map_Element		*ptr = e;

			if (ptr->_right)
			{
				ptr = ptr->_right;
				while (ptr->_left)
					ptr = ptr->_left;
				return (ptr);
			}
			else if (ptr->_parent)
			{
				Map_Element		*buf = ptr;
				ptr = ptr->_parent;
				while (!_comp(buf->_val.first, ptr->_val.first))
				{
					buf = ptr;
					if (!ptr->_parent)
						return (NULL);
					ptr = ptr->_parent;
				}
				return (ptr);
			}
			return (NULL);
		}
		Map_Element	*prev(Map_Element *e)
		{
			Map_Element		*ptr = e;

			if (ptr->_left)
			{
				ptr = ptr->_left;
				while (ptr->_right)
					ptr = ptr->_right;
				return (ptr);
			}
			else
			{
				ptr = ptr->_parent;
				return (ptr);
			}
		}
		void		erase_leaf(Map_Element *ptr)
		{
			if (!ptr->parent())
				delete ptr;
			else if (ptr->parent()->right() && ptr->parent()->right() == ptr)
			{
				ptr->parent()->right() = NULL;
				delete ptr;
			}
			else
			{
				ptr->parent()->left() = NULL;
				delete ptr;
			}
		}
		void		erase_one(Map_Element *ptr, Map_Element **root, Map_Element **end)
		{
			if (!ptr->right() || ptr->right() == *end)
			{
				if (ptr->parent() && ptr->parent()->right() == ptr)
					ptr->parent()->right() = ptr->left();
				else if (ptr->parent())
					ptr->parent()->left() = ptr->left();
				else
					*root = ptr->left();
				ptr->left()->parent() = ptr->parent();
				delete ptr;
			}
			if (!ptr->left())
			{
				if (ptr->parent() && ptr->parent()->right() == ptr)
					ptr->parent()->right() = ptr->right();
				else if (ptr->parent())
					ptr->parent()->left() = ptr->right();
				else
					*root = ptr->right();
				ptr->right()->parent() = ptr->parent();
				delete ptr;
			}
		}
		void		erase_two(Map_Element *ptr, Map_Element *prev, Map_Element **root, Map_Element **end)
		{
			Map_Element		*p = ptr->_parent;
			Map_Element		*r = ptr->_right;
			Map_Element		*l = ptr->_left;
			int				pos = 0;

			if (p && p->_right && p->_right == ptr)
				pos = 1;
			else if (p && p->_left && p->_left == ptr)
				pos = 2;
			delete ptr;
			Map_Element		*replace = new Map_Element(prev->_val, l, r, p);
			r->_parent = replace;
			l->_parent = replace;
			if (pos == 0)
				*root = replace;
			if (pos== 1)
				p->_right = replace;
			else if (pos == 2)
				p->_left = replace;
			if (prev->left())
				erase_one(prev, root, end);
			else
				erase_leaf(prev);
		}
		Map_Element	*&right(void)
		{
			return (this->_right);
		}
		Map_Element	*&left(void)
		{
			return (this->_left);
		}
		Map_Element	*&parent(void)
		{
			return (this->_parent);
		}
		Map_Element const	*right(void) const
		{
			return (this->_right);
		}
		Map_Element	const	*left(void) const
		{
			return (this->_left);
		}
		Map_Element	const	*parent(void) const
		{
			return (this->_parent);
		}
		T		&value(void)
		{
			return (this->_val);
		}
		T const	&value(void) const
		{
			return (this->_val);
		}
		void	change_value(T const &value)
		{
			this->_val = value;
		}

	private:
		Map_Element	*_left;
		Map_Element	*_right;
		Map_Element	*_parent;
		T			_val;
		Compare		_comp;
};

#endif
