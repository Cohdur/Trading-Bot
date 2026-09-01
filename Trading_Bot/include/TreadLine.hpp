#pragma once
#include<vector>
#include<cmath>
#include "algorithm.hpp"
#include "Quote.hpp"


class TreadLine : public Algorithm
{
    private:
    double baselineValue = 0.0;
    double fiveDayAverage = 0.0;
    public:

    void run(std::vector<Quote>& Obj) override;
    double getRollingAverage() const {return fiveDayAverage;}
};
