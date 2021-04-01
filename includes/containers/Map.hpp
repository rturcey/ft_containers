/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:32:26 by rturcey           #+#    #+#             */
/*   Updated: 2021/03/15 11:48:06 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "Map_Element.hpp"
#include "ReverseIterator.hpp"
#include "Utils.hpp"

namespace	ft
{
	template <class Key, typename T, class Compare = less<Key> >
	class	Map
	{
		public:
			typedef T										mapped_type;
            typedef Key										key_type;
            typedef std::pair<const key_type, mapped_type>		value_type;
            typedef Compare                                 key_compare;
			typedef size_t									size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef value_type&								reference;
			typedef value_type const &						const_reference;
			typedef value_type *							pointer;
			typedef value_type const *						const_pointer;
			typedef Map_Element<Key, T>						elt;
			typedef Iterator<value_type, elt>        			iterator;
			typedef Iterator<value_type, elt>                    const_iterator;
			typedef ReverseIterator<iterator> 				reverse_iterator;
			typedef ReverseIterator<const_iterator> 		const_reverse_iterator;


			explicit Map(const key_compare &comp = key_compare())
            {

            }
            template <class InputIterator>
            Map(InputIterator first, InputIterator last, const key_compare &comp = key_compare())
            {

            }
            Map(const map &x)
            {

            }
			{
				this->init();
			}
			~Map(void)
			{
				this->clear();
				delete this->_end;
			}
			void		init(void)
			{
				this->_end = new elt();
				this->_begin = this->_end;
				this->_end->right() = NULL;
				this->_end->left() = NULL;
				this->_end->parent() = NULL;
				this->_size = 0;
			}
			void		reset(void)
			{
				this->_begin = this->_end;
				this->_end->right() = NULL;
				this->_end->left() = NULL;
				this->_end->parent() = NULL;
			}
			std::pair<iterator, bool>	check_double_std::pair(const value_type& val, elt *root)
			{
				value_type		ret = NULL;
				if (!root)
					return (NULL);
				if (root->value().first == val.first)
					return (root->value());
				if ((ret = check_double(val, root->left())))
					return (ret);
				if ((ret = check_double(val, root->right())))
					return (ret);
			}
			iterator				check_double(const value_type& val, elt *root)
			{
				iterator		ret = end();
				if (!root)
					return (end());
				if (root->value().first == val.first)
					return (iterator(root));
				if ((ret = check_double(val, root->left())))
					return (ret);
				if ((ret = check_double(val, root->right())))
					return (ret);
			}
			std::pair<iterator, bool>	insert(const value_type& val)
			{
				value_type	ret;
				if ((ret = check_double_std::pair(val, _begin)))
					return (ret);
				elt			it = _begin;
				if (begin() == end())
				{
					_begin = new elt(val, _end);
					_size++;
					return ;
				}
				while (42)
				{
					if (comp(val.first, it.first))
					{
						if (it->left)
							it = it->left;
						else
						{
							it->left = new elt(val, it);
							_size++;
							return ;
						}
					}
					else
					{
						if (it->right)
							it = it->right;
						else
						{
							it->right = new elt(val, it);
							_size++;
							return ;
						}
					}
				}	
			}
			iterator		insert(iterator position, const value_type &val)
			{
				iterator		ret;

				if ((ret = check_double(val, _begin)) != end())
					return (ret);
				elt			it = *position;
				if (begin() == end())
				{
					_begin = new elt(val, _end);
					_size++;
					return ;
				}
				while (42)
				{
					if (comp(val.first, it.first))
					{
						if (it->left)
							it = it->left;
						else
						{
							it->left = new elt(val, it);
							_size++;
							return ;
						}
					}
					else
					{
						if (it->right)
							it = it->right;
						else
						{
							it->right = new elt(val, it);
							_size++;
							return ;
						}
					}
				}	
			}
				
			}
			template< class InputIt >
			void			insert(InputIt first, InputIt last)
			{
				for (iterator it = first ; it != last ; it++)
				{
					this->insert(first->get_ptr()->value());
				}
			}/*
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
				if (this->_size > 1)
				{
					elt		*first = this->_begin->next();
					this->_begin->detach();
					delete this->_begin;
					this->_begin = first;
					this->_size -= 1;
				}
				else if (this->_size == 1)
				{
					delete this->_begin;
					this->_begin = this->_end;
					this->_begin->prev() = NULL;
					this->_size -= 1;
				}
			}
			void			pop_back(void)
			{
				if (this->_size > 1)
				{
					elt		*last = this->_end->prev();
					this->_end->prev()->detach();
					delete last;
					this->_size -= 1;
				}
				else if (this->_size == 1)
				{
					delete this->_begin;
					this->_begin = this->_end;
					this->_begin->prev() = NULL;
					this->_size -= 1;
				}
			}
			template <class InputIt>
			void			assign(InputIt first, InputIt last)
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
			void			swap(Map &x)
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
			void			merge(Map &other, Compare comp)
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
			void			merge(Map &other)
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
			void			splice(iterator pos, Map &other)
			{
				this->splice(pos, other, other.begin(), other.end());
			}
			void			splice(iterator pos, Map &other, iterator it)
			{
				iterator	it2 = it;
				++it2;
				this->splice(pos, other, it, it2);
			}
			void			splice(iterator pos, Map &other, iterator first, iterator last)
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
					{
						this->_begin = tmp;
						tmp->prev() = NULL;
					}
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

				if (_size == 0)
					return ;
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

				if (_size == 0)
					return ;
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
				iterator	it = this->begin();
				iterator	itbis = it++;

				if (this->_size == 0)
					return ;
				while (it != this->end())
				{
					while (it != this->end() && *itbis == *it)
						it = this->erase(it);
					++itbis;
					it = itbis;
					if (it != this->end())
						++it;
				}
			}
			template<class BinaryPredicate>
			void			unique(BinaryPredicate p)
			{
				iterator	it = this->begin();
				iterator	itbis = it++;

				if (this->_size == 0)
					return ;
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
			T 				&front(void)		const
			{
				return (this->_begin->value());
			}
			T 				&back(void)			const
			{
				if (this->_size > 0)
					return (this->_end->prev()->value());
				return (this->_end->value());
			}
			size_type		size(void)		const
			{
				return (this->_size);
			}
			size_type		max_size(void)		const
			{
				return (std::numeric_limits<size_type>::max() / (sizeof(elt)));
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

			Map &operator=(const Map &rhs)
			{
				this->clear();
				this->assign(rhs.begin(), rhs.end());
				return (*this);
			}


*/
		private:
			elt					*_begin;
			elt					*_end;
			size_type			_size;


	};

	template<typename T>
	bool operator==(Map<T> const &lhs, Map<T> const &rhs)
	{
		if (lhs.size() != rhs.size())
			return (0);
		typename Map<T>::const_iterator beg = lhs.begin();
		typename Map<T>::const_iterator itend = lhs.end();
		typename Map<T>::const_iterator beg2 = rhs.begin();
		typename Map<T>::const_iterator itend2 = rhs.end();
		while (beg != itend)
		{
			if (*beg++ != *beg2++)
				return (0);
		}
		return (1);
	}
	template<typename T>
	bool operator!=(Map<T> const &lhs, Map<T> const &rhs)
	{
		if (lhs == rhs)
			return (0);
		return (1);
	}
	template<typename T>
	bool operator<(Map<T> const &lhs, Map<T> const &rhs)
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
	bool operator>(Map<T> const &lhs, Map<T> const &rhs)
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
	bool operator>=(Map<T> const &lhs, Map<T> const &rhs)
	{
		if (lhs.size() > rhs.size())
			return (1);
		if (ft::inf(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) <= 0)
			return (1);
		return (0);
	}
		template<typename T>
	bool operator<=(Map<T> const &lhs, Map<T> const &rhs)
	{
		if (lhs.size() < rhs.size())
			return (1);
		if (ft::inf(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) >= 0)
			return (1);
		return (0);
	}
	template<typename T>
	void	swap(Map<T> &lhs, Map<T> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
