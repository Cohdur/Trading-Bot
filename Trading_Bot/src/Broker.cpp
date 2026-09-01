#include "Broker.hpp"

void Broker::executeBuy(const Quote& quote)
{
    if(limitInPennies < amountInPennies)
    {
        std::cout << "Insufficient funds to execute buy order.\n";
        return;
    }

    // for now not sure which to execute on 

    if(quote.askOpen < quote.askClose)
    {
        priceOfStock = quote.askOpen;
        int64_t stockPriceInPennies = static_cast<std::int64_t>(priceOfStock * 100);
        stockCnt = static_cast<int>(amountInPennies / stockPriceInPennies);
        int64_t totalCostInPennies = stockCnt * stockPriceInPennies;
        limitInPennies -= totalCostInPennies;
        std::pair<std::string, int> key = std::make_pair("SPY", stockCnt);
        quoteMap[key] = quote.askOpen;
    }
    else if(quote.askClose < quote.askOpen)
    {
        priceOfStock = quote.askClose;
        int64_t stockPriceInPennies = static_cast<std::int64_t>(priceOfStock * 100);
        stockCnt = static_cast<int>(amountInPennies / stockPriceInPennies);
        int64_t totalCostInPennies = stockCnt * stockPriceInPennies;
        limitInPennies -= totalCostInPennies;
        std::pair<std::string, int> key = std::make_pair("SPY", stockCnt);
        quoteMap[key] = quote.askClose;
    }
    else
    {
        priceOfStock = quote.askHigh;
        int64_t stockPriceInPennies = static_cast<std::int64_t>(priceOfStock * 100);
        stockCnt = static_cast<int>(amountInPennies / stockPriceInPennies);
        int64_t totalCostInPennies = stockCnt * stockPriceInPennies;
        limitInPennies -= totalCostInPennies;
        std::pair<std::string, int> key = std::make_pair("SPY", stockCnt);
        quoteMap[key] = quote.askHigh;
    }
    
}

void Broker::executeSell(const Quote& quote)
{
    if(stockCnt <= 0)
    {
        std::cout << "No stocks to sell.\n";
        return;
    }

    if(quote.bidOpen > quote.bidClose)
    {
        priceOfStock = quote.bidOpen;
        int64_t stockPriceInPennies = static_cast<std::int64_t>(priceOfStock * 100);
        int64_t totalRevenueInPennies = stockCnt * stockPriceInPennies;
        limitInPennies += totalRevenueInPennies;
        stockCnt = 0; // Reset stock count after selling
    }
    else if(quote.bidClose > quote.bidOpen)
    {
        priceOfStock = quote.bidClose;
        int64_t stockPriceInPennies = static_cast<std::int64_t>(priceOfStock * 100);
        int64_t totalRevenueInPennies = stockCnt * stockPriceInPennies;
        limitInPennies += totalRevenueInPennies;
        stockCnt = 0; // Reset stock count after selling
    }
    else
    {
        priceOfStock = quote.bidLow;
        int64_t stockPriceInPennies = static_cast<std::int64_t>(priceOfStock * 100);
        int64_t totalRevenueInPennies = stockCnt * stockPriceInPennies;
        limitInPennies += totalRevenueInPennies;
        stockCnt = 0; // Reset stock count after selling
    }
}