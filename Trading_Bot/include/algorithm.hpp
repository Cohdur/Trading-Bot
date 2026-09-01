#pragma once
#include<vector>
#include "Quote.hpp"

class Algorithm
{
public:
    virtual ~Algorithm() = default;

    virtual void run( std::vector<Quote>& quoteObj) = 0;

};