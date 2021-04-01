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

#include <limits>

template <typename T>
class	Map_Element
{
	public:
		Map_Element(void) : _left(NULL), _right(NULL), parent(NULL), _data() {}
		Map_Element(const T &data) : _left(NULL), _right(NULL), parent(NULL), _data(data) {}
		Map_Element(const T &data, Map_Element *left, Map_Element *right, Map_Element *parent) : _left(left), _right(right), parent(NULL), _data(data) {}
		Map_Element(const T &data, Map_Element *parent) : _left(NULL), _right(NULL), parent(parent), _data(data) {}
		Map_Element(Map_Element const &src) : _left(src._left), _right(src._right), _parent(src._parent), _data(src._data) {}

		Map_Element &operator=(const Map_Element &rhs)
		{
			this->_left = rhs._left;
			this->_right = rhs._right;
			this->_parent = rhs._parent;
			this->_data = rhs.data;
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
			return (this->_data);
		}
		T const	&value(void) const
		{
			return (this->_data);
		}
		void	change_value(T const &value)
		{
			this->_data = value;
		}

	private:
		Map_Element	*_left;
		Map_Element	*_right;
		Map_Element	*parent;
		T			_data;
};

#endif
