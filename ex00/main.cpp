#include "BitcoinExchange.hpp"

int main(int ac, char**av)
{
    if (ac != 2) {
        std::cerr << "usage: ./btc filename" << std::endl;
        return 1;
    }
    (void)av;
    BitcoinExchange btc;
    btc.importDatabase();
    btc.printMultipliedValue(av[1]);
    return 0;
}