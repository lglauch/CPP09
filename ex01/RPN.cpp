#include "RPN.hpp"

RPN::RPN(void){
	std::cout << "Default constructor called" << std::endl;
}

RPN::RPN(const RPN &old){
	std::cout << "Copy constructor called" << std::endl;
}

RPN& RPN::operator=(const RPN &old){
	if (this != &old){
		
	}
	return *this;
}

RPN::~RPN(void){
	std::cout << "Constructor called" << std::endl;
}