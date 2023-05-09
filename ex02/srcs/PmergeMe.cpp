#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {};

PmergeMe::PmergeMe(PmergeMe &) {};

PmergeMe	&PmergeMe::operator=(PmergeMe &) {return (*this);};

PmergeMe::~PmergeMe() {};

void	PmergeMe::insert_sort(std::list<unsigned int> &lst)
{
	std::list<unsigned int>::iterator it = lst.begin();
	std::list<unsigned int>::iterator next = it;
	next++;
	while (it != lst.end())
	{
		std::rotate(std::upper_bound(lst.begin(), it, *it), it, next);
		it++;
		next++;
	}
}

std::list<unsigned int>	PmergeMe::merge(std::list<unsigned int> &left, std::list<unsigned int> &right)
{
	std::list<unsigned int>	lst;
	std::list<unsigned int>::iterator it_left = left.begin();
	std::list<unsigned int>::iterator it_right = right.begin();
	while (it_left != left.end() && it_right != right.end())
	{
		if (*it_left <= *it_right)
			lst.push_back(*it_left++);
		else
			lst.push_back(*it_right++);
	}
	while (it_left != left.end())
		lst.push_back(*it_left++);
	while (it_right != right.end())
		lst.push_back(*it_right++);
	return (lst);
}

void	PmergeMe::merge_insert_sort(std::list<unsigned int> &lst, unsigned int k)
{
	if (lst.size() <= k)
	{
		insert_sort(lst);
		return ;
	}
	std::list<unsigned int>::iterator	middle = lst.begin();
	std::advance(middle, lst.size() / 2);
	std::list<unsigned int>	left(lst.begin(), middle);
	std::list<unsigned int>	right(middle, lst.end());
	merge_insert_sort(left);
	merge_insert_sort(right);
	lst = merge(left, right);
}

void	PmergeMe::insert_sort(std::vector<unsigned int> &lst)
{
	std::vector<unsigned int>::iterator it = lst.begin();
	std::vector<unsigned int>::iterator next = it;
	next++;
	while (it != lst.end())
	{
		std::rotate(std::upper_bound(lst.begin(), it, *it), it, next);
		it++;
		next++;
	}
}

std::vector<unsigned int>	PmergeMe::merge(std::vector<unsigned int> &left, std::vector<unsigned int> &right)
{
	std::vector<unsigned int>	lst;
	std::vector<unsigned int>::iterator it_left = left.begin();
	std::vector<unsigned int>::iterator it_right = right.begin();
	while (it_left != left.end() && it_right != right.end())
	{
		if (*it_left <= *it_right)
			lst.push_back(*it_left++);
		else
			lst.push_back(*it_right++);
	}
	while (it_left != left.end())
		lst.push_back(*it_left++);
	while (it_right != right.end())
		lst.push_back(*it_right++);
	return (lst);
}

void	PmergeMe::merge_insert_sort(std::vector<unsigned int> &lst, unsigned int k)
{
	if (lst.size() <= k)
	{
		insert_sort(lst);
		return ;
	}
	std::vector<unsigned int>::iterator	middle = lst.begin();
	std::advance(middle, lst.size() / 2);
	std::vector<unsigned int>	left(lst.begin(), middle);
	std::vector<unsigned int>	right(middle, lst.end());
	merge_insert_sort(left);
	merge_insert_sort(right);
	lst = merge(left, right);
}