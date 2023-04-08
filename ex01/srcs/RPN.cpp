#include "RPN.hpp"

void	RPN::parse_rpn(const std::string &rpn) {
	std::stack<int>	stack;

	for (unsigned int i = 0; i < rpn.size(); i++)
	{
		if (std::isdigit(rpn[i]))
			stack.push(rpn[i] - '0');
		else if (rpn[i] == '+')
			RPN::use_operator(stack, std::plus<long>());
		else if (rpn[i] == '-')
			RPN::use_operator(stack, std::minus<long>());
		else if (rpn[i] == '*')
			RPN::use_operator(stack, std::multiplies<long>());
		else if (rpn[i] == '/')
			RPN::use_operator(stack, std::divides<long>());
		else if (rpn[i] != ' ')
			throw RPN::Error();
	}
	if (stack.size() != 1)
		throw RPN::Error();
	std::cout << stack.top() << std::endl;
}