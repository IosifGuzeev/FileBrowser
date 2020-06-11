#include "chartadapter.h"
#include <QBarSeries>
#include <QBarSet>
#include <QPieSeries>
#include <QPieSlice>

QChart *BarChartAdapter::MakeChart(std::vector<std::pair<std::string, std::string>> data)
{
    auto result = new QChart();
    auto bars = new QBarSeries();
    //Элементы с значением стастики меньше 5% будут помещены в общую группу "остальные"
    double not_others_weigt = 0; //Вспомогательная переменная для отсчета отображенной части занимаемого места
    for(auto e: data)
    {
        if (e.second != "<0.01%")
        {
            auto raw_statistic = e.second; //Статистика в строковом формате
            raw_statistic.pop_back(); //Удаляем символ процента
            auto statistic = QString(raw_statistic.c_str()).toDouble();
            if(statistic > 0.05)
            {
                auto bar = new QBarSet(e.first.c_str());
                bar->append(statistic);
                bars->append(bar);
                not_others_weigt += statistic;
            }
        }
    }
    if(not_others_weigt < 1) //Если имеются пропущенные элементы
    {
        auto bar = new QBarSet("Other");
        bar->append(1 - not_others_weigt);
        bars->append(bar);
    }
    result->addSeries(bars);
    result->setTitle("Визуализация данных об обозреваемой директории:");
    result->legend()->setAlignment(Qt::AlignLeft); //Легенда помещается влево, так как элементов можеть быть очень много
    return result;
}

QChart *PieChartAdapter::MakeChart(std::vector<std::pair<std::string, std::string> > data)
{
    auto result = new QChart();
    auto bars = new QPieSeries();
    //Элементы с значением стастики меньше 5% будут помещены в общую группу "остальные"
    double not_others_weigt = 0;//Вспомогательная переменная для отсчета отображенной части занимаемого места
    for(auto e: data)
    {
        if (e.second != "<0.01%")
        {
            auto raw_statistic = e.second;//Статистика в строковом формате
            raw_statistic.pop_back();//Удаляем символ процента
            auto statistic = QString(raw_statistic.c_str()).toDouble();
            if(statistic > 0.05)
            {
                auto bar = new QPieSlice(e.first.c_str(), statistic);
                bars->append(bar);
                not_others_weigt += statistic;
            }
        }
    }
    if(not_others_weigt < 1) //Если имеются пропущенные элементы
    {
        auto bar = new QPieSlice("Other", 1 - not_others_weigt);
        bars->append(bar);
    }
    result->addSeries(bars);
    result->setTitle("Визуализация данных об обозреваемой директории:");
    result->legend()->setAlignment(Qt::AlignLeft);//Легенда помещается влево, так как элементов можеть быть очень много
    return result;
}
