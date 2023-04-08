#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string &path) {
	std::ifstream fin(path.c_str());
	if (!fin)
		throw std::exception();
	std::string	value;
	std::string	key;
	std::getline(std::getline(fin, key, ','), value);
	while (std::getline(std::getline(fin, key, ','), value))
		_price[key] = std::strtod(value.c_str(), NULL);
}

void	BitcoinExchange::treat_input(const std::string &path) {
	std::ifstream fin(path.c_str());
	if (!fin)
		throw std::exception();
	std::string value;
	std::string key;
	std::getline(std::getline(fin, key, '|'), value);
	while (std::getline(std::getline(fin, key, '|'), value))
		std::cout << key << " " << value << std::endl;

}
