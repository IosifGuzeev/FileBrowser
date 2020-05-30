#include "calculationstrategy.h"

std::vector<std::pair<std::string, std::string>> EachElement_CalculationStrategy::Calculate(QList<QFileInfo> files)
{
    std::vector<std::pair<std::string, std::string>> result;
    std::vector<std::pair<std::string, qint64>> rawResult;

    qint64 totalWeight = 0;

    for(auto fileInfo: files)
    {
        qint64 size = fileInfo.size();
        rawResult.push_back(std::make_pair(fileInfo.fileName().toStdString(), size));
        totalWeight += size;
    }

    if(totalWeight == 0)
    {
        for(auto rawFile: rawResult)
        {
            double procentSize =  100 / rawResult.size();
            std::string num_text = std::to_string(procentSize);
            std::string rounded = num_text.substr(0, num_text.find(".")+3);
            if(rounded == "0.00")
            {
                result.push_back(std::make_pair(rawFile.first, "<0.01%"));
            }
            else
            {
                result.push_back(std::make_pair(rawFile.first, rounded));
            }
        }
    }
    else
    {
        for(auto rawFile: rawResult)
        {
            double procentSize = 100 * float(rawFile.second) / totalWeight;
            std::string num_text = std::to_string(procentSize);
            std::string rounded = num_text.substr(0, num_text.find(".")+3);
            if(rounded == "0.00")
            {
                result.push_back(std::make_pair(rawFile.first, ">0.01%"));
            }
            else
            {
                result.push_back(std::make_pair(rawFile.first, rounded + "%"));
            }
        }
    }
    return result;
}

std::vector<std::pair<std::string, std::string> > Extention_CalculationStrategy::Calculate(QList<QFileInfo> files)
{
    std::vector<std::pair<std::string, std::string>> result;
    return result;
}
