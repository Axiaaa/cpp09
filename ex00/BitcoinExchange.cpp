#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & src) {
    *this = src;
}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const & rhs) {
    if (this != &rhs) {
        this->_data = rhs._data;
    }
    return *this;
}

void BitcoinExchange::importDatabase() {
    std::ifstream file("data.csv");
    if (!file.is_open()) {
        std::cerr << "Error: could not open database.csv" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string key;
        double value;
        std::getline(ss, key, ',');
        ss >> value;
        this->_data[key] = value;
    }
    file.close();
}

std::string checkDate(std::string const & date, std::string &strValue) {


    if (date.size() != 10) {
        strValue = "Error: bad input => Date is not formatted correctly";
        return strValue;
    }
    if (date[4] != '-' || date[7] != '-') {
        strValue = "Error: bad input => Date is not formatted correctly";
        return strValue;
    }

    for (int i = MIN_YEAR_DIGITS; i < MAX_YEAR_DIGITS; ++i) {
        if (!isdigit(date[i])) {
            strValue = "Error: bad input => Year is not a number";
            return strValue;
        }
    }

    for (int i = MIN_MONTH_DIGITS; i < MAX_MONTH_DIGITS; ++i) {
        if (!isdigit(date[i])) {
            strValue = "Error: bad input => Month is not a number";
            return strValue;
        }
    }

    for (int i = MIN_DAY_DIGITS; i < MAX_DAY_DIGITS; ++i) {
        if (!isdigit(date[i])) {
            strValue = "Error: bad input => Day is not a number";
            return strValue;
        }
    }

    int year    =   atoi(date.substr(MIN_YEAR_DIGITS, YEAR_LENGTH).c_str());
    int month   =   atoi(date.substr(MIN_MONTH_DIGITS, MONTH_LENGTH).c_str());
    int day     =   atoi(date.substr(MIN_DAY_DIGITS, DAY_LENGTH).c_str());

    if (month < MIN_MONTH || month > MAX_MONTH) {
        strValue = "Error: bad input => Month is out of range";
        return strValue;
    }

    if (day < MIN_DAY || day > MAX_DAY) {
        strValue = "Error: bad input => Day is out of range";
        return strValue;
    }

    if (month == FEBRUARY) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day == 29 && !isLeap)) {
            strValue = "Error: bad input => Day is out of range for February";
            return strValue;
        }
    } else if (month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER) {
        if (day > 30) {
            strValue = "Error: bad input => Day is out of range for the month";
            return strValue;
        }
    }
    return "";
}


std::string checkBtcCount(std::string const & currency, std::string &strValue) {

    for (size_t i = 0; i < currency.size(); ++i) {
        if (!isdigit(currency[i]) && currency[i] != '.') {
            strValue = "Error: bad input => Value is not a number or is a decimal";
            return strValue;
        }
    }
    if (strtol(currency.c_str(), NULL, 10) >= INT_MAX || strtol(currency.c_str(), NULL, 10) < 0) {
        strValue = "Error: bad input => Value is not a positive number or is too large";
        return strValue;
    }
    if (atoi(currency.c_str()) > 1000) {
        strValue = "Error: bad input => Value is too large";
        return strValue;
    }
    return "";
}

void BitcoinExchange::printMultipliedValue(std::string const & file) const {
    std::ifstream fileToMultiply(file.c_str());
    if (!fileToMultiply.is_open()) {
        std::cerr << "Error: could not open " << file << std::endl;
        return;
    }

    std::string line;
    while (std::getline(fileToMultiply, line)) {
        if (line == "date | value")
            continue;
        std::stringstream ss(line);
        if (line.empty()) {
            std::cout << "Error: bad input => Line is empty" << std::endl;
            continue;
        }
        if (line.size() < 13 || line[11] != '|' || line[10] != ' ' || line[12] != ' ') {
            std::cout << "Error: bad input => Line is not formatted correctly" << std::endl;
            continue;
        }
        //Erase white spaces
        line.erase(line.find_last_not_of(" \n\r\t") + 1);
        line.erase(0, line.find_first_not_of(" \n\r\t"));
        std::string date = line.substr(0, 10);
        std::string btcCount = line.substr(13);
        string strValue = "";
        strValue = checkDate(date, strValue);
        if (!strValue.empty()) {
            std::cout << strValue << std::endl;
            continue;
        }
        strValue = checkBtcCount(btcCount, strValue);
        if (!strValue.empty()) {
            std::cout << strValue << std::endl;
            continue;
        }
        std::map<string, double>::const_iterator it = this->_data.find(date);
        //Find the closest date
        if (it == this->_data.end()) {
            std::map<string, double>::const_iterator lower = this->_data.lower_bound(date);
            std::map<string, double>::const_iterator upper = this->_data.upper_bound(date);
            if (lower == this->_data.begin()) {
                std::cout << "Error: no data available for this date" << std::endl;
                continue;
            }
            if (lower == this->_data.end()) {
                --lower;
                it = lower;
            } else {
                --lower;
                if (abs(atoi(lower->first.c_str()) - atoi(date.c_str())) < abs(atoi(upper->first.c_str()) - atoi(date.c_str()))) {
                    it = lower;
                } else {
                    it = upper;
                }
            }
        }
        std::cout << date << " => " << btcCount << " = " << atof(btcCount.c_str()) * it->second << std::endl;
    }
    fileToMultiply.close();
}