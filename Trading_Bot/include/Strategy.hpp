#pragma once
#include <vector>
#include "TreadLine.hpp"
#include "Quote.hpp"
class Strategy
{
private:

    bool bought = false;
    bool sold = true;

public:

    enum class Signal
    {
        Buy,
        Sell,
        Hold 
    };
    void setBuyOrderPlaced(bool value) { bought = value; }
    bool getBuyOrderPlaced() const { return bought; }
    void setSellOrderPlaced(bool value) { sold = value; }
    bool getSellOrderPlaced() const { return sold; }
    Signal evaluate(const Quote& quote, TreadLine& algorithmObj);
   
};