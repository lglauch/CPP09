#include "BitcoinExchange.hpp"
#include <fstream>
#include <regex>

BitcoinExchange::BitcoinExchange(void){
	std::cout << "Default constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &old) : btcPrices(old.btcPrices){
	std::cout << "Copy constructor called" << std::endl;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &old){
	if (this != &old){
		btcPrices = old.btcPrices;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange(void){
	std::cout << "Constructor called" << std::endl;
}

	//parse input to this.btcPrices
void	BitcoinExchange::loadDatabase(const std::string &filename){
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}
	std::string line;
	std::getline(file, line);
	while(std::getline(file, line)){
		std::string date = line.substr(0, 10);
		std::string price_str = line.substr(11, line.length());
		try{
			double btc_price = stod(price_str);
			// std::cout << date << " :";
			// std::cout << std::fixed << std::setprecision(2) << btc_price << std::endl;
			this->btcPrices[date] = btc_price;
		}
		catch(std::invalid_argument &e){
			std::cout << e.what() << std::endl;
		}
		catch(std::out_of_range &e){
			std::cout << e.what() << std::endl;
		}
	}
}

void BitcoinExchange::checkInput(const std::string &filename){
	std::ifstream file(filename);
	if (!file){
		std::cout << "Error: Couldn't open input file" << std::endl;
		return;
	}
	std::string line;
	std::getline(file, line);
	std::regex line_regex(R"((\d{4}-\d{2}-\d{2}) \| (-?\d+(\.\d+)?))");
	while(std::getline(file, line)){
		std::smatch match;

		if (!std::regex_match(line, match, line_regex)){
			std::cout << "Error: bad input " << line << std::endl;
			continue;
		}
		std::string date = match[1].str();
		std::string btc_amount = match[2].str();
		// std::cout << date << std::endl;
		// std::cout << btc_amount << std::endl;
		
		try{
			double btc_p = std::stod(btc_amount);
			if (btc_p < 0){
				std::cout << "Error: not a positive number" << std::endl;
				continue;
			}
			else if (btc_p > 1000){
				std::cout << "Error: too large number" << std::endl;
				continue;
			}
			else{
				auto it = btcPrices.find(date);
				if (it == btcPrices.end()){
					it = btcPrices.lower_bound(date);
					if (it == btcPrices.begin()){
						std::cout << "No lower date available for" << date << std::endl;
						continue;
					}
					--it;
				}
				// std::cout << "Price: " << it->second << std::endl << "Amount: " << btc_p << std::endl;
				std::cout << date << " => " << btc_amount << " = " << (btc_p * it->second) << std::endl;
			}
		}
		catch (std::invalid_argument &e){
			std::cout << e.what() << std::endl;
		}
		catch (std::out_of_range &e){
			std::cout << e.what() << std::endl;
		}
	}
}