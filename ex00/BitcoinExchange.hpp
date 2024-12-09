#pragma once

#include <iostream>
#include <limits.h>
#include <map>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdlib>


using std::string;


#define MIN_YEAR_DIGITS 0
#define MAX_YEAR_DIGITS 4
#define MIN_MONTH_DIGITS 5
#define MAX_MONTH_DIGITS 7
#define MIN_DAY_DIGITS 8
#define MAX_DAY_DIGITS 10
#define YEAR_LENGTH 4
#define MONTH_LENGTH 2
#define DAY_LENGTH 2
#define MIN_MONTH 1
#define MAX_MONTH 12
#define MIN_DAY 1
#define MAX_DAY 31
#define FEBRUARY 2
#define APRIL 4
#define JUNE 6
#define SEPTEMBER 9
#define NOVEMBER 11

class BitcoinExchange {
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(BitcoinExchange const & src);
        BitcoinExchange & operator=(BitcoinExchange const & rhs);

        void importDatabase();
        void printMultipliedValue(std::string const & file) const;

    private:
        std::map<string, double> _data;

};