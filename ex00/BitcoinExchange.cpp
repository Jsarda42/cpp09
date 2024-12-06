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
				for (unsigned int i = 0; i < value.size();i++) {
					if (value[i] != '.' && !std::isdigit(value[i])) {
						std:: cout << value[i]<< std::endl;
						std::cerr << "Wrong value: only numeric values are accepted ." << "\n";
						return;
					}
				}
				priceValue = std::atol(value.c_str());
				if (priceValue < 0) {
					std::cerr << "Wrong value: only non-negative value accepted'." << "\n";
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

	int year = std::atoi(date_["year"].c_str());
	int month = std::atoi(date_["month"].c_str());
	int day = std::atoi(date_["day"].c_str());

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
			throw WrongDateFormatException("Invalid day format for '" + date + "' Only numbers accepted");
	}

	std::time_t t = std::time(0);
	std::tm* localTime = std::localtime(&t);
	int currentYear = localTime->tm_year + 1900;

	std::ostringstream oss;
	oss << currentYear;
	if (year < 2009 || year > currentYear)
		throw WrongDateFormatException("Invalid year format for '" + date + "' the year should be between 2009 and " + oss.str());

	std::ostringstream ss;
	ss << month;

	if (month < 1 || month > 12)
		throw WrongDateFormatException("Invalid month format for '" + date + "' there is only 12 month a year");
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30 || day < 1)
			throw WrongDateFormatException("Invalid day format for '" + date + "' month is 30 days");
	}
	else if (month != 2) {
		if (day > 31 || day < 1)
			throw WrongDateFormatException("Invalid day format for '" + date + "' month is 31 days");
	}
	else {
		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
			if (day < 1 || day > 29)
				throw WrongDateFormatException("Invalid day format for '" + date + "' February has 29 days in a leap year");
		}
		else if (day < 1 || day > 28)
			throw WrongDateFormatException("Invalid day format for '" + date + "' February has 28 days in a common year");
	}
}

BitcoinExchange::WrongDateFormatException::WrongDateFormatException(const std::string& msg) : message_(msg) {}

const char* BitcoinExchange::WrongDateFormatException::what() const throw() {
	return message_.c_str();
}
