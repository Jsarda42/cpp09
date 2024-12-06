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

