#include "BitcoinExchange.hpp"

bool	Date::operator<(const Date &date) const
{
	if (this->year != date.year)
		return (this->year < date.year);
	if (this->month != date.month)
		return (this->month < date.month);
	if (this->day != date.day)
		return (this->day < date.day);
	return (false);
}


std::ostream	&operator<<(std::ostream &out, const Date &date)
{
	out << std::setfill('0') << std::setw(2) << date.year << '-';
	out << std::setfill('0') << std::setw(2) << date.month << '-' << std::setfill('0') << std::setw(2) << date.day;
	return (out);
}


BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange &copy)
{
	*this = copy;
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	if (this == &rhs)
		return (*this);
	_price = rhs._price;
	return (*this);
}

Date	init_date(std::string &key)
{
	Date				date;
	std::stringstream	ss;

	if (key.size() != 10)
	{
		date.year = 0;
		date.month = 0;
		date.day = 0;
		return (date);
	}
	ss << key.substr(0, 4);
	ss >> date.year;
	ss.clear();
	ss << key.substr(5, 2);
	ss >> date.month;
	ss.clear();
	ss << key.substr(8, 2);
	ss >> date.day;
	return (date);
}

bool	is_valid_date(Date &date)
{
	if (!date.day || !date.month)
		return (false);
	if (date.month > 12)
		return (false);
	if (date.year < 1000 || date.year > 9999)
		return (false);
	if (date.day > 31)
		return (false);
	if (date.day == 31 && date.month <= 7 && !(date.month % 2))
		return (false);
	if (date.day == 31 && date.month > 7 && date.month % 2)
		return (false);
	if (date.day == 30 && date.month == 2)
		return (false);
	if (date.day == 29 && date.month == 2)
		if (date.year % 4 || (!(date.year % 100) && date.year % 400))
			return (false);
	return (true);
}

std::string	strtrim(const std::string &str)
{
	int	i, j;
	for (i = 0; i < static_cast<int>(str.size()) && str[i] == ' '; i++);
	for (j = str.size() - 1; j >= 0 && str[j] == ' '; j--);
	if (i > j)
		return ("");
	return (str.substr(i, j - i + 1));
}

void	open_file(std::ifstream &fin, std::string &path)
{
	fin.open(path.c_str());
	if (!fin)
		std::cerr << "Error: could not open file." << std::endl;
}

int	BitcoinExchange::check_first_line(std::string &line, std::string model) const
{
	if (line != model)
	{
		std::cerr << "Error: invalid header line (\"" << line << "\")" << std::endl;
		return (1);
	}
	return (0);
}

int	BitcoinExchange::get_data(std::ifstream &fin, std::string *key, std::string *value, char delim) const
{
	std::string	line;
	std::getline(fin, line);
	size_t	delim_index = line.find(delim);
	if (delim_index == std::string::npos)
	{
		*key = line;
		*value = "";
	}
	else
	{
		*key = line.substr(0, delim_index);
		*value = line.substr(delim_index + 1, line.size() - delim_index - 1);
	}
	*key = strtrim(*key);
	*value = strtrim(*value);
	return (!(!fin));
}

int	BitcoinExchange::init_db(std::string db_path)
{
	std::ifstream	fin;
	open_file(fin, db_path);
	if (!fin)
		return (1);
	std::string	line;
	std::getline(fin, line);
	if (check_first_line(line, "date,exchange_rate"))
	{
		fin.close();
		return (1);
	}
	std::string	key, value;
	while (get_data(fin, &key, &value, ','))
	{
		Date	crt_date = init_date(key);
		if (!is_valid_date(crt_date))
			std::cerr << "Error: bad input => " << key << std::endl;
		else
		{
			double	price = get_quantity(value);
			if (price >= 0)
				_price[crt_date] = price;
		}
	}
	fin.close();
	return (0);
}

double BitcoinExchange::get_quantity(std::string &value) const
{
	char	*end;
	double	quantity = strtod(value.c_str(), &end);
	if (*end || quantity < 0)
		quantity = -1;
	if (*end)
		std::cerr << "Error: invalid number " << value << std::endl;
	if (quantity < 0)
		std::cerr << "Error: not a positive number." << std::endl;
	return (quantity);
}

int BitcoinExchange::treat_input(std::string path) const
{
	std::ifstream	fin;
	open_file(fin, path);
	if (!fin)
		return (1);
	std::string	line;
	std::getline(fin, line);
	if (check_first_line(line, "date | value"))
	{
		fin.close();
		return (1);
	}
	std::string	key, value;
	while (get_data(fin, &key, &value, '|'))
	{
		Date	crt_date = init_date(key);
		if (!is_valid_date(crt_date))
			std::cerr << "Error: bad input => " << key << std::endl;
		else
		{
			double	quantity = get_quantity(value);
			if (static_cast<int>(quantity) != static_cast<long>(quantity))
				std::cerr << "Error: too large a number." << std::endl;
			else if (quantity >= 0)
			{
				std::map<Date, double>::const_iterator it = _price.upper_bound(crt_date);
				if (it-- == _price.begin())
					std::cerr << "Error: no data for this key (\"" << key << "\")" << std::endl;
				else
					std::cout << key << " => " << value << " = " << quantity * it->second << std::endl;
			}
		}
	}
	fin.close();
	return (0);
}