/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:32:26 by rturcey           #+#    #+#             */
/*   Updated: 2021/04/07 14:48:02 by rturcey          ###   ########.fr       */
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
			typedef T												mapped_type;
            typedef Key												key_type;
            typedef std::pair<const key_type, mapped_type>			value_type;
            typedef Compare                                			key_compare;
			typedef size_t											size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef value_type&										reference;
			typedef value_type const &								const_reference;
			typedef value_type *									pointer;
			typedef value_type const *								const_pointer;
			typedef Map_Element<key_type, value_type, key_compare>	elt;
			typedef MapIterator<value_type, elt>        			iterator;
			typedef MapIterator<value_type, elt>              	    const_iterator;
			typedef ReverseIterator<iterator> 						reverse_iterator;
			typedef ReverseIterator<const_iterator> 				const_reverse_iterator;

			class value_compare
			{
				friend class Map;
				protected:
  				Compare comp;
  				value_compare (Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
					return comp(x.first, y.first);
					}
			};
			explicit Map(const key_compare &comp = key_compare()) : _comp(comp), _value_comp(comp)
            {
				this->init();
            }
            template <class InputIterator>
            Map(InputIterator first, InputIterator last, const key_compare &comp = key_compare()) : _comp(comp), _value_comp(comp)
            {
				this->init();
				this->insert(first, last);
            }
            Map(const Map &x) : _comp(x._comp), _value_comp(x._value_comp)
            {
				this->init();
				insert(x.begin(), x.end());
            }
			~Map(void)
			{
				this->clear();
				delete this->_end;
			}
			void		init(void)
			{
				this->_root = new elt();
				this->_begin = this->_root;
				this->_end = _root;
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

				if (!(elm = _root->find(k, _root)))
					return (this->end());
				return (iterator(elm));
			}
			const_iterator			find(const key_type &k) const
			{
				elt		*elm;

				if (!(elm = _root->find(k, _root)))
					return (this->end());
				return (const_iterator(elm));
			}
			size_type				count(const key_type& k) const
			{
				if (find(k) == end())
					return (0);
				return (1);
			}
			mapped_type				&operator[](const key_type &k)
			{
				iterator	it;
				if (_size && (it = find(k)) != end())
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
				if (_size && (ret = find(val.first)) != end())
					return (std::make_pair(ret, 0));
				if (_size)
				{
					_size++;
					return (std::make_pair(_root->push(_root, &_end, &_begin, val), 1));
				}
				else
				{
					_root = new elt(val);
					_root->right() = _end;
					_end->parent() = _root;
					_begin = _root;
					_size++;
				}
				return (std::make_pair(iterator(_root), 1));
			}
			iterator		insert(iterator position, const value_type &val)
			{
				elt *e;

				if (_size && (e = _root->find(val.first, position.get_ptr())))
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
			void		erase(iterator position)
			{
				elt		*ptr = position.get_ptr();
				elt		*prev;
				if (!ptr)
					return ;
				if ((!ptr->right() || ptr->right() == _end) && !ptr->left())
				{
					ptr->erase_leaf(ptr);
					_size--;
					if (_size == 0)
					{
						reset();
						return ;
					}
				}
				else if ((!ptr->right() || ptr->right() == _end) || !ptr->left())
				{
					ptr->erase_one(ptr, &_root, &_end);
					_size--;
				}
				else
				{
					prev = ptr->prev(ptr);
					ptr->erase_two(ptr, prev, &_root, &_end);
					_size--;
				}
				_begin = _root->beg(_root);
				_end = _root->setend(_root, _end);
			}
			size_type	erase(const key_type& k)
			{
				iterator	it = find(k);
				if (it == end())
					return (0);
				else
					erase(it);
				return (1);
			}
			void		erase(iterator first, iterator last)
			{
				key_type	key;

				while (first != last)
				{
					key = first.get_ptr()->next(first.get_ptr())->value().first;
					erase(first);
					first = find(key);
				}
			}
			void		clear()
			{
				erase(begin(), end());
			}
			void		swap(Map& x)
			{
				elt		*ptr;
				ptr = this->_begin;
				this->_begin = x._begin;
				x._begin = ptr;
				ptr = this->_end;
				this->_end = x._end;
				x._end = ptr;
				ptr = this->_root;
				this->_root = x._root;
				x._root = ptr;
				size_t	size;
				size = this->_size;
				this->_size = x._size;
				x._size = size;
			}
			iterator		lower_bound(const key_type& k)
			{
				iterator	it;

				for (it = begin() ; it != end() ; it++)
					if (!_comp(it.get_ptr()->value().first, k))
						return (it);
				return (end());
			}
			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator	it;

				for (it = begin() ; it != end() ; it++)
					if (!_comp(it.get_ptr()->value().first, k))
						return (it);
				return (end());
			}
			iterator		upper_bound(const key_type& k)
			{
				iterator	it;

				for (it = begin() ; it != end() ; it++)
					if (_comp(k, it.get_ptr()->value().first))
						return (it);
				return (end());
			}
			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator	it;

				for (it = begin() ; it != end() ; it++)
					if (_comp(k, it.get_ptr()->value().first))
						return (it);
				return (end());
			}
			std::pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
			{
				return (std::make_pair(lower_bound(k), upper_bound(k)));
			}
			std::pair<iterator,iterator>				equal_range(const key_type& k)
			{
				return (std::make_pair(lower_bound(k), upper_bound(k)));
			}
			key_compare		key_comp() const
			{
				return (this->_comp);
			}
			value_compare	value_comp() const
			{
				return (this->_value_comp);
			}
			size_type	size() const
			{
				return (this->_size);
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
			bool		empty()
			{
				if (_size)
					return (0);
				return (1);
			}
			size_type		max_size(void)		const
			{
				return (std::numeric_limits<size_type>::max() / (sizeof(elt)));
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
		private:
			elt					*_begin;
			elt					*_end;
			elt					*_root;
			size_type			_size;
			key_compare			_comp;
			value_compare		_value_comp;


	};
	template <class Key, typename T, class Compare>
	void	swap(Map<Key, T, Compare> &lhs, Map<Key, T, Compare> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
