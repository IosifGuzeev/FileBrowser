#include "filebrowser.h"

FileBrowser::FileBrowser(std::string directory, FileBrowser::Strategy strategy)
{
    workingDirectory = directory;
    strat = nullptr;
    SetStrat(strategy);
}

FileBrowser::~FileBrowser()
{
    delete strat;
}

std::vector<std::pair<std::string, std::string>> FileBrowser::CalculateStats()
{
    QDir qd(workingDirectory.c_str());

    if(!qd.exists())
        throw std::exception("Folder doesnt exists!");

    if(qd.isEmpty())
    {
        std::vector<std::pair<std::string, std::string>> result;
        result.push_back(std::make_pair("empty", "100%"));
        return result;
    }
    else
    {
        QList<QFileInfo> list = qd.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries);
        return strat->Calculate(list);
    }
}

void FileBrowser::SetStrat(FileBrowser::Strategy newStrat)
{
    if(strat != nullptr)
        delete strat;

    switch (newStrat){
        case FileBrowser::Strategy::ByType:
        {
            strat = new Extention_CalculationStrategy();
            break;
        }
        case FileBrowser::Strategy::EachFile:
        {
            strat = new EachElement_CalculationStrategy();
            break;
        }
        default:
        {
            throw std::exception("Wrong strategy number!");
        }
    }
}
