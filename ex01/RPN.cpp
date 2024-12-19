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
	double result = 1;
	std::stack<double> container;
	std::istringstream tokens(input);
	std::string token;
	while (tokens >> token)
		std::cout << token << std::endl;

	return result;
}