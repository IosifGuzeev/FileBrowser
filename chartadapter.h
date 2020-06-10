#ifndef CHARTADAPTER_H
#define CHARTADAPTER_H
#include <QChart>
#include <string>
#include <vector>
using namespace QtCharts;

//Адаптер, создающий единый интерфейс для всех чартов
class ChartAdapter
{
public:
    //На вход подаются визуализируемые данные (первая строка - имя элемета, вторя строка - его статистика)
    //На выход подается готовый чарт
    virtual QChart* MakeChart(std::vector<std::pair<std::string, std::string>> data) = 0;
    virtual ~ChartAdapter() = default;
};

//Адаптер столбчатого чарта
class BarChartAdapter : public ChartAdapter
{
    // ChartAdapter interface
public:
    QChart *MakeChart(std::vector<std::pair<std::string, std::string>> data) override;
};

#endif // CHARTADAPTER_H
