#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H
#pragma once
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <QDir>


class CalculationStrategy
{
 public:
    virtual std::vector<std::pair<std::string, std::string>> Calculate (QList<QFileInfo> files)=0;
    virtual ~CalculationStrategy() = default;
};

class EachElement_CalculationStrategy: public CalculationStrategy
{
public:
    qint64 folder_size(QString path);
public:
    std::vector<std::pair<std::string, std::string>> Calculate(QList<QFileInfo> files) override;
    ~EachElement_CalculationStrategy() override {};
};

class Extention_CalculationStrategy: public CalculationStrategy
{
    std::vector<std::pair<std::string, std::string>> Calculate(QList<QFileInfo> files) override;
    ~Extention_CalculationStrategy() override {};
};

#endif // CALCULATIONSTRATEGY_H