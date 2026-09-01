#include "TreadLine.hpp"

void TreadLine::run(std::vector<Quote>& Obj)
{
    int minuteCnt = 0;
    int dayCnt = 0; // get five days
    double dailyMid = 0.0;
    std::string day = (Obj.begin()->date);

    for (auto& quote : Obj)
    {
        if(dayCnt == 5)
        {
            fiveDayAverage = (baselineValue / 5);
            break;
        }
        else if(dayCnt != 5 && quote.date != day)
        {
            baselineValue += (dailyMid / minuteCnt);
            dailyMid = 0.0;
            minuteCnt = 0;
            ++dayCnt;
            day = quote.date;
        }
        dailyMid += (quote.bidHigh + quote.bidLow + quote.askHigh + quote.askLow) / 4.0;
        ++minuteCnt;
    }

}