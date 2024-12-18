#include "BitcoinExchange.hpp"




int main(int argc, char **argv){
	(void)argv;
	BitcoinExchange btc;
	if (argc != 2){
		std::cout << "Error: could not open file." << std::endl;
		return -1;
	}
	btc.loadDatabase("data.csv");
	btc.checkInput(argv[1]);
	// btc.getClosestPrice();
	return (0);
}