#include <fstream>
#include <iostream>
#include "BitcoinExchange.hpp"
int main()
{
	BitcoinExchange exchange;

	exchange.initData();
	exchange.processData("input.txt");
	return 0;
}

// to get the closest date for the input from the data
// use lower_bound

