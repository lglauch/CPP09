#include "BitcoinExchange.hpp"


int main(int argc, char **argv){
	(void)argv;
	if (argc != 2){
		std::cout << "Error: could not open file." << std::endl;
		return -1;
	}
	std::map<std::string, double> btcPrices = getPricesFromCSV("data.csv");
}