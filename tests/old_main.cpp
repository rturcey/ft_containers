#include "List.hpp"
#include <list>
#include <iomanip>
#include "ReverseIterator.hpp"

template<class T>
bool	p(const T &a, const T &b)
{
	if (a % 2 == 0 && b % 2 == 0)
		return (1);
	return (0);
}

template<class T>
bool	lesser(const T &a, const T &b)
{
	if (a < b)
		return (1);
	return (0);
}

template<class T>
bool	even(const T &v)
{
	if (v % 2)
		return (0);
	return (1);
}

template<class T>
bool	odd(const T &v)
{
	if (v % 2)
		return (1);
	return (0);
}

template<class ft_lst, class lst>
void		compare_lst(ft_lst &ft_list, lst &list, std::string const &test)
{
	typename lst::iterator			beg = list.begin();
	typename lst::iterator			itend = list.end();
	typename ft_lst::iterator		ft_beg = ft_list.begin();
	typename ft_lst::iterator		ft_itend = ft_list.end();
	typename lst::reverse_iterator			rbeg = list.rbegin();
	typename lst::reverse_iterator			ritend = list.rend();
	typename ft_lst::reverse_iterator		rft_beg = ft_list.rbegin();
	typename ft_lst::reverse_iterator		rft_itend = ft_list.rend();

	if (ft_list.size() != list.size())
		std::cout << "DIFF: ft::List.size() = " << *ft_beg << " vs std::list.size() = " << *beg << std::endl;
	while (beg != itend && ft_beg != ft_itend)
	{
		if (*beg != *ft_beg)
		{
			std::cout << "DIFF: ft::List <" << *ft_beg << "> vs std::list <" << *beg << ">" << std::endl;
			return ;
		}
		++beg;
		++ft_beg;
	}
	while (rbeg != ritend && rft_beg != rft_itend)
	{
		if (*rbeg != *rft_beg)
		{
			std::cout << "DIFF (reverse_iterator): ft::List <" << *rft_beg << "> vs std::list <" << *rbeg << ">" << std::endl;
			return ;
		}
		++rbeg;
		++rft_beg;
	}
	std::cout << std::setw(30) << test;
	std::cout << ": ✔" << std::endl;
}

