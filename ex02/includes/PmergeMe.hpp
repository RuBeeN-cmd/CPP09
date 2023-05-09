#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <list>
#include <vector>

class PmergeMe
{
private:
	PmergeMe();
	PmergeMe(PmergeMe &);
	PmergeMe	&operator=(PmergeMe &);

	static void	insert_sort(std::list<unsigned int> &lst);
	static std::list<unsigned int>	merge(std::list<unsigned int> &left, std::list<unsigned int> &right);

	static void	insert_sort(std::vector<unsigned int> &lst);
	static std::vector<unsigned int>	merge(std::vector<unsigned int> &left, std::vector<unsigned int> &right);

public:
	~PmergeMe();

	static void	merge_insert_sort(std::list<unsigned int> &lst, unsigned int k = 4);
	static void	merge_insert_sort(std::vector<unsigned int> &lst, unsigned int k = 4);
};

#endif