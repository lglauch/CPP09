#pragma once

#include <iostream>
#include <map>

class BitcoinExchange {
	private:
		std::map<std::string, double> btcPrices;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &old);
		BitcoinExchange& operator=(const BitcoinExchange &old);
		~BitcoinExchange(;)
};