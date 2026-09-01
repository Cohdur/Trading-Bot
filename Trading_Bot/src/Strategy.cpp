#include "Strategy.hpp"
#include <cmath>

Strategy::Signal Strategy::evaluate(const Quote& quote, TreadLine& algorithmObj)
{    
    // buy once sell once 
    if(bought == false)
    {
        if(quote.askClose <= algorithmObj.getRollingAverage() || quote.askHigh <= algorithmObj.getRollingAverage() 
        || quote.askLow <= algorithmObj.getRollingAverage() || quote.askOpen <= algorithmObj.getRollingAverage())
        {
            bought = true;
            sold = false;
            return Signal(Strategy::Signal::Buy);
        }
        else return Signal(Strategy::Signal::Hold);
    }
    else if(bought == true && sold == false)
    {
        if(quote.bidClose >= algorithmObj.getRollingAverage() || quote.bidHigh >= algorithmObj.getRollingAverage()
        || quote.bidLow >= algorithmObj.getRollingAverage() || quote.bidOpen >= algorithmObj.getRollingAverage())
        {
            sold = true;
            bought = false;
            return Signal(Strategy::Signal::Sell); 
        }
        else return Signal(Strategy::Signal::Hold);
    }
    
    return Signal(Strategy::Signal::Hold);
}