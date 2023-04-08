#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <exception>
#include <iostream>
#include <typeinfo>

class RPN
{
private:
	RPN();
	RPN(const RPN &);
	RPN	&operator=(const RPN &);

	template <typename T>
	static void	use_operator(std::stack<int> &stack, T op) {
		if (stack.size() < 2 || (typeid(op) == typeid(std::divides<long>) && stack.top() == 0))
			throw Error();
		int	second = stack.top();
		stack.pop();
		long	res = op(static_cast<long>(stack.top()), static_cast<long>(second));
		if (res != static_cast<int>(res))
			throw Error();
		stack.top() = res;
	}

public:
	~RPN();

	class Error: public std::exception {
		virtual const char* what() const throw() {
			return ("Error");
		}
	};

	static void	parse_rpn(const std::string &rpn);
};

#endif