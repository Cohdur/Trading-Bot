#pragma once

class Portfolio
{
private:
    double cash_;
    int shares_;
    double averageEntryPrice_;

public:
    explicit Portfolio(double startingCash);

    double cash() const;
    int shares() const;
    double accountValue(double currentPrice) const;

    bool buy(int quantity, double price);
    bool sell(int quantity, double price);
};