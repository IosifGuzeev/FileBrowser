#ifndef FILEBROWSER_H
#define FILEBROWSER_H
#pragma once

#include <string>
#include <calculationstrategy.h>
#include <writer.h>
#include <QDir>


///
/// \brief The FileBrowser class
/// Основной класс, наблюдающей за заданной директорией (причем директория может быть изменена в ходе работы программы по средствам вызова сеттра).
/// Наблюдение реализуется по средствам сбора статистики методом CalculateStats (вид которой задается стратегией).
class FileBrowser
{
    //Текущая обозреваемая директория
    std::string workingDirectory;

    //Текущая стратегия сбора статистики о директории
    CalculationStrategy *strat;

public:
    //Вспомогательное перечисление кодов стратегий, для более удобного использования библиотеки
    enum Strategy
    {
        EachFile = 0,
        ByType = 1
    };

    ///
    /// \brief FileBrowser
    /// На вход подается адрес рабочей директории и стратегия сбора статистики.
    /// \param directory
    /// Абсолютный путь до отслеживаемой директории. Директория должна существовать на момент сбора статистики (То есть при вызове конструктора указывать существующий путь не обязательно).
    /// \param strategy
    /// Код стратегии сбора статистики. При неверном коде будет вызвано исключение.
    FileBrowser(std::string directory = "NOT INITIALIZED", Strategy strategy = Strategy::EachFile);
    ~FileBrowser();

    ///
    /// \brief CalculateStats
    /// Метод сбора статистики о заранее заданной директории (workingDirectory) с помощью заранее заданной стратегии (strat)
    /// Важно: На момент вызова метода директория должна существовать! В противном случае будет вызвано исключение.
    /// \return
    /// Возвращает вектора пар строк: первая строка отвечает за имя элемента, вторая строка показывает его статистику.
    /// Если директория не содержит элементов будет возвращен вектор с одной парой - ("empty", "100%").
    std::vector<std::pair<std::string, std::string>> CalculateStats();
    ///
    /// \brief SetStrat
    /// Сеттер стратегии.
    /// \param newStrat
    /// Код новой стратегии.
    void SetStrat(Strategy newStrat);
    ///
    /// \brief SetDirectory.
    /// Сеттер обозреваемой директории
    /// \param path
    /// Абсолютный путь до отслеживаемой директори.
    void SetDirectory(std::string path);
};

#endif // FILEBROWSER_H
