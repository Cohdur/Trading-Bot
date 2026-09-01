#pragma once
#include <string>

struct Quote
{
    std::string date;
    std::string time;

    double bidOpen{};
    double bidHigh{};
    double bidLow{};
    double bidClose{};

    double askOpen{};
    double askHigh{};
    double askLow{};
    double askClose{};
};