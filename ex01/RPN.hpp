#pragma once

#include <iostream>
#include <stack>
#include <sstream>

class RPN{
	private:

	public:
		RPN();
		RPN(const RPN &old);
		RPN& operator=(const RPN &old);
		~RPN();

		double calculate(const std::string &input);
};