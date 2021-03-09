/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:32:26 by rturcey           #+#    #+#             */
/*   Updated: 2021/03/09 10:22:51 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "Element.hpp"
#include "ReverseIterator.hpp"
#include "Utils.hpp"

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

			elt				*get_ptr(void) const
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
			const_reference		operator*() const
			{
				return (this->ptr->value());
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
			void		reset(void)
			{
				this->_begin = this->_end;
				this->_end->next() = NULL;
				this->_end->prev() = NULL;
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
				this->erase(this->begin(), this->end());
				this->reset();
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
			template<class Compare>
			void			merge(List &other, Compare comp)
			{
				if (*this == other)
					return ;
				iterator	it = this->begin();
				iterator	itbis = other.begin();
				while (itbis != other.end())
				{
					if (it == this->end())
					{
						splice(it, other);
						return ;
					}
					else if (comp(*itbis, *it))
					{
						splice(it, other, itbis);
						itbis = other.begin();
					}
					else
						it++;
				}
			}
			void			merge(List &other)
			{
				if (*this == other)
					return ;
				iterator	it = this->begin();
				iterator	itbis = other.begin();
				while (itbis != other.end())
				{
					if (it == this->end())
					{
						splice(it, other);
						return ;
					}
					else if (*itbis < *it)
					{
						splice(it, other, itbis);
						itbis = other.begin();
					}
					else
						it++;
				}
			}
			void			splice(iterator pos, List &other)
			{
				this->splice(pos, other, other.begin(), other.end());
			}
			void			splice(iterator pos, List &other, iterator it)
			{
				iterator	it2 = it;
				++it2;
				this->splice(pos, other, it, it2);
			}
			void			splice(iterator pos, List &other, iterator first, iterator last)
			{
				elt	*tmp;

				while (first != last)
				{
					tmp = first++.get_ptr();
					if (tmp == other._begin)
						other._begin = tmp->next();
					tmp->detach();
					pos.get_ptr()->push_before(tmp);
					if (pos.get_ptr() == this->_begin)
						this->_begin = tmp;
					this->_size++;
					other._size--;
				}
				if (other._size == 0)
					other.reset();
			}
			void			reverse(void)
			{
				iterator	it = this->begin();
				iterator	itbis = this->end();
				T			value;

				--itbis;
				for (size_t i = 0 ; i < _size / 2 ; i++)
				{
					value = *itbis;
					itbis.get_ptr()->change_value(*it);
					it.get_ptr()->change_value(value);
					++it;
					--itbis;
				}
			}
			template<class Compare>
			void sort(Compare comp)
			{
				int			lever = 0;
				T			value;
				iterator	it = this->begin();
				iterator	itbis = it++;

				while (it != this->end())
				{
					if (comp(*it, *itbis))
					{
						value = *itbis;
						itbis.get_ptr()->change_value(*it);
						it.get_ptr()->change_value(value);
						lever = 1;
					}
					++it;
					++itbis;
				}
				if (lever == 1)
					this->sort(comp);
			}
			void			sort(void)
			{
				int			lever = 0;
				T			value;
				iterator	it = this->begin();
				iterator	itbis = it++;

				while (it != this->end())
				{
					if (*itbis > *it)
					{
						value = *itbis;
						itbis.get_ptr()->change_value(*it);
						it.get_ptr()->change_value(value);
						lever = 1;
					}
					++it;
					++itbis;
				}
				if (lever == 1)
					this->sort();
			}
			void			unique(void)
			{
				iterator	it = this->_begin;
				iterator	itbis = it++;

				while (it != this->_end)
				{
					while (it != this->_end && *itbis == *it)
						it = this->erase(it);
					++itbis;
					it = itbis;
					if (it != this->_end)
						++it;
				}
			}
			template<class BinaryPredicate>
			void			unique(BinaryPredicate p)
			{
				iterator	it = this->begin();
				iterator	itbis = it++;

				while (it != this->end())
				{
					while (it != this->end() && p(*it, *itbis))
						it = this->erase(it);
					++itbis;
					it = itbis;
					if (it != this->end())
						++it;
				}
			}
			template<class UnaryPredicate>
			void			remove_if(UnaryPredicate p)
			{
				iterator		it = this->begin();

				while (it != this->end())
				{
					if (p(*it))
						it = this->erase(it);
					else
						++it;
				}
			}
			void			remove(const T &value)
			{
				iterator		it = this->begin();

				while (it != this->end())
				{
					if (*it == value)
						it = this->erase(it);
					else
						++it;
				}
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

	template<typename T>
	bool operator==(List<T> const &lhs, List<T> const &rhs)
	{
		if (lhs.size() != rhs.size())
			return (0);
		typename List<T>::const_iterator beg = lhs.begin();
		typename List<T>::const_iterator itend = lhs.end();
		typename List<T>::const_iterator beg2 = rhs.begin();
		typename List<T>::const_iterator itend2 = rhs.end();
		while (beg != itend)
		{
			if (*beg++ != *beg2++)
				return (0);
		}
		return (1);
	}
	template<typename T>
	bool operator!=(List<T> const &lhs, List<T> const &rhs)
	{
		if (lhs == rhs)
			return (0);
		return (1);
	}
	template<typename T>
	bool operator<(List<T> const &lhs, List<T> const &rhs)
	{
		if (lhs.size() < rhs.size())
			return (1);
		else if (lhs.size() != rhs.size())
			return (0);
		if (ft::inf(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) == 1)
			return (1);
		return (0);
	}
	template<typename T>
	bool operator>(List<T> const &lhs, List<T> const &rhs)
	{
		if (lhs.size() > rhs.size())
			return (1);
		else if (lhs.size() != rhs.size())
			return (0);
		if (ft::inf(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) == -1)
			return (1);
		return (0);
	}
	template<typename T>
	bool operator>=(List<T> const &lhs, List<T> const &rhs)
	{
		if (lhs.size() >= rhs.size())
			return (1);
		else
			return (0);
		if (ft::inf(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) <= 0)
			return (1);
		return (0);
	}
		template<typename T>
	bool operator<=(List<T> const &lhs, List<T> const &rhs)
	{
		if (lhs.size() <= rhs.size())
			return (1);
		else
			return (0);
		if (ft::inf(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) >= 0)
			return (1);
		return (0);
	}

}

#endif
