#include "calculationstrategy.h"

qint64 EachElement_CalculationStrategy::folder_size(QString path, int maxDeep, int deep)
{
    if(deep > maxDeep)
        return 0;

    QDir dir(path);
    if(!dir.exists())
        throw std::exception("Folder doesnt exists!");

    qint64 size = 0;
    for(auto& file: dir.entryInfoList(QDir::NoDotAndDotDot|QDir::Files))
        size += file.size();
    for(auto& folder: dir.entryInfoList(QDir::NoDotAndDotDot|QDir::Dirs))
        size += folder_size(folder.absoluteFilePath(), maxDeep, deep + 1);
    return size;
}

std::vector<std::pair<std::string, std::string>> EachElement_CalculationStrategy::Calculate(QList<QFileInfo> files)
{
    std::vector<std::pair<std::string, std::string>> result;
    std::vector<std::pair<std::string, qint64>> rawResult;

    qint64 totalWeight = 0;

    for(auto fileInfo: files)
    {
        qint64 size;
        if(fileInfo.isFile())
            size = fileInfo.size();
        else
            size = folder_size(fileInfo.absoluteFilePath());
        rawResult.push_back(std::make_pair(fileInfo.fileName().toStdString(), size));
        totalWeight += size;
    }
    if (rawResult.size() == 0)
    {
        result.push_back(std::make_pair("empty", "100%"));
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
                result.push_back(std::make_pair(rawFile.first, "<0.01%"));
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
    std::map<std::string, qint64> rawResult;

    qint64 totalWeight = 0;

    for(auto fileInfo: files)
    {
        if(fileInfo.isFile())
        {
            qint64 size = fileInfo.size();
            auto suffix = "*." + fileInfo.suffix().toStdString();
            if(rawResult.find(suffix) == rawResult.end())
            {
                rawResult[suffix] = size;
            }
            else
            {
                rawResult[suffix] += size;
            }
            totalWeight += size;
        }
    }
    if (rawResult.size() == 0)
    {
        result.push_back(std::make_pair("empty", "100%"));
    }
    if(totalWeight == 0)
    {
        for(auto rawFile: rawResult)
        {
            double procentSize =  100.0 / rawResult.size();
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
                result.push_back(std::make_pair(rawFile.first, "<0.01%"));
            }
            else
            {
                result.push_back(std::make_pair(rawFile.first, rounded + "%"));
            }
        }
    }
    return result;
}
