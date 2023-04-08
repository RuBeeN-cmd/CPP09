#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include <sstream>
#include <cstdlib>
#include <algorithm>

class BitcoinExchange
{
private:
	std::map<std::string, double> _price;
	BitcoinExchange();

public:
	BitcoinExchange(const std::string &path);
	BitcoinExchange	&operator=(const BitcoinExchange &);
	~BitcoinExchange();

	void	treat_input(const std::string &path);
};

#endif
