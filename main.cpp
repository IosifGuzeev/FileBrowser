#include <QCoreApplication>
#include <QDir>
#include <iostream>
#include <filebrowser.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto writer = new ConsoleWriter();

    FileBrowser fb("C:/tests", FileBrowser::Strategy::EachFile);
    for(auto& e: fb.CalculateStats())
        writer->Write(e.first + '\t' + e.second);
    return a.exec();
}
