#include "BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
	if (argc != 2)
		return (1);
	BitcoinExchange exchange("assets/data.csv");
	exchange.treat_input(argv[1]);
	return (0);
}
