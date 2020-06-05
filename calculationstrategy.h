#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H
#pragma once
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <QDir>

//Абстрактный класс стратегии по сбору статистики об обозреваемой директории.
class CalculationStrategy
{
 public:
    ///
    /// \brief Calculate
    /// Метод сбора статистики.
    /// \param files
    /// Список элементов обозреваемой директории.
    /// \return
    /// Вектор пар строк: Первая строка содержит имя элемента, вторая строка содержит статистику соответствующего элемента.
    ///
    virtual std::vector<std::pair<std::string, std::string>> Calculate (QList<QFileInfo> files)=0;
    virtual ~CalculationStrategy() = default;
};

///
/// \brief The EachElement_CalculationStrategy class
/// Стратегия, описывающая директорию по средствам предоставления статистики о занимаемом каждым элементом пространстве директории (то есть папкой или файлом).
class EachElement_CalculationStrategy: public CalculationStrategy
{
public:
    ///
    /// \brief folder_size
    ///  Рекурсивно вычисляет размер заданной директории.
    /// \param path
    ///  Абсолютный путь до директории.
    /// \return
    /// Размер заданной директории.
    qint64 folder_size(QString path);
public:
    std::vector<std::pair<std::string, std::string>> Calculate(QList<QFileInfo> files) override;
    ~EachElement_CalculationStrategy() override {};
};

///
/// \brief The Extention_CalculationStrategy class
/// Стратегия, описывающая директорию по средствам предоставления статистики о процентом отношении занимаемого пространства директории среди типов файлов.
class Extention_CalculationStrategy: public CalculationStrategy
{
    std::vector<std::pair<std::string, std::string>> Calculate(QList<QFileInfo> files) override;
    ~Extention_CalculationStrategy() override {};
};

#endif // CALCULATIONSTRATEGY_H
