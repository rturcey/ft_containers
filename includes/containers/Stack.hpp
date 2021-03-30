/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:32:26 by rturcey           #+#    #+#             */
/*   Updated: 2021/03/15 11:48:06 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "Element.hpp"
#include "ReverseIterator.hpp"
#include "Utils.hpp"

namespace	ft
{
	template < typename T, class Container = ft::List<T> >
	class	Stack
	{
		public:
			typedef Container								container_type;
			typedef T										value_type;
			typedef size_t									size_type;

			explicit Stack(const Container &cont = Container()) : c(cont)
			{
			}
			~Stack(void)
			{
				c.clear();
			}
			void			push(const T &value)
			{
				c.push_back(value);
			}
			void			pop(void)
			{
				c.pop_back();
			}
			bool			empty(void)		const
			{
				return (c.empty());
			}
			void			swap(Stack &x)
			{
				c.swap(x);
			}
			T 				&top(void)			const
			{
				return (c.back());
			}
			size_type		size(void)		const
			{
				return (c.size());
			}
			Stack &operator=(const Stack &rhs)
			{
				c = rhs.c;
				return (*this);
			}

		private:
			Container		c;

			template <class A, class B>
			friend bool	operator==(const Stack<A, B> &lhs, const Stack<A, B> &rhs);

			template <class A, class B>
			friend bool	operator!=(const Stack<A, B> &lhs, const Stack<A, B> &rhs);

			template <class A, class B>
			friend bool	operator<(const Stack<A, B> &lhs, const Stack<A, B> &rhs);

			template <class A, class B>
			friend bool	operator<=(const Stack<A, B> &lhs, const Stack<A, B> &rhs);

			template <class A, class B>
			friend bool	operator>(const Stack<A, B> &lhs, const Stack<A, B> &rhs);
            
			template <class A, class B>
			friend bool	operator>=(const Stack<A, B> &lhs, const Stack<A, B> &rhs);
	};

	template < typename T, class Container>
	bool operator==(Stack<T, Container> const &lhs, Stack<T, Container> const &rhs)
	{
		if (lhs.c == rhs.c)
			return (1);
		return (0);
	}
	template < typename T, class Container>
	bool operator!=(Stack<T, Container> const &lhs, Stack<T, Container> const &rhs)
	{
		if (lhs == rhs)
			return (0);
		return (1);
	}
	template < typename T, class Container>
	bool operator<(Stack<T, Container> const &lhs, Stack<T, Container> const &rhs)
	{
		if (lhs.c < rhs.c)
			return (1);
		return (0);
	}
	template < typename T, class Container>
	bool operator>(Stack<T, Container> const &lhs, Stack<T, Container> const &rhs)
	{
		if (lhs.c > rhs.c)
			return (1);
		return (0);
	}
	template < typename T, class Container>
	bool operator>=(Stack<T, Container> const &lhs, Stack<T, Container> const &rhs)
	{
		if (lhs.c >= rhs.c)
			return (1);
		return (0);
	}
	template < typename T, class Container>
	bool operator<=(Stack<T, Container> const &lhs, Stack<T, Container> const &rhs)
	{
		if (lhs.c <= rhs.c)
			return (1);
		return (0);
	}
	template < typename T, class Container>
	void	swap(Stack<T, Container> &lhs, Stack<T, Container> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
