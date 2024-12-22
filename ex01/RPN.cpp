#include "RPN.hpp"

RPN::RPN(void){
	std::cout << "Default constructor called" << std::endl;
}

RPN::RPN(const RPN &old){
	(void)old;
	std::cout << "Copy constructor called" << std::endl;
}

RPN& RPN::operator=(const RPN &old){
	(void)old;
	return *this;
}

RPN::~RPN(void){
	std::cout << "Constructor called" << std::endl;
}

double RPN::calculate(const std::string &input){
	std::stack<double> container;
	std::istringstream tokens(input);
	std::string token;
	while (tokens >> token){
		if ((std::isdigit(token[0]) && token.size() == 1) || (token[0] == '-' && isdigit(token[1]) && token.size() == 2))
			container.push(std::stod(token));
		else if (token == "+" || token == "-" || token == "/" || token == "*"){
			if (container.size() < 2)
				throw std::invalid_argument("Error: Invalid RPN expression");
			double x = container.top();
			container.pop();
			double y = container.top();
			container.pop();
			double tmp;
			if (token == "+")
				tmp = y + x;
			else if (token == "-")
				tmp = y - x;
			else if (token == "/")
				tmp = y / x;
			else if (token == "*")
				tmp = y * x;
			container.push(tmp);
		}
		else{
			throw std::invalid_argument("Error: Invalid RPN expression or characters");
		}
	}
	if (container.size() != 1)
		throw std::invalid_argument("Error: Invalid result");
	return container.top();
}