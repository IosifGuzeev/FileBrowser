#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H
#pragma once
#include <vector>
#include <string>
#include <utility>
#include <QDir>


class CalculationStrategy
{
 public:
    virtual std::vector<std::pair<std::string, std::string>> Calculate (QList<QFileInfo> files)=0;
};

class EachElement_CalculationStrategy: public CalculationStrategy
{
    std::vector<std::pair<std::string, std::string>> Calculate(QList<QFileInfo> files) override;
};

#endif // CALCULATIONSTRATEGY_H
