/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Element.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:05:58 by rturcey           #+#    #+#             */
/*   Updated: 2021/03/15 10:48:20 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <limits>

template <typename T>
class	Element
{
	public:
		Element(void) : _prev(NULL), _next(NULL), _data() {}
		Element(const T &data) : _prev(NULL), _next(NULL), _data(data) {}
		Element(const T &data, Element *prev, Element *next) : _prev(prev), _next(next), _data(data) {}
		Element(Element const &src) : _prev(src._prev), _next(src._next), _data(src._data) {}

		Element &operator=(const Element &rhs)
		{
			this->_prev = rhs.prev;
			this->_next = rhs.next;
			this->_data = rhs.data;
		}
		void	detach(void)
		{
			if (this->_prev)
				this->_prev->_next = this->_next;
			if	(this->_next)
				this->_next->_prev = this->_prev;
		}
		void	push_before(Element *elt)
		{
			if (this->_prev)
			{
				elt->_prev = this->_prev;
				this->_prev->_next = elt;
			}
			elt->_next = this;
			this->_prev = elt;
		}
		Element	*&next(void)
		{
			return (this->_next);
		}
		Element	*&prev(void)
		{
			return (this->_prev);
		}
		Element const	*next(void) const
		{
			return (this->_next);
		}
		Element	const	*prev(void) const
		{
			return (this->_prev);
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
		Element	*_prev;
		Element	*_next;
		T		_data;
};

#endif
