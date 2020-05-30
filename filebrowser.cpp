#include "filebrowser.h"

FileBrowser::FileBrowser(std::string directory, FileBrowser::Strategy strategy)
{
    workingDirectory = directory;
    switch (strategy) {
        case FileBrowser::Strategy::ByType:
        {
            strat = nullptr;
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

std::vector<std::pair<std::string, std::string> > FileBrowser::Calculate()
{
    QDir qd(workingDirectory.c_str());
    QList<QFileInfo> list = qd.entryInfoList();
    return strat->Calculate(list);
}
