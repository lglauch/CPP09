#include "RPN.hpp"

int main(int argc, char **argv){
	RPN rpn;
	if (argc != 2){
		std::cout << "Error: wrong input" << std::endl;
		return -1;
	}
	// try{
		double result = rpn.calculate(argv[1]);
		std::cout << "Result: " << result << std::endl;
	// }
	// catch(){

	// }
}