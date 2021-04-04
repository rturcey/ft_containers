/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map_Element.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:05:58 by rturcey           #+#    #+#             */
/*   Updated: 2021/03/15 10:48:20 by rturcey          ###   ########.fr       */
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

		Map_Element	*find(T key, Map_Element *root)
		{
			if (!root)
				return (NULL);
			if (root->_val.first == key.first)
				return (root);
			find(key, root->_left);
			find(key, root->_right);
			return (NULL);
		}
		Map_Element &operator=(const Map_Element &rhs)
		{
			this->_left = rhs._left;
			this->_right = rhs._right;
			this->_parent = rhs._parent;
			this->_val = rhs.data;
		}
		ft::MapIterator<T, Map_Element>	push(Map_Element *root, Map_Element **nend, Map_Element **begin, T val)
		{
			Map_Element		*stock = root;
			Map_Element		*i = stock;
			while (stock)
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
				i->_left->_parent = i;
				stock = i->_left;
			}
			else
			{
				i->_right = new Map_Element(val, i);			
				i->_right->_parent = i;
				stock = i->_right;
			}
			while ((*begin)->_left)
			{
				*begin = (*begin)->_left;
			}
			*nend = end(root, *nend);
			return (stock);
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
		Map_Element	*end(Map_Element *root, Map_Element *oldend) {

				Map_Element *newend = root;
				if (newend->_right && newend->_right != oldend)
					newend = newend->_right;
				return (newend);
			};
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
