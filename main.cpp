#include <QCoreApplication>
#include <QDir>
#include <iostream>
#include <filebrowser.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileBrowser fb("C:/tests");
    for(auto& e: fb.Calculate())
        std::cout << e.first << ' ' << e.second << std::endl;
    return a.exec();
}
