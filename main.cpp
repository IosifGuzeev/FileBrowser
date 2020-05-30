#include <QCoreApplication>
#include <QDir>
#include <iostream>
#include <filebrowser.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileBrowser fb("C:/tests", FileBrowser::Strategy::EachFile);
    for(auto& e: fb.Calculate())
        std::cout << e.first << ' ' << e.second << std::endl;
    QDir qd("C:/tests");
    return a.exec();
}
