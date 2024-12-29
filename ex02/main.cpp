#include "PmergeMe.hpp"

int main(int argc, char **argv){
	if (argc < 2){
		std::cout << "Error: no input" << std::endl;
		return 1;
	}

	std::vector<int> vec;
	std::list<int> lst;
	
	for (int i = 1; i < argc; i++){
		std::istringstream token(argv[i]);
		int number;
		if (!(token >> number) || number < 0){
			std::cout << "Error: invalid input" << argv[i] << std::endl;
			return 1;
		}
		vec.push_back(number);
		lst.push_back(number);
	}

	PmergeMe sorter;

	sorter.printSequence("Before(vec): ", vec);
	sorter.printSequence("Before(lst): ", lst);

	// double vecTime = sorter.measureSortTime(vec);
	// double lstTime = sorter.measureSortTime(lst);

	// sorter.printSequence("After(vec): ", vec);
	// sorter.printSequence("After(lst): ", lst);

	// std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: " << vecTime << std::endl;
	// std::cout << "Time to process a range of " << lst.size() << " elements with std::lst: " << lstTime << std::endl;

	return 0;
}