int		main(void)
{
	ft::List<int>		newlist;
	std::list<int>		list;
	//------------------------------------------// PUSH_BACK //
	for (int i = 0 ; i < 10000 ; i++)
	{
		newlist.push_back(i);
		list.push_back(i);
	}
	compare_lst(newlist, list, "push_back");

	//------------------------------------------// ERASE //
	newlist.erase(newlist.begin());
	list.erase(list.begin());
	compare_lst(newlist, list, "erase begin");
	newlist.erase(newlist.begin(), newlist.end());
	list.erase(list.begin(), list.end());
	compare_lst(newlist, list, "erase begin to end");

	//------------------------------------------// PUSH_FRONT //
	newlist.push_front(20);
	newlist.push_front(1);
	list.push_front(20);
	list.push_front(1);
	compare_lst(newlist, list, "push_front with empty list");
	for (int i = 0 ; i < 10 ; i++)
	{
		newlist.push_back(i);
		list.push_back(i);
	}
	newlist.push_front(0);
	newlist.push_front(-25478);
	list.push_front(0);
	list.push_front(-25478);
	compare_lst(newlist, list, "push_front");

	//------------------------------------------// INSERT //
	newlist.insert(newlist.begin(), 42);
	list.insert(list.begin(), 42);
	compare_lst(newlist, list, "insert 42 at begin()");
	ft::List<int>		newlist2;
	std::list<int>		list2;
	newlist2.insert(newlist2.begin(), 10, 12);
	list2.insert(list2.begin(), 10, 12);
	compare_lst(newlist, list, "insert 12 ten times at begin()");
	newlist.insert(newlist.end(), newlist2.begin(), newlist2.end());
	list.insert(list.end(), list2.begin(), list2.end());
	compare_lst(newlist, list, "insert another list at end()");

	//------------------------------------------// SWAP //
	for (int i = 0 ; i < 100 ; i++)
	{
		newlist.push_back(i);
		list.push_back(i);
		newlist2.push_back(i);
		list2.push_back(i);
	}
	newlist.swap(newlist2);
	list.swap(list2);
	compare_lst(newlist, list, "swap 1");
	newlist.swap(newlist2);
	list.swap(list2);
	compare_lst(newlist, list, "swap 2");
	for (int i = 0 ; i < 100 ; i++)
	{
		newlist.push_back(i);
		list.push_back(i);
		newlist2.push_back(i);
		list2.push_back(i);
	}
	std::list<int>		empty;
	ft::List<int>		empt;
	newlist2.swap(empt);
	list2.swap(empty);
	compare_lst(newlist2, list2, "swap 3");
	empty.swap(list);
	empt.swap(newlist);
	compare_lst(newlist, list, "swap 4");

	//------------------------------------------// RESIZE //
	newlist.resize(15, 42);
	list.resize(15, 42);
	compare_lst(newlist, list, "resize(15, 42)");
	newlist.resize(5, 21);
	list.resize(5, 21);
	compare_lst(newlist, list, "resize(5, 21)");
	newlist.resize(0);
	list.resize(0);
	compare_lst(newlist, list, "resize(0)");

	//------------------------------------------// SORT //
	for (int i = 100 ; i >= 0  ; i--)
	{
		newlist.push_back(i);
		list.push_back(i);
	}
	newlist.sort();
	list.sort();
	compare_lst(newlist, list, "sort");
	newlist.sort(std::greater<int>());
	list.sort(std::greater<int>());
	compare_lst(newlist, list, "sort with std::greater()");

	//------------------------------------------// UNIQUE //
	for (int i = 100 ; i >= 0  ; i--)
	{
		newlist.push_back(i);
		list.push_back(i);
	}
	newlist.push_back(2);
	list.push_back(2);
	newlist.push_back(2);
	list.push_back(2);
	newlist.push_back(2);
	list.push_back(2);
	newlist.unique();
	list.unique();
	compare_lst(newlist, list, "unique");
	newlist.unique(p<int>);
	list.unique(p<int>);
	newlist.push_back(2);
	list.push_back(2);
	newlist.push_back(2);
	list.push_back(2);
	newlist.push_back(1);
	list.push_back(1);
	newlist.push_back(1);
	list.push_back(1);
	newlist.push_back(2);
	list.push_back(2);
	newlist.push_back(2);
	list.push_back(2);
	compare_lst(newlist, list, "unique with comp even");

	//------------------------------------------// REVERSE //
	newlist.reverse();
	list.reverse();
	compare_lst(newlist, list, "reverse");

	//------------------------------------------// REMOVE / REMOVE_IF //
	newlist.push_back(10);
	list.push_back(10);
	newlist.push_back(10);
	list.push_back(10);
	newlist.push_back(10);
	list.push_back(10);
	newlist.remove(10);
	list.remove(10);
	compare_lst(newlist, list, "remove");
	newlist.remove_if(odd<int>);
	list.remove_if(odd<int>);
	compare_lst(newlist, list, "remove_if(odd)");

	//------------------------------------------// SPLICE //
	newlist2.insert(newlist2.begin(), 10, 10);
	list2.insert(list2.begin(), 10, 10);
	newlist.splice(newlist.end(), newlist2, newlist2.begin(), newlist2.end());
	list.splice(list.end(), list2, list2.begin(), list2.end());
	compare_lst(newlist, list, "splice");

	//------------------------------------------// MERGE //
	list.clear();
	newlist.clear();
	list2.clear();
	newlist2.clear();
	for (int i = 0 ; i < 10 ; i += 2)
	{
		list.push_back(i);
		newlist.push_back(i);
	}
	newlist2.clear();
	for (int i = 1 ; i < 10 ; i += 2)
	{
		list2.push_back(i);
		newlist2.push_back(i);
	}
	newlist.merge(newlist2);
	list.merge(list2);
	compare_lst(newlist, list, "merge");
	for (int i = 0 ; i < 10 ; i += 2)
	{
		list.push_back(i);
		newlist.push_back(i);
	}
	newlist2.clear();
	for (int i = 1 ; i < 10 ; i += 2)
	{
		list2.push_back(i);
		newlist2.push_back(i);
	}
	newlist2.reverse();
	newlist.reverse();
	list2.reverse();
	list.reverse();
	newlist.merge(newlist2, std::greater<int>());
	list.merge(list2, std::greater<int>());
	compare_lst(newlist, list, "merge with std::greater()");

	//------------------------------------------// OPERATORS //
	int		lev = 0;
	int		levb = 0;
	if (newlist == newlist2)
		lev = 1;
	if (list == list2)
		levb = 1;
	std::cout << std::setw(30) << "operator =";
	if (lev == levb)
		std::cout << ": ✔" << std::endl;
	else
		std::cout << ": ✗" << std::endl;

	lev = 0;
	levb = 0;
	if (newlist != newlist2)
		lev = 1;
	if (list != list2)
		levb = 1;
	std::cout << std::setw(30) << "operator !=";
	if (lev == levb)
		std::cout << ": ✔" << std::endl;
	else
		std::cout << ": ✗" << std::endl;

	lev = 0;
	levb = 0;
	if (newlist > newlist2)
		lev = 1;
	if (list > list2)
		levb = 1;
	std::cout << std::setw(30) << "operator >";
	if (lev == levb)
		std::cout << ": ✔" << std::endl;
	else
		std::cout << ": ✗" << std::endl;

	lev = 0;
	levb = 0;
	if (newlist < newlist2)
		lev = 1;
	if (list < list2)
		levb = 1;
	std::cout << std::setw(30) << "operator <";
	if (lev == levb)
		std::cout << ": ✔" << std::endl;
	else
		std::cout << ": ✗" << std::endl;

	lev = 0;
	levb = 0;
	if (newlist >= newlist2)
		lev = 1;
	if (list >= list2)
		levb = 1;
	std::cout << std::setw(30) << "operator >=";
	if (lev == levb)
		std::cout << ": ✔" << std::endl;
	else
		std::cout << ": ✗" << std::endl;

	lev = 0;
	levb = 0;
	if (newlist <= newlist2)
		lev = 1;
	if (list <= list2)
		levb = 1;
	std::cout << std::setw(30) << "operator <=";
	if (lev == levb)
		std::cout << ": ✔" << std::endl;
	else
		std::cout << ": ✗" << std::endl;

	return (0);
}
