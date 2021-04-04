/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 09:40:30 by rturcey           #+#    #+#             */
/*   Updated: 2021/03/09 10:20:37 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

namespace	ft
{
	template<class It, class Itbis>
	int			inf(It beg, It itend, Itbis beg2, Itbis itend2)
	{
		while (beg != itend && beg2 != itend2)
		{
			if (*beg < *beg2)
				return (1);
			else if (*beg > *beg2)
				return (-1);
			beg++;
			beg2++;
		}
		return (0);
	};

	template <typename T, typename E>
	class	MapIterator
	{
		public:
			typedef T							value_type;
			typedef std::ptrdiff_t				difference_type;
			typedef T*							pointer;
			typedef T const *					const_pointer;
			typedef T&							reference;
			typedef T const &					const_reference;
			typedef	E							elt;

		protected:
			elt			*ptr;

		public:
			MapIterator() : ptr(NULL) {}
			MapIterator(elt *ptr) : ptr(ptr) {}
			MapIterator(MapIterator const &src) : ptr(src.ptr) {}
			virtual			~MapIterator() {}

			elt				*get_ptr(void) const
			{
				return (this->ptr);
			}
			MapIterator	&operator++()
			{
				this->ptr = this->ptr->next(this->ptr);
				return (*this);
			}
			MapIterator	&operator--()
			{
				this->ptr = this->ptr->prev();
				return (*this);
			}
			MapIterator	operator++(int)
			{
				MapIterator	stock(*this);
				this->ptr = this->ptr->next(this->ptr);
				return (stock);
			}
			MapIterator	operator--(int)
			{
				MapIterator	stock(*this);
				this->ptr = this->ptr->prev();
				return (stock);
			}
			T			&operator*() const
			{
				return (ptr->value());
			}
			bool		operator==(MapIterator const &rhs) const
			{
				return (this->ptr == rhs.ptr);
			}
			bool		operator!=(MapIterator const &rhs) const
			{
				return (this->ptr != rhs.ptr);
			}
			bool		operator>(MapIterator const &rhs) const
			{
				return (this->ptr > rhs.ptr);
			}
			bool		operator<(MapIterator const &rhs) const
			{
				return (this->ptr < rhs.ptr);
			}
			bool		operator>=(MapIterator const &rhs) const
			{
				return (this->ptr >= rhs.ptr);
			}
			bool		operator<=(MapIterator const &rhs) const
			{
				return (this->ptr <= rhs.ptr);
			}
	};

	template <typename T, typename E>
	class	Iterator
	{
		public:
			typedef T							value_type;
			typedef std::ptrdiff_t				difference_type;
			typedef T*							pointer;
			typedef T const *					const_pointer;
			typedef T&							reference;
			typedef T const &					const_reference;
			typedef	E							elt;

		protected:
			elt			*ptr;

		public:
			Iterator() : ptr(NULL) {}
			Iterator(elt *ptr) : ptr(ptr) {}
			Iterator(Iterator const &src) : ptr(src.ptr) {}
			virtual			~Iterator() {}

			elt				*get_ptr(void) const
			{
				return (this->ptr);
			}
			Iterator	&operator++()
			{
				this->ptr = this->ptr->next();
				return (*this);
			}
			Iterator	&operator--()
			{
				this->ptr = this->ptr->prev();
				return (*this);
			}
			Iterator	operator++(int)
			{
				Iterator	stock(*this);
				this->ptr = this->ptr->next();
				return (stock);
			}
			Iterator	operator--(int)
			{
				Iterator	stock(*this);
				this->ptr = this->ptr->prev();
				return (stock);
			}
			reference		operator*()
			{
				return (this->ptr->value());
			}
			elt				*elt_ptr(void)
			{
				return (this->ptr);
			}
			const_reference		operator*() const
			{
				return (this->ptr->value());
			}
			bool		operator==(Iterator const &rhs) const
			{
				return (this->ptr == rhs.ptr);
			}
			bool		operator!=(Iterator const &rhs) const
			{
				return (this->ptr != rhs.ptr);
			}
			bool		operator>(Iterator const &rhs) const
			{
				return (this->ptr > rhs.ptr);
			}
			bool		operator<(Iterator const &rhs) const
			{
				return (this->ptr < rhs.ptr);
			}
			bool		operator>=(Iterator const &rhs) const
			{
				return (this->ptr >= rhs.ptr);
			}
			bool		operator<=(Iterator const &rhs) const
			{
				return (this->ptr <= rhs.ptr);
			}
	};
}

#endif
