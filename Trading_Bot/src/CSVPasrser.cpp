#include "TradingChart.hpp"

std::vector<Quote> CSVParser::load(const std::string& filename)
{
    std::filesystem::path path = dataDirectory / filename;

    std::ifstream file;   
    file.open(path, std::ios::in);

    std::vector<Quote> quotes;
    std::string line;
    size_t count = 0;
    if (!file.is_open())
    {
        std::cerr << "Could not open CSV file: " + path.string() << '\n';
    }
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::istringstream row{line};
        Quote quote;
        std::string token;

        std::getline(row, quote.date, ',');

        std::getline(row, quote.time, ',');

        std::getline(row, token, ',');
        quote.bidOpen = std::stod(token);

        std::getline(row, token, ',');
        quote.bidHigh = std::stod(token);

        std::getline(row, token, ',');
        quote.bidLow = std::stod(token);

        std::getline(row, token, ',');
        quote.bidClose = std::stod(token);

        std::getline(row, token, ',');
        quote.askOpen = std::stod(token);

        std::getline(row, token, ',');
        quote.askHigh = std::stod(token);

        std::getline(row, token, ',');
        quote.askLow = std::stod(token);

        std::getline(row, token);
        quote.askClose = std::stod(token);

        quotes.push_back(quote);
    }
    return quotes;

}