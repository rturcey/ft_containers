/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:32:26 by rturcey           #+#    #+#             */
/*   Updated: 2021/03/15 11:48:06 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "ReverseIterator.hpp"
#include "Utils.hpp"

namespace	ft
{
	template <typename T, typename E>
	class	VectorIterator
	{
		public:
			typedef T							value_type;
			typedef std::ptrdiff_t				difference_type;
			typedef T*							pointer;
			typedef T const *					const_pointer;
			typedef T&							reference;
			typedef T const &					const_reference;

		protected:
			T			*ptr;

		public:
			VectorIterator() : ptr(NULL) {}
			VectorIterator(T *ptr) : ptr(ptr) {}
			VectorIterator(VectorIterator const &src) : ptr(src.ptr) {}
			virtual			~VectorIterator() {}

			VectorIterator	&operator++()
			{
				++this->ptr;
				return (*this);
			}
			VectorIterator	&operator--()
			{
				--this->ptr;
				return (*this);
			}
			VectorIterator	operator++(int)
			{
				VectorIterator	stock(*this);
				++this->ptr;
				return (stock);
			}
			VectorIterator	operator--(int)
			{
				VectorIterator	stock(*this);
				--this->ptr;
				return (stock);
			}
			reference		operator*()
			{
				return (*this->ptr);
			}
			const_reference	operator*() const
			{
				return (*this->ptr);
			}
			VectorIterator	&operator+=(int val)
			{
				this->p += val;
				return (*this);
			}
			VectorIterator	&operator-=(int val)
			{
				this->p -= val;
				return (*this);
			}
			VectorIterator	operator+(int val) const
			{
				VectorIterator tmp(*this);
				return (tmp += val);
			}
			VectorIterator	operator-(int val) const
			{
				VectorIterator tmp(*this);
				return (tmp -= val);
			}
			difference_type	operator-(VectorIterator const &rhs) const
			{
				return (this->ptr - rhs.ptr);
			}
			reference		operator[](int val)
			{
				return (*(this->ptr + val));
			}
			const_reference	operator[](int val) const
			{
				return (*(this->ptr + val));
			}
			pointer			operator->()
			{
				return (*this->ptr);
			}
			const_pointer	operator->() const
			{
				return (*this->ptr);
			}
			bool		operator==(VectorIterator const &rhs) const
			{
				return (this->ptr == rhs.ptr);
			}
			bool		operator!=(VectorIterator const &rhs) const
			{
				return (this->ptr != rhs.ptr);
			}
			bool		operator>(VectorIterator const &rhs) const
			{
				return (this->ptr > rhs.ptr);
			}
			bool		operator<(VectorIterator const &rhs) const
			{
				return (this->ptr < rhs.ptr);
			}
			bool		operator>=(VectorIterator const &rhs) const
			{
				return (this->ptr >= rhs.ptr);
			}
			bool		operator<=(VectorIterator const &rhs) const
			{
				return (this->ptr <= rhs.ptr);
			}
	};

	template < typename T>
	class	Vector
	{
		public:
			typedef T											value_type;
			typedef size_t										size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef T&											reference;
			typedef T const &									const_reference;
			typedef T *											pointer;
			typedef T const *									const_pointer;
			typedef VectorIterator< T, Element<T> > 			iterator;
			typedef VectorIterator<T const, Element<T> const>	const_iterator;
			typedef ReverseIterator<iterator> 					reverse_iterator;
			typedef ReverseIterator<const_iterator> 			const_reverse_iterator;


			Vector() : _capacity(0), _size(0), _vector(NULL)
			{
			}
			Vector(size_type count, const T &value = T()) : _capacity(count), _size(count), _vector(NULL)
			{
				this->assign(count, value);
			}
			Vector(const Vector &src) : _vector(NULL)
			{
				const_iterator	first = src.begin();
				int		i = 0;

				while (first++ != src.end())
					i++;
				_capacity = i;
				_size = i;
				this->assign(src.begin(), src.end());
			}
			template <class InputIt>
			Vector(InputIt first, InputIt last) : _capacity(0), _size(0), _vector(NULL)
			{
				InputIt	cpy = first;
				int		i = 0;

				while (cpy++ != last)
					i++;
				_capacity = i;
				_size = i;
				this->assign(first, last);
			}
			~Vector(void)
			{
				this->clear();
			}
			iterator		insert(iterator position, const value_type& val)
			{
				size_type		i = 0;
				iterator		ret = this->begin();
				if (position != ret)
					while (ret++ != position)
						i++;
				if (_size + 1 > _capacity && _size + 1 <= _capacity * 2)
					reserve(_capacity * 2);
				else
					reserve(_size + 1);
				ret = iterator(&_vector[i]);
				T	next;
				T	stock = _vector[i];
				_vector[i++] = val;
				while (i < _size)
				{
					next = _vector[i];
					_vector[i++] = stock;
					stock = next;
				}
				if (_size)
					_vector[i++] = stock;
				this->_size += 1;
				return (ret);
			}
			void			insert(iterator position, size_type n, const value_type &val)
			{
				iterator		it = this->begin();
				size_type		i = 0;
				if (it != position)
					while (it++ != position)
						i++;
				if (_size + n > _capacity && _size + n <= _capacity * 2)
					reserve(_capacity * 2);
				else
					reserve(_size + n);
				it = this->begin();
				for (size_type j = 0 ; j < i ; j++)
					it++;
				for (size_type id = 0 ; id < n ; id++)
					it = this->insert(it, val);
			}
			template< class InputIt >
			void			insert(InputIt position, InputIt first, InputIt last)
			{
				iterator		it = this->begin();
				size_type		i = 0;
				if (it != position)
					while (it++ != position)
						i++;
				iterator	stock = first;
				size_type	t = _size;
				while (stock++ != last)
					t++;
				if (_size + (last - first) > _capacity && _size + (last - first) <= _capacity * 2)
					reserve(_capacity * 2);
				else
					reserve(_size + (last - first));
				size_type		j = 0;
				T*		buf = new T[t];
				while (j != i)
				{
					buf[j] = _vector[j];
					j++;
				}
				while (first != last)
				{
					buf[j++] = *first;
					first++;
				}
				while (i != _size)
					buf[j++] = _vector[i++];
				delete [] _vector;
				_vector = buf;
				_size = j;
			}
			iterator		erase(iterator position)
			{
				if (_size == 0 || position == this->end())
					return (this->end());
				iterator	it = position;

				it++;
				if (it == this->end())
					*position = T();
				int	i = 0;
				for (iterator itb = this->begin() ; itb != position ; itb++)
					i++;
				while (it != this->end())
				{
					*position = *it;
					position++;
					it++;
				}
				this->_size--;
				return (iterator(&(_vector[i])));
			}
			iterator		erase(iterator first, iterator last)
			{
				size_type		cut = (last - first);
				iterator		it = first;
				
				it++;
				if (it == this->end())
					*first = T();
				int	i = 0;
				for (iterator itb = this->begin() ; itb != first ; itb++)
					i++;
				while (first != last && it != this->end())
				{
					*first = *it;
					first++;
					it++;
				}
				this->_size -= cut;
				return (iterator(&(_vector[i])));
			}
			void			clear(void)
			{
				delete[] this->_vector;
				_size = 0;
				_capacity = 0;
			}
			void			push_back(const T &value)
			{
				if (_size + 1 > _capacity && _size + 1 <= _capacity * 2)
					reserve(_capacity * 2);
				else
					reserve(_size + 1);
				this->_vector[_size] = value;
				this->_size++;
			}
			void			pop_back(void)
			{
				if (this->_size == 1)
					delete[] _vector;
				else if (this->_size > 1)
				{
					this->_size--;
					this->_vector[_size] = T();
				}
			}
			template <class InputIt>
			void			assign(InputIt first, InputIt last)
			{
				size_type	cp = _capacity;
				this->clear();
				this->_vector = new T[cp];
				_capacity = cp;
				while (first != last)
				{
					this->push_back(*first);
					first++;
				}
			}
			void			assign(size_type count, const T &value)
			{
				size_type	cp = _capacity;
				this->clear();
				this->_vector = new T[cp];
				_capacity = cp;
				for (size_type i = 0 ; i < count ; i++)
					this->push_back(value);
			}
			bool			empty(void)		const
			{
				if (this->_size == 0)
					return (1);
				return (0);
			}
			void			swap(Vector &x)
			{
				T		*ptr;
				ptr = x._vector;
				x._vector = this->_vector;
				this->_vector = ptr;
			}
			void			resize(size_type n, value_type val = value_type())
			{
				if (n < this->size())
				{
					iterator	it = this->begin();
					for (size_type i = 0 ; i < n ; i++)
						it++;
					this->erase(it,this->end());
				}
				else
					this->insert(this->end(), n - this->size(), val);
			}
			T 				&front(void)		const
			{
				return (this->_vector[0]);
			}
			T 				&back(void)			const
			{
				return (this->_vector[_size - 1]);
			}
			size_type		size(void)		const
			{
				return (this->_size);
			}
			size_type		capacity(void)		const
			{
				return (this->_capacity);
			}
			size_type		max_size(void)		const
			{
				size_type diff = std::numeric_limits<difference_type>::max();
				size_type val = std::numeric_limits<size_type>::max() / (sizeof(T));
				if (diff < val)
					return (diff);
				return (val);
			}
			iterator		begin(void)
			{
				return (iterator(this->_vector));
			}
			iterator		end(void)
			{
				return (iterator(&(this->_vector[this->_size])));
			}
			const_iterator	begin(void) const
			{
				return (const_iterator(this->_vector));
			}
			const_iterator	end(void) const
			{
				return (const_iterator(&(this->_vector[this->_size])));
			}
			iterator		rbegin(void)
			{
				return (reverse_iterator(this->end()));
			}
			iterator		rend(void)
			{
				return (reverse_iterator(this->begin()));
			}
			const_iterator	rbegin(void) const
			{
				return (reverse_iterator(this->end()));
			}
			const_iterator	rend(void) const
			{
				return (reverse_iterator(this->begin()));
			}

			Vector &operator=(const Vector &rhs)
			{
				this->assign(rhs.begin(), rhs.end());
				return (*this);
			}

			T 		operator[](size_type pos)
			{
				iterator	it;

				it = begin();
				for (size_type i = 0 ; i < _size ; i++)
				{
					if (i == pos)
						return (*it);
					it++;
				}
				return (0);
			}
			reference at(size_type pos)
			{
				if (pos < 0 || pos > _size - 1)
					throw std::out_of_range("vector");
				return (this->_vector[pos]);
				
			}
			const_reference at(size_type pos) const
			{
				if (pos < 0 || pos > _size - 1)
					throw std::out_of_range("vector");
				return (this->_vector[pos]);
				
			}
			T const	operator[](size_type pos) const
			{
				const_iterator	it;

				it = begin();
				for (size_type i = 0 ; i < _size ; i++)
				{
					if (i == pos)
						return (*it);
					it++;
				}
				return (NULL);
			}
			void	reserve(size_type new_cap)
			{
				if (new_cap <= _capacity)
					return ;
				T*	cpy = new T[new_cap];
				for (size_type i = 0 ; i < _size ; i++)
					cpy[i] = _vector[i];
				if (_capacity)
					delete[] _vector;
				_capacity = new_cap;
				_vector = cpy;
			}


		private:
			size_type			_capacity;
			size_type			_size;
			T					*_vector;


	};

	template<typename T>
	bool operator==(Vector<T> const &lhs, Vector<T> const &rhs)
	{
		if (lhs.size() != rhs.size())
			return (0);
		typename Vector<T>::const_iterator beg = lhs.begin();
		typename Vector<T>::const_iterator itend = lhs.end();
		typename Vector<T>::const_iterator beg2 = rhs.begin();
		typename Vector<T>::const_iterator itend2 = rhs.end();
		while (beg != itend)
		{
			if (*beg++ != *beg2++)
				return (0);
		}
		return (1);
	}
	template<typename T>
	bool operator!=(Vector<T> const &lhs, Vector<T> const &rhs)
	{
		if (lhs == rhs)
			return (0);
		return (1);
	}
	template<typename T>
	bool operator<(Vector<T> const &lhs, Vector<T> const &rhs)
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
	bool operator>(Vector<T> const &lhs, Vector<T> const &rhs)
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
	bool operator>=(Vector<T> const &lhs, Vector<T> const &rhs)
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
	bool operator<=(Vector<T> const &lhs, Vector<T> const &rhs)
	{
		if (lhs.size() <= rhs.size())
			return (1);
		else
			return (0);
		if (ft::inf(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) >= 0)
			return (1);
		return (0);
	}
	template<typename T>
	void	swap(Vector<T> &lhs, Vector<T> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
