/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:32:26 by rturcey           #+#    #+#             */
/*   Updated: 2021/03/04 15:18:34 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "Element.hpp"
#include "ReverseIterator.hpp"

namespace	ft
{
	template <typename T, typename E>
	class	ListIterator
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
			ListIterator() : ptr(NULL) {}
			ListIterator(elt *ptr) : ptr(ptr) {}
			ListIterator(ListIterator const &src) : ptr(src.ptr) {}
			virtual			~ListIterator() {}

			elt				*get_ptr(void)
			{
				return (this->ptr);
			}
			ListIterator	&operator++()
			{
				this->ptr = this->ptr->next();
				return (*this);
			}
			ListIterator	&operator--()
			{
				this->ptr = this->ptr->prev();
				return (*this);
			}
			ListIterator	operator++(int)
			{
				ListIterator	stock(*this);
				this->ptr = this->ptr->next();
				return (stock);
			}
			ListIterator	operator--(int)
			{
				ListIterator	stock(*this);
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

			bool		operator==(ListIterator const &rhs) const
			{
				return (this->ptr == rhs.ptr);
			}
			bool		operator!=(ListIterator const &rhs) const
			{
				return (this->ptr != rhs.ptr);
			}
			bool		operator>(ListIterator const &rhs) const
			{
				return (this->ptr > rhs.ptr);
			}
			bool		operator<(ListIterator const &rhs) const
			{
				return (this->ptr < rhs.ptr);
			}
			bool		operator>=(ListIterator const &rhs) const
			{
				return (this->ptr >= rhs.ptr);
			}
			bool		operator<=(ListIterator const &rhs) const
			{
				return (this->ptr <= rhs.ptr);
			}
	};

	template < typename T>
	class	List
	{
		public:
			typedef T										value_type;
			typedef size_t									size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef T&										reference;
			typedef T const &								const_reference;
			typedef T *										pointer;
			typedef T const *								const_pointer;
			typedef Element<T>								elt;
			typedef ListIterator< T, Element<T> > 			iterator;
			typedef ListIterator<T const, Element<T> const> const_iterator;
			typedef ReverseIterator<iterator> 				reverse_iterator;
			typedef ReverseIterator<const_iterator> 		const_reverse_iterator;


			List()
			{
				this->init();
			}
			List(size_type count, const T &value = T())
			{
				this->init();
				this->assign(begin(), count, value);
			}
			List(const List &src)
			{
				this->init();
				this->assign(begin(), src.begin(), src.end());
			}
			List(iterator first, iterator last)
			{
				this->init();
				this->assign(begin(), first, last);
			}
			~List(void)
			{
				this->clear();
				delete this->_end;
			}

			void		init(void)
			{
				this->_end = new elt();
				this->_begin = this->_end;
				this->_end->next() = NULL;
				this->_end->prev() = NULL;
				this->_size = 0;
			}
			iterator		insert(iterator position, const value_type& val)
			{
				if (position == this->begin())
				{
					this->push_front(val);
					return (this->begin());
				}
				else if (position == this->end())
				{
					this->push_back(val);
					return (this->end());
				}
				else
				{
					elt		*insert = new elt(val);
					position.get_ptr()->push_before(insert);
					this->_size += 1;
					return (iterator(insert));
				}
			}
			void			insert(iterator position, size_type n, const value_type &val)
			{
				for (size_type i = 0 ; i < n ; i++)
				{
					this->insert(position, val);
				}
			}
			void			insert(iterator position, iterator first, iterator last)
			{
				for (iterator it = first ; it != last ; it++)
				{
					this->insert(position, *it);
				}
			}
			iterator		erase(iterator position)
			{
				if (position == this->begin())
				{
					this->pop_front();
					return (this->begin());
				}
				else if (position == this->end())
				{
					this->pop_back();
					return (this->end());
				}
				this->_size -= 1;
				elt		*next = position.get_ptr()->next();
				position.get_ptr()->detach();
				delete position.get_ptr();
				return (iterator(next));
			}
			iterator		erase(iterator first, iterator last)
			{
				while (first != last)
				{
					this->erase(first++);
				}
				return (first);
			}
			void			clear(void)
			{
				elt		*tmp;

				while (this->_begin != this->_end)
				{
					tmp = this->_begin->next();
					delete this->_begin;
					this->_begin = tmp;
				}
				this->_begin = this->_end;
				this->_end->prev() = NULL;
			}
			void			push_back(const T &value)
			{
				elt		*new_one = new elt(value);
				this->_end->push_before(new_one);
				if (!this->_size)
					this->_begin = new_one;
				this->_size += 1;
			}
			void			push_front(const T &value)
			{
				elt		*new_one = new elt(value);
				this->_begin->push_before(new_one);
				this->_begin = new_one;
				this->_size += 1;
			}
			void			pop_front(void)
			{
				if (this->empty())
					return ;
				if (this->_size > 1)
				{
					elt		*first = this->_begin->next();
					this->_begin->detach();
					delete this->_begin;
					this->_begin = first;
				}
				else
				{
					delete this->_begin;
					this->_begin = this->_end;
					this->_begin->prev() = NULL;
				}
				this->_size -= 1;
			}
			void			pop_back(void)
			{
				if (this->empty())
					return ;
				if (this->_size > 1)
				{
					elt		*last = this->_end->prev();
					this->_end->prev()->detach();
					delete last;
				}
				else
				{
					delete this->_begin;
					this->_begin = this->_end;
					this->_begin->prev() = NULL;
				}
				this->_size -= 1;
			}
			void			assign(iterator first, iterator last)
			{
				this->clear();
				while (first != last)
				{
					this->push_back(*first);
					first++;
				}
			}
			void			assign(size_type count, const T &value)
			{
				this->clear();
				for (size_type i = 0 ; i < count ; i++)
					this->push_back(value);
			}
			bool			empty(void)		const
			{
				if (this->_begin == this->_end)
					return (1);
				return (0);
			}
			void			swap(List &x)
			{
				elt		*ptr;
				ptr = this->_begin;
				this->_begin = x._begin;
				x._begin = ptr;
				ptr = this->_end;
				this->_end = x._end;
				x._end = ptr;
				size_t	size;
				size = this->_size;
				this->_size = x._size;
				x._size = size;
			}
			void			resize(size_type n, value_type val = value_type())
			{
				if (n < this->size())
				{
					iterator	it = this->begin();
					for (size_t i = 0 ; i < n ; i++)
						++it;
					this->erase(it, this->end());
				}
				else
					this->insert(this->end(), n - this->size(), val);
			}
			T 				front(void)		const
			{
				return (this->_begin->value());
			}
			T 				back(void)		const
			{
				return (this->_end->prev()->value());
			}
			size_type		size(void)		const
			{
				return (this->_size);
			}
			size_type		max_size(void)		const
			{
				return (std::numeric_limits<difference_type>::max() - std::numeric_limits<size_type>::max() / (sizeof(elt) - sizeof(T*)));
			}
			iterator		begin(void)
			{
				return (iterator(this->_begin));
			}
			iterator		end(void)
			{
				return (iterator(this->_end));
			}
			const_iterator	begin(void) const
			{
				return (const_iterator(this->_begin));
			}
			const_iterator	end(void) const
			{
				return (const_iterator(this->_end));
			}
			iterator		rbegin(void)
			{
				return (reverse_iterator(this->_end));
			}
			iterator		rend(void)
			{
				return (reverse_iterator(this->_begin));
			}
			const_iterator	rbegin(void) const
			{
				return (reverse_iterator(this->_end));
			}
			const_iterator	rend(void) const
			{
				return (reverse_iterator(this->_begin));
			}

			List &operator=(const List &rhs);



		private:
			elt					*_begin;
			elt					*_end;
			size_type			_size;


	};
}

#endif
