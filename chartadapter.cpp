#include "chartadapter.h"
#include <QBarSeries>
#include <QBarSet>

QChart *BarChartAdapter::MakeChart(std::vector<std::pair<std::string, std::string>> data)
{
    auto result = new QChart();
    auto bars = new QBarSeries();
    for(auto e: data)
    {
        auto bar = new QBarSet(e.first.c_str());
        bar->append(QString(e.second.c_str()).toDouble());
        bars->append(bar);
    }
    result->addSeries(bars);
    return result;
}
