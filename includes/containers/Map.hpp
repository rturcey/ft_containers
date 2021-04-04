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
			typedef Map_Element<value_type>					elt;
			typedef Iterator<value_type, elt>        		iterator;
			typedef Iterator<value_type, elt>                   const_iterator;
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
				*this = x;
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
			iterator				find(const key_type &k)
			{
				Map_Element<value_type>	*elm;

				if (!(elm = _begin->find(k)))
					return (this->end());
				return (iterator(elm));
			}
			const_iterator			find(const key_type &k) const
			{
				Map_Element<value_type>	*elm;

				if (!(elm = _begin->find(k)))
					return (this->end());
				return (const_iterator(elm));
			}
			mapped_type				&operator[](const key_type &k)
			{
				elt		*ret;
				if ((ret = _begin->find(k, _begin)))
					return (ret->value());
				else
				{
					ret = insert(std::make_pair(k, mapped_type()));
					return(ret->get_ptr->value());
				}
			}
			std::pair<iterator, bool>	check_double_pair(const value_type& val, elt *root)
			{
				std::pair<iterator, bool>	ret = NULL;
				if (!root)
					return (std::make_pair(root, 1));
				if (root->value().first == val.first)
					return (std::make_pair(iterator(root), 0));
				if ((ret = std::make_pair(check_double(val, root->left()), 0)))
					return (ret);
				if ((ret = std::make_pair(check_double(val, root->right()), 0)))
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
				if ((ret = check_double_pair(val, _begin)).second == 0)
					return (ret);
				elt			*it = _begin;
				if (begin() == end())
				{
					_begin = new elt(val, _end);
					_size++;
					return (std::make_pair(iterator(val), 1));
				}
				while (42)
				{
					if (comp(val.first, it->first))
					{
						if (it->left)
							it = it->left;
						else
						{
							it->left = new elt(val, it);
							_size++;
							return (std::make_pair(iterator(val), 1));
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
							return (std::make_pair(iterator(val), 1));
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
			template< class InputIt >
			void			insert(InputIt first, InputIt last)
			{
				for (iterator it = first ; it != last ; it++)
				{
					this->insert(*first);
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
			size_t		size()
			{
				return (this->_size);
			}
		private:
			elt					*_begin;
			elt					*_end;
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
