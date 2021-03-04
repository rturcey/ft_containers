/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:34:55 by rturcey           #+#    #+#             */
/*   Updated: 2021/02/09 11:04:29 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSEITERATOR_HPP
#define REVERSEITERATOR_HPP

template <typename Iterator>
class	ReverseIterator : public Iterator
{
	public:
		using typename Iterator::value_type;
		ReverseIterator(void) : Iterator() {}
		ReverseIterator(Iterator const &iterator) : Iterator(iterator) {}
		ReverseIterator(ReverseIterator const &src) : Iterator(src.ptr) {}

		ReverseIterator 	&operator=(const ReverseIterator &rhs)
		{
			this->ptr = rhs.ptr;
			return (*this);
		}
		Iterator			&operator++(void)
		{
			return (this->Iterator::operator--());
		}
		Iterator			&operator--(void)
		{
			return (this->Iterator::operator++());
		}
		ReverseIterator		operator++(int)
		{
			ReverseIterator	it(*this);
			this->Iterator::operator--();
			return (it);
		}
		ReverseIterator		operator--(int)
		{
			ReverseIterator	it(*this);
			this->Iterator::operator++();
			return (it);
		}
		value_type			*operator->(void)
		{
			Iterator	it(*this);
			return (&(*--it));
		}
		value_type const	*operator->(void) const
		{
			Iterator	it(*this);
			return (&(*--it));
		}
		value_type			&operator*(void)
		{
			Iterator	it(*this);
			return (*--it);
		}

	private:

};

#endif
