#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <iomanip>

struct	Date {
	unsigned int	year;
	unsigned int	month;
	unsigned int	day;

	bool	operator<(const Date &date) const;
};

class BitcoinExchange
{
private:
	std::map<Date, double> _price;

	int	check_first_line(std::string &line, std::string model) const;
	int	get_data(std::ifstream &fin, std::string *key, std::string *value, char delim) const;
	double get_quantity(std::string &value) const;


public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(BitcoinExchange &);
	BitcoinExchange	&operator=(const BitcoinExchange &);

	int	init_db(std::string	db_path);
	int	treat_input(std::string path) const;
};

#endif
