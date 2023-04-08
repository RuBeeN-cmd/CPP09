#include "RPN.hpp"

int main(int argc, char *argv[]) {
	if (argc != 2)
		return (1);
	try {
		RPN::parse_rpn(argv[1]);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return (1);
	}
	return (0);
}