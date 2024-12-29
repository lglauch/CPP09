#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void){
	std::cout << "Default constructor called" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &old){
	(void)old;
	std::cout << "Copy constructor called" << std::endl;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &old){
	(void)old;
	std::cout << "Assignment operator called" << std::endl;
	return *this;
}

PmergeMe::~PmergeMe(void){
	std::cout << "Destructor called" << std::endl;
}

void	PmergeMe::printSequence(const std::string &prefix, const std::vector<int> &vec){
	std::cout << prefix;
	for (int numbers : vec){
		std::cout << numbers << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::printSequence(const std::string &prefix, const std::list<int> &lst){
	std::cout << prefix;
	for (int numbers : lst){
		std::cout << numbers << " ";
	}
	std::cout << std::endl;
}