#ifndef FILEBROWSER_H
#define FILEBROWSER_H
#pragma once

#include <string>
#include <calculationstrategy.h>
#include <writer.h>
#include <QDir>


class FileBrowser
{
    std::string workingDirectory;
    CalculationStrategy *strat;
    Writer *writer;
    bool IsOwnWriter;

public:
    enum Strategy
    {
        EachFile = 0,
        ByType = 1
    };

    FileBrowser(std::string directory = "NOT INITIALIZED", Strategy strategy = Strategy::EachFile, Writer *writer = nullptr);
    ~FileBrowser();
    std::vector<std::pair<std::string, std::string>> CalculateStats();

};

#endif // FILEBROWSER_H
