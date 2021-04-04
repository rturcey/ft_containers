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
	template <class Key, typename T, class Compare = std::less<Key> >
	class	Map
	{
		public:
			typedef T										mapped_type;
            typedef Key										key_type;
            typedef std::pair<const key_type, mapped_type>	value_type;
            typedef Compare                                 key_compare;
			typedef size_t									size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef value_type&								reference;
			typedef value_type const &						const_reference;
			typedef value_type *							pointer;
			typedef value_type const *						const_pointer;
			typedef Map_Element<key_type, value_type, key_compare>	elt;
			typedef MapIterator<value_type, elt>        		iterator;
			typedef MapIterator<value_type, elt>                   const_iterator;
			typedef ReverseIterator<iterator> 				reverse_iterator;
			typedef ReverseIterator<const_iterator> 		const_reverse_iterator;

			explicit Map(const key_compare &comp = key_compare()) : _comp(comp)
            {
				this->init();
            }
            template <class InputIterator>
            Map(InputIterator first, InputIterator last, const key_compare &comp = key_compare()) : _comp(comp)
            {
				this->init();
				this->insert(first, last);
            }
            Map(const Map &x)
            {
				this->init();
				insert(x.begin(), x.end());
            }
			~Map(void)
			{
			//	this->clear();
				delete this->_end;
			}
			void		init(void)
			{
				this->_end = new elt();
				this->_begin = this->_end;
				this->_root = _end;
				this->_end->right() = NULL;
				this->_end->left() = NULL;
				this->_end->parent() = NULL;
				this->_size = 0;
			}
			void		reset(void)
			{
				this->_begin = this->_end;
				this->_root = this->_end;
				this->_end->right() = NULL;
				this->_end->left() = NULL;
				this->_end->parent() = NULL;
			}
			iterator				find(const key_type &k)
			{
				elt		*elm;

				if (!(elm = _root->find(std::make_pair(k, mapped_type()), _begin)))
					return (this->end());
				return (iterator(elm));
			}
			const_iterator			find(const key_type &k) const
			{
				elt		*elm;

				if (!(elm = _root->find(std::make_pair(k, mapped_type()), _begin)))
					return (this->end());
				return (const_iterator(elm));
			}
			mapped_type				&operator[](const key_type &k)
			{
				iterator	it;
				if ((it = find(k)) != end())
					return (it.get_ptr()->value().second);
				else
				{
					it = insert(std::make_pair(k, mapped_type())).first;
					return(it.get_ptr()->value().second);
				}
			}
			
			std::pair<iterator, bool>	insert(const value_type& val)
			{
				iterator	ret;
				if ((ret = find(val.first)) != end())
					return (std::make_pair(ret, 0));
				if (_size)
					return (std::make_pair(_root->push(_root, &_end, &_begin, val), 1));
				else
				{
					_root = new elt(val);
					_root->right() = _end;
					_begin = _root;
					_end->parent() = _root;
					_size++;
				}
				return (std::make_pair(iterator(_root), 1));
			}
			iterator		insert(iterator position, const value_type &val)
			{
				elt *e;

				if (_size && (e = _root->find(val, position.get_ptr())))
					return (iterator(e));
				std::pair<iterator,bool> tup = insert(val);
				return (tup.first);
			}
			template< class InputIt >
			void			insert(InputIt first, InputIt last)
			{
				while (first != last)
				{
					this->insert(*first);
					first++;
				}
			}
			iterator	begin()
			{
				return (iterator(this->_begin));
			}
			iterator	end()
			{
				return (iterator(this->_end));
			}
			const_iterator	begin() const
			{
				return (iterator(this->_begin));
			}
			const_iterator	end() const
			{
				return (iterator(this->_end));
			}
			size_t		size()
			{
				return (this->_size);
			}
		private:
			elt					*_begin;
			elt					*_end;
			elt					*_root;
			size_type			_size;
			key_compare			_comp;


	};

	/*template<typename T>
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
	}*/
}

#endif
