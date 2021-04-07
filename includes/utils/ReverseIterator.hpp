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

template <typename It>
class	ReverseIterator : public It
{
	public:
		using typename It::value_type;
		ReverseIterator(void) : It() {}
		ReverseIterator(It const &iterator) : It(iterator) {}
		ReverseIterator(ReverseIterator const &src) : It(src.ptr) {}

		ReverseIterator 	&operator=(const ReverseIterator &rhs)
		{
			this->ptr = rhs.ptr;
			return (*this);
		}
		It			&operator++(void)
		{
			return (this->It::operator--());
		}
		It			&operator--(void)
		{
			return (this->It::operator++());
		}
		ReverseIterator		operator++(int)
		{
			ReverseIterator	it(*this);
			this->It::operator--();
			return (it);
		}
		ReverseIterator		operator--(int)
		{
			ReverseIterator	it(*this);
			this->It::operator++();
			return (it);
		}
		value_type			*operator->(void)
		{
			It	it(*this);
			return (&(*--it));
		}
		value_type const	*operator->(void) const
		{
			It	it(*this);
			return (&(*--it));
		}
		value_type			&operator*(void)
		{
			It	it(*this);
			return (*--it);
		}

	private:

};

#endif
