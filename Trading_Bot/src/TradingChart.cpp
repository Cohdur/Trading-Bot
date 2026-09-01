#include "TradingChart.hpp"

void TradingChart::addQuote(const Quote& quote)
{

    QDate date = QDate::fromString(
    QString::fromStdString(quote.date),
    "MM/dd/yyyy"
    );

    QTime time = QTime::fromString(
    QString::fromStdString(quote.time),
    "HH:mm"
    );
    qint64 timestamp =
    QDateTime(date, time).toMSecsSinceEpoch();

    auto* candles = new QCandlestickSet(
        quote.askOpen,
        quote.askHigh,
        quote.askLow,
        quote.askClose,
        static_cast<qreal>(timestamp));

    candle->append(candles);

    if (firstTimestamp == 0)
    firstTimestamp = timestamp;

    lastTimestamp = timestamp;

    minPrice = std::min(minPrice, quote.askLow);
    maxPrice = std::max(maxPrice, quote.askHigh);
}

void TradingChart::setupAxes()
{
    
    axisX = new QDateTimeAxis();
    axisY = new QValueAxis();
    

    axisX->setFormat("MM/dd HH:mm");

    axisX->setRange(
        QDateTime::fromMSecsSinceEpoch(firstTimestamp),
        QDateTime::fromMSecsSinceEpoch(lastTimestamp)
    );

    double padding = (maxPrice - minPrice) * 0.05;

    axisY->setRange(
        minPrice - padding,
        maxPrice + padding
    );

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    candle->attachAxis(axisX);
    candle->attachAxis(axisY);

    buyMarkers->attachAxis(axisX);
    buyMarkers->attachAxis(axisY);

    sellMarkers->attachAxis(axisX);
    sellMarkers->attachAxis(axisY);
}
void TradingChart::updateYAxis()
{
    if (!axisX || !axisY || !candle)
    {
        std::cerr << "NULL POINTER\n";
        return;
    }
    qint64 visibleStart = axisX->min().toMSecsSinceEpoch();
    qint64 visibleEnd   = axisX->max().toMSecsSinceEpoch();

    double visibleMin = std::numeric_limits<double>::max();
    double visibleMax = std::numeric_limits<double>::lowest();

    bool foundCandle = false;

    for (auto* set : candle->sets())
    {
        qint64 timestamp =
            static_cast<qint64>(set->timestamp());

        if (timestamp >= visibleStart &&
            timestamp <= visibleEnd)
        {
            foundCandle = true;

            visibleMin = std::min(
                visibleMin,
                static_cast<double>(set->low())
            );

            visibleMax = std::max(
                visibleMax,
                static_cast<double>(set->high())
            );
        }
    }

    if (!foundCandle)
        return;

    double range = visibleMax - visibleMin;

    // Protect against a completely flat visible range.
    if (range <= 0.0)
        range = 1.0;

    double padding = range * 0.05;

    axisY->setRange(
        visibleMin - padding,
        visibleMax + padding
    );
}
void TradingChart::TradingChartView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragging = true;
        lastMousePosition = event->pos();
        event->accept();
        return;
    }

    QChartView::mousePressEvent(event);
}

void TradingChart::TradingChartView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragging = false;
        event->accept();
        return;
    }

    QChartView::mouseReleaseEvent(event);
}
void TradingChart::TradingChartView::mouseMoveEvent(QMouseEvent* event)
{
    if (!dragging)
    {
        QChartView::mouseMoveEvent(event);
        return;
    }

    int deltaX = event->position().x() - lastMousePosition.x();
    int deltaY = event->position().y() - lastMousePosition.y();

    chart()->scroll(-deltaX, deltaY);

    lastMousePosition = event->position().toPoint();

    event->accept();
}
void TradingChart::TradingChartView::wheelEvent(QWheelEvent* event)
{
    auto* axisX = qobject_cast<QDateTimeAxis*>(
        chart()->axes(Qt::Horizontal).first()
    );

    qint64 min = axisX->min().toMSecsSinceEpoch();
qint64 max = axisX->max().toMSecsSinceEpoch();

qint64 range = max - min;

double factor = event->angleDelta().y() > 0
    ? 0.65// changed from 0.95 or 5% to 35%
    : 1.35;

qint64 newRange =
    static_cast<qint64>(range * factor);

    axisX->setRange(
    QDateTime::fromMSecsSinceEpoch(max - newRange),
    QDateTime::fromMSecsSinceEpoch(max)
);
    owner->updateYAxis();
    event->accept();
}
void TradingChart::addBuyMarker(const Quote& quote, double price)
{
    QDate date = QDate::fromString(
        QString::fromStdString(quote.date),
        "MM/dd/yyyy"
    );

    QTime time = QTime::fromString(
        QString::fromStdString(quote.time),
        "HH:mm"
    );

    qint64 timestamp = QDateTime(date, time).toMSecsSinceEpoch();
    price -= 0.05; 

    buyMarkers->append(static_cast<qreal>(timestamp), static_cast<qreal>(price));
}
    
void TradingChart::addSellMarker(const Quote& quote, double price)
{
    QDate date = QDate::fromString(
        QString::fromStdString(quote.date),
        "MM/dd/yyyy"
    );

    QTime time = QTime::fromString(
        QString::fromStdString(quote.time),
        "HH:mm"
    );

    qint64 timestamp = QDateTime(date, time).toMSecsSinceEpoch();
    price += 0.05; 

    sellMarkers->append(static_cast<qreal>(timestamp), static_cast<qreal>(price));
}
