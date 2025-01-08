#include "PmergeMe.hpp"

int main(int argc, char **argv){
	if (argc < 2){
		std::cout << "Error: no input" << std::endl;
		return 1;
	}

	std::vector<int> vec;
	std::list<int> lst;
	std::set<int> seen_numbers;
	
	for (int i = 1; i < argc; i++){
		std::istringstream token(argv[i]);
		int number;
		if (!(token >> number) || number < 0){
			std::cout << "Error: invalid input " << argv[i] << std::endl;
			return 1;
		}
		if (seen_numbers.find(number) == seen_numbers.end()){
			vec.push_back(number);
			lst.push_back(number);
			seen_numbers.insert(number);
		}
	}

	PmergeMe sorter;
	std::cout << std::endl;
	std::cout << std::endl;
	sorter.printSequence("Before(vec): ", vec);
	std::cout << std::endl;
	std::cout << std::endl;
	sorter.printSequence("Before(lst): ", lst);
	std::cout << std::endl;
	std::cout << std::endl;

	double vecTime = sorter.measureSortTime(vec);
	double lstTime = sorter.measureSortTime(lst);

	sorter.printSequence("Ordered (vec): ", vec);
	std::cout << std::endl;
	std::cout << std::endl;
	sorter.printSequence("Ordered (lst): ", lst);
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: " << vecTime << "µs" << std::endl;
	std::cout << "Time to process a range of " << lst.size() << " elements with std::lst: " << lstTime << "µs" << std::endl;

	return 0;
}