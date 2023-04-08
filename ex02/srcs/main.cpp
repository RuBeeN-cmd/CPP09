#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>



std::list<int>	get_list(unsigned int argc, char *argv[]) {
	std::list<int>		lst;
	for (unsigned int i = 1; i < argc; i++) {
		std::stringstream	ss;
		int					n;
		unsigned int		j = 0;
		std::string			arg = argv[i];
		if (arg[0] == '-')
			j++;
		while (j < arg.size() && std::isdigit(arg[j]))
			j++;
		if (j != arg.size())
			throw std::exception();
		ss << arg;
		ss >> n;
		lst.push_back(n);
	}
	return (lst);
}

void	print_list(std::list<int> &lst) {
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << " " << std::flush;
	std::cout << std::endl;
}

void	ft_insert_sort(std::list<int>::iterator begin, std::list<int>::iterator end) {
	std::list<int>::iterator it = begin;
	std::list<int>::iterator j = it;
	j++;
	while (it != end) {
		std::rotate(std::upper_bound(begin, it, *it), it, j);
		it++;
		j++;
	}
}

void	ft_merge_insert_sort(std::list<int>::iterator begin, std::list<int>::iterator end, unsigned int k = 4) {
	
	std::list<int>::iterator sub_end = begin;
	for (unsigned int i = 0; i < *end / k; i++)
	{
		size_t j = 0;
		while (j < k && *sub_end != *end)
		{
			sub_end++;
			j++;
		}
		ft_insert_sort(begin, sub_end);
		begin = sub_end;
	}
}


int main(int argc, char *argv[]) {
	std::list<int> lst = get_list(argc, argv);
	print_list(lst);
	ft_merge_insert_sort(lst.begin(), lst.end());


	print_list(lst);
	
	return (0);
}