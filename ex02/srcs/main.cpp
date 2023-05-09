#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

std::list<unsigned int>	get_list(unsigned int argc, char *argv[]) {
	std::list<unsigned int>		lst;
	for (unsigned int i = 1; i < argc; i++) {
		std::stringstream	ss;
		long int	n;
		unsigned int		j = 0;
		std::string			arg = argv[i];
		if (arg.size() > 20)
			throw std::exception();
		while (j < arg.size() && std::isdigit(arg[j]))
			j++;
		if (j != arg.size())
			throw std::exception();
		ss << arg;
		ss >> n;
		if (static_cast<unsigned int>(n) != n)
			throw std::exception();
		lst.push_back(n);
	}
	if (!lst.size())
		throw std::exception();
	return (lst);
}

void	print_list(std::string prefix, std::list<unsigned int> &lst) {
	std::cout << std::left << std::setw(6) << prefix << ": ";
	for (std::list<unsigned int>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << " " << std::flush;
	std::cout << std::endl;
}

std::vector<unsigned int>	get_vector(unsigned int argc, char *argv[]) {
	std::vector<unsigned int>		lst;
	for (unsigned int i = 1; i < argc; i++) {
		std::stringstream	ss;
		long int	n;
		unsigned int		j = 0;
		std::string			arg = argv[i];
		if (arg.size() > 20)
			throw std::exception();
		while (j < arg.size() && std::isdigit(arg[j]))
			j++;
		if (j != arg.size())
			throw std::exception();
		ss << arg;
		ss >> n;
		if (static_cast<unsigned int>(n) != n)
			throw std::exception();
		lst.push_back(n);
	}
	return (lst);
}

void	print_vector(std::string prefix, std::vector<unsigned int> &lst) {
	std::cout << std::left << std::setw(6) << prefix << ": ";
	for (std::vector<unsigned int>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << " " << std::flush;
	std::cout << std::endl;
}

int main(int argc, char *argv[]) {
	std::list<unsigned int> lst;
	std::vector<unsigned int> vector;
	try
	{
		lst = get_list(argc, argv);
		vector = get_vector(argc, argv);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}	
	print_list("Before", lst);

	clock_t start, end;
	start = clock();
	PmergeMe::merge_insert_sort(lst);
	end = clock();
	double list_time = ((double) end - start) * 1000000.0 / CLOCKS_PER_SEC;

	start = clock();
	PmergeMe::merge_insert_sort(vector);
	end = clock();
	double vector_time = ((double) end - start) * 1000000.0 / CLOCKS_PER_SEC;

	print_list("After", lst);
	std::cout << "Time to process a range of " << lst.size() << " element";
	if (lst.size() > 1)
		std::cout << "s";
	std::cout << " with std::list : " << list_time << "us." << std::endl;
	std::cout << "Time to process a range of " << lst.size() << " element";
	if (vector.size() > 1)
		std::cout << "s";
	std::cout  << " with std::vector : " << vector_time << "us." << std::endl;
	return (0);
}