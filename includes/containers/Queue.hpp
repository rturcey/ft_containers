/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:32:26 by rturcey           #+#    #+#             */
/*   Updated: 2021/03/15 11:48:06 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include "Element.hpp"
#include "ReverseIterator.hpp"
#include "Utils.hpp"

namespace	ft
{
	template < typename T, class Container = ft::List<T> >
	class	Queue
	{
		public:
			typedef Container								container_type;
			typedef T										value_type;
			typedef size_t									size_type;

			explicit Queue(const Container &cont = Container()) : c(cont)
			{
			}
			~Queue(void)
			{
				c.clear();
			}
			void			push(const T &value)
			{
				c.push_back(value);
			}
			void			pop(void)
			{
				c.pop_front();
			}
			T				&front()
			{
				return (c.front());
			}
			const T 		&front() const
			{
				return (c.front());
			}
			bool			empty(void)		const
			{
				return (c.empty());
			}
			T 				&back(void)			const
			{
				return (c.back());
			}
			size_type		size(void)		const
			{
				return (c.size());
			}
			Queue &operator=(const Queue &rhs)
			{
				c = rhs.c;
				return (*this);
			}

		private:
			Container		c;

			template <class A, class B>
			friend bool	operator==(const Queue<A, B> &lhs, const Queue<A, B> &rhs);

			template <class A, class B>
			friend bool	operator!=(const Queue<A, B> &lhs, const Queue<A, B> &rhs);

			template <class A, class B>
			friend bool	operator<(const Queue<A, B> &lhs, const Queue<A, B> &rhs);

			template <class A, class B>
			friend bool	operator<=(const Queue<A, B> &lhs, const Queue<A, B> &rhs);

			template <class A, class B>
			friend bool	operator>(const Queue<A, B> &lhs, const Queue<A, B> &rhs);
            
			template <class A, class B>
			friend bool	operator>=(const Queue<A, B> &lhs, const Queue<A, B> &rhs);
	};

	template < typename T, class Container>
	bool operator==(Queue<T, Container> const &lhs, Queue<T, Container> const &rhs)
	{
		if (lhs.c == rhs.c)
			return (1);
		return (0);
	}
	template < typename T, class Container>
	bool operator!=(Queue<T, Container> const &lhs, Queue<T, Container> const &rhs)
	{
		if (lhs == rhs)
			return (0);
		return (1);
	}
	template < typename T, class Container>
	bool operator<(Queue<T, Container> const &lhs, Queue<T, Container> const &rhs)
	{
		if (lhs.c < rhs.c)
			return (1);
		return (0);
	}
	template < typename T, class Container>
	bool operator>(Queue<T, Container> const &lhs, Queue<T, Container> const &rhs)
	{
		if (lhs.c > rhs.c)
			return (1);
		return (0);
	}
	template < typename T, class Container>
	bool operator>=(Queue<T, Container> const &lhs, Queue<T, Container> const &rhs)
	{
		if (lhs.c >= rhs.c)
			return (1);
		return (0);
	}
	template < typename T, class Container>
	bool operator<=(Queue<T, Container> const &lhs, Queue<T, Container> const &rhs)
	{
		if (lhs.c <= rhs.c)
			return (1);
		return (0);
	}
}

#endif
