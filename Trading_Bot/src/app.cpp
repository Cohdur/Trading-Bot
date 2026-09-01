#include <iostream>
#include <limits>
#include <algorithm>
#include "TradingChart.hpp"
#include "TreadLine.hpp" // I may want to include this into chart for visual 

int main(int argc, char* argv[]) 
{
    Broker broker;
    Strategy strat;
    TreadLine evaluate;
    QApplication app(argc, argv);
    CSVParser parser;
    TradingChart chart;
    std::vector<Quote> index = parser.load("SPY_daily.csv");
    evaluate.run(index); // rolling average 

    for(const auto& itr : index)
    {
        chart.addQuote(itr);
        switch(strat.evaluate(itr, evaluate))
        {
            case Strategy::Signal::Buy:
    
                broker.executeBuy(itr);
                chart.addBuyMarker(itr, broker.getPriceOfStock());
                break;
            case Strategy::Signal::Sell:
            
                broker.executeSell(itr);
                chart.addSellMarker(itr, broker.getPriceOfStock());
                break;
            case Strategy::Signal::Hold:
    
                break;
        }
    }
    chart.setupAxes();
    QChart* qChart = chart.getChart();


    if (qChart == nullptr)
    {
        std::cerr << "TradingChart has no QChart\n";
        return 1;
    }
    TradingChart::TradingChartView view{chart.getChart(), &chart};
    view.resize(1200, 800);
    view.show();
    std::cout << broker.getLimit();
    return app.exec();


    return 0;
}