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

template <typename T>
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
		Map_Element	*next()
		{
			Map_Element		*ptr;

			if (_left)
				return (_left);
			if (_right)
				return (_right);
			while (42)
			{
				if (_parent)
				{
					ptr = _parent;
					while (ptr && !_right)
						ptr = _parent;
					if (ptr && ptr->_right)
						return (ptr->_right);
					return (NULL);
				}
				else
					return (NULL);
			}
			return (NULL);
		}
		Map_Element	*prev()
		{
			Map_Element		*ptr;
			
			if (_right)
				return (_right);
			if (_left)
				return (_left);
			while (42)
			{
				if (_parent)
				{
					ptr = _parent;
					while (ptr && !_left)
						ptr = _parent;
					if (ptr && ptr->_left)
						return (ptr->_left);
					return (NULL);
				}
				else
					return (NULL);
			}
			return (NULL);
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
};

#endif
