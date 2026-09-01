#pragma once
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <fstream>      // std::ifstream
#include <sstream>      // std::istringstream
#include<vector>
#include<iostream>
#include "Quote.hpp"
class CSVParser
{
private:
std::filesystem::path dataDirectory{"data"};
public:
    std::vector<Quote> load(const std::string& filename);

};