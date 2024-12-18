#pragma once

#include <iostream>
#include <map>
#include <string>
#include <regex.h>

class BitcoinExchange {
	private:
		std::map<std::string, double> btcPrices;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &old);
		BitcoinExchange& operator=(const BitcoinExchange &old);
		~BitcoinExchange();

		void	loadDatabase(const std::string &filename);
		void	checkInput(const std::string &filename);
		double  getClosestPrice(void);
};