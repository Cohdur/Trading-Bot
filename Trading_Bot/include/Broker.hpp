#pragma once
#include<cstdint>
#include<map>
#include <utility>
#include "Strategy.hpp"
#include "CSVParser.hpp"

class Broker
{
    private:
    Quote quote;
    CSVParser parser;
    std::map<std::pair<std::string, int>,double> quoteMap;
    std::int64_t limitInPennies = 1000000; 
    std::int64_t amountInPennies = (limitInPennies / 4); // spending amount
    int stockCnt = 0;
    double priceOfStock;
    std::vector<Quote> ticker = parser.load("SPY_daily.csv");

    public:

    void executeBuy(const Quote& quote);
    void executeSell(const Quote& quote);
    std::int64_t getAmount() const {return amountInPennies;}
    std::int64_t getLimit() const {return limitInPennies;}
    double getPriceOfStock() const {return priceOfStock;}
    
};