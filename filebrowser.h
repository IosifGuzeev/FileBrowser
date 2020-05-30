#ifndef FILEBROWSER_H
#define FILEBROWSER_H
#pragma once

#include <string>
#include <calculationstrategy.h>
#include <QDir>


class FileBrowser
{
    enum Strategy
    {
        EachFile = 0,
        ByType = 1
    };

    std::string workingDirectory;
    CalculationStrategy *strat;

public:
    FileBrowser(std::string directory = "NOT INITIALIZED", Strategy strategy = Strategy::EachFile);
    std::vector<std::pair<std::string, std::string>> Calculate();

};

#endif // FILEBROWSER_H
