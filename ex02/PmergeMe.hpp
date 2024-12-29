#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <chrono>
#include <thread>

class PmergeMe{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &old);
		PmergeMe& operator=(const PmergeMe &old);
		~PmergeMe();

		void printSequence(const std::string &prefix, const std::vector<int> &vec);
		void printSequence(const std::string &prefix, const std::list<int> &lst);

		template <typename Container>
		void	measureSortTime(Container &container);

		template <typename Container>
		double measureSortTime(Container &container){
			(void)container;
			auto start = std::chrono::high_resolution_clock::now();
			mergeInsertSort(container);
			std::this_thread::sleep_for(std::chrono::seconds(5));
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::micro> duration = end - start;

			return duration.count();
		}
};