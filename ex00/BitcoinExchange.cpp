#include "BitcoinExchange.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <ctime>

BitcoinExchange::BitcoinExchange(void) {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& cpy) {(void)cpy;}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs) {(void)rhs;return *this;}
BitcoinExchange::~BitcoinExchange(void) {}

void BitcoinExchange::initData(void) {
	std::ifstream file("data.csv");
	if (!file.is_open()) {
		std::cerr << "Error: Could not open data file " << "data.csv" << "\n";
		return ;
	}
	std::string line;
	std::string date;
	std::string value;
	double priceValue = 0;
	std::getline(file, line);
	if (line != "date,exchange_rate") {
		std::cerr << "Error: Wrong header format. Expected 'date,exchange_rate'." << "\n";
		return;
	}
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		if (std::getline(ss, date, ',') && std::getline(ss, value) ) {
			try {
				priceValue = std::atol(value.c_str());
				if (priceValue < 0) {
					std::cerr << "Wrong value: only numeric values are accepted and non-negative'." << "\n";
					return;
				}
				parseDate(date);
				data_[date] = priceValue;
			}
			catch (const std::exception &e){
				std::cerr << "Error: " << e.what() << "\n";
				return ;
			}
		}
	}
}

void BitcoinExchange::processData(std::string inputFile) {(void)inputFile;
	// for (std::map<std::string, double>::iterator it = data_.begin(); it != data_.end(); ++it) {
    //     std::cout << it->first << std::endl;
    // }
}

void BitcoinExchange::parseDate(std::string date) {
	if (date[4] != '-' || date[7] != '-' || date.size() != 10)
		throw WrongDateFormatException("Invalid date format for '" + date + "'! Expected format: YYYY-MM-DD");
	date_["year"] = date.substr(0, 4).c_str();
	date_["month"] = date.substr(5, 2).c_str();
	date_["day"] = date.substr(8, 2).c_str();

	for (unsigned int i = 0; i < date_["year"].size(); i++) {
		if (!std::isdigit(date_["year"][i]))
			throw WrongDateFormatException("Invalid year format for '" + date + "'! Only numbers accepted");
	}
	for (unsigned int i = 0; i < date_["month"].size(); i++) {
		if (!std::isdigit(date_["month"][i]))
			throw WrongDateFormatException("Invalid month format for '" + date + "'! Only numbers accepted");
	}
	for (unsigned int i = 0; i < date_["day"].size(); i++) {
		if (!std::isdigit(date_["day"][i]))
			throw WrongDateFormatException("Invalid day format for '" + date + "'! Only numbers accepted");
	}

	std::time_t t = std::time(0);
	std::tm* localTime = std::localtime(&t);
	int currentYear = localTime->tm_year + 1900;

	int actualYear = currentYear;
	int year = std::atoi(date_["year"].c_str());
	std::ostringstream oss;
	oss << actualYear;
	if (year < 2009 || year > actualYear)
		throw WrongDateFormatException("Invalid year format for '" + date + "'the year should be between 2009 and " + oss.str());


	// if (year < 2009 && year > actualYear)
	// 	throw WrongDateFormatException("The year should be between 2009 and " + oss.str());
	// Range Checks for Year, Month, and Day:
		// Month: Ensure the month is between 01 and 12.
		// Day: Ensure the day is valid within the given
		// month and year.

	// Leap Year Check (for February):
		// February (the 2nd month) can have 28 or 29 days
			// depending on whether the year is a leap year.
		// A year is a leap year if:
			// It is divisible by 4.
			// It is not divisible by 100,
			// unless it is also divisible by 400.
		// If the year is a leap year, February will have 29 days,
			// otherwise, it will have 28 days.

		// Validity of the Date (e.g., April 31 is invalid):
			// Check for the validity of the day based on the month.
				// For example:
				// Months with 31 days: January, March, May, July,
					// August, October, December
				// Months with 30 days: April, June, September,
					// November
				// February has either 28 or 29 days
					// (depending on the year).
}

BitcoinExchange::WrongDateFormatException::WrongDateFormatException(const std::string& msg) : message_(msg) {}

const char* BitcoinExchange::WrongDateFormatException::what() const throw() {
	return message_.c_str();
}
