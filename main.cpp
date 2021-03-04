#include "List.hpp"
#include "ReverseIterator.hpp"

int		main(void)
{
	ft::List<int>		newlist;
	std::cout << "Size max ? " << newlist.max_size() << std::endl;
	std::cout << "Empty ? " << newlist.empty() << std::endl;
	std::cout << "Size ? " << newlist.size() << std::endl;
	newlist.push_back(50);
	newlist.push_back(80);
	newlist.push_back(100);
	newlist.erase(newlist.begin().get_ptr()->next());
	ft::List<int>::iterator		it = newlist.begin();
	while (it != newlist.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	newlist.erase(newlist.begin(), newlist.end());
	newlist.push_front(20);
	newlist.push_front(1);
	std::cout << "Reading checking after full erase + push_front 20 and 1" << std::endl;
	it = newlist.begin();
	while (it != newlist.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	newlist.insert(newlist.begin(), 42);
	ft::List<int>		newlist2;
	newlist2.insert(newlist2.begin(), 10, 12);
	std::cout << "swap 1" << std::endl;
	newlist.swap(newlist2);
	it = newlist.begin();
	while (it != newlist.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << "swap 2" << std::endl;
	newlist.swap(newlist2);
	it = newlist.begin();
	while (it != newlist.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	newlist.insert(newlist.begin().get_ptr()->next(), newlist2.begin(), newlist2.end());
	it = newlist.begin();
	std::cout << "Empty ? " << newlist.empty() << std::endl;
	std::cout << "Size ? " << newlist.size() << std::endl;
	std::cout << newlist.front() << std::endl;
	std::cout << newlist.back() << std::endl;
	std::cout << "Reading list using iterator" << std::endl;
	while (it != newlist.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	ft::List<int>::reverse_iterator rev = newlist.rbegin();
	std::cout << "Reading list using reverse_iterator" << std::endl;
	while (rev != newlist.rend())
	{
		std::cout << *rev << std::endl;
		rev++;
	}
	std::cout << "Size ? " << newlist.size() << std::endl;
	newlist.resize(15, 42);
	it = newlist.begin();
	std::cout << "Size ? " << newlist.size() << std::endl;
	std::cout << "Reading list using iterator, after resize(15, 42)" << std::endl;
	while (it != newlist.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	newlist.resize(5, 21);
	it = newlist.begin();
	std::cout << "Reading list using iterator, after resize(5, 21)" << std::endl;
	while (it != newlist.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	return (0);
}
