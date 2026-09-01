#pragma once
#include <QtCharts/QCandlestickSeries>
#include <QtCharts/QCandlestickSet>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCore/QDateTime>
#include <QtWidgets/QApplication>
#include <QtCore/QTime>
#include <QtCore/QDate>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtGui/QWheelEvent>
#include <QtGui/QMouseEvent>
#include "Broker.hpp"

class TradingChart
{
private:

    QString dateString;
    QString timeString;
    Broker broker;
    Strategy strategy;
    QLineSeries* movingAverageSeries;
    QScatterSeries* buyMarkers;
    QScatterSeries* sellMarkers;
    QCandlestickSet* currentCandle;
    // zoom scaling 
    QDateTimeAxis* axisX{nullptr};
    QValueAxis* axisY{nullptr};
    QCandlestickSeries* candle;
    QChart* chart{new QChart()};
    double minPrice = std::numeric_limits<double>::max();
    double maxPrice = std::numeric_limits<double>::lowest();
    qint64 firstTimestamp = 0;
    qint64 lastTimestamp = 0;


public:

    class TradingChartView : public QChartView
    {
        public:
        using QChartView::QChartView;
        private:
        TradingChart* owner;
        public:
        TradingChartView(
            QChart* chart,
            TradingChart* owner,
            QWidget* parent = nullptr
        )
            : QChartView(chart, parent),
              owner(owner)
        {}
        
        protected:
        void wheelEvent(QWheelEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        private:
        bool dragging{false};
        QPoint lastMousePosition;
    };

    TradingChart()
    :   candle(new QCandlestickSeries()), buyMarkers(new QScatterSeries()), sellMarkers(new QScatterSeries)
    {
        candle->setIncreasingColor(Qt::green);
        candle->setDecreasingColor(Qt::red);
        candle->setBodyWidth(0.7);
        candle->setMinimumColumnWidth(2.0);
        candle->setMaximumColumnWidth(30.0);

        buyMarkers->setName("Buy");
        buyMarkers->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        buyMarkers->setColor(Qt::cyan);
        buyMarkers->setMarkerSize(12.0);
        
        sellMarkers->setName("Sell");
        sellMarkers->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
        sellMarkers->setColor(Qt::magenta);
        sellMarkers->setMarkerSize(12.0);

        chart->addSeries(buyMarkers);
        chart->addSeries(sellMarkers);
        chart->addSeries(candle);
    }
    
    void setupAxes();
    void updateYAxis();
    QChart* getChart() const { return chart; }
    void addQuote(const Quote& quote);
    void addBuyMarker(const Quote& quote, double price);
    void addSellMarker(const Quote& quote, double price); // based on sell order
    void updateMovingAverage(long long time, double value);




};