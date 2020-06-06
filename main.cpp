#include <QApplication>
#include <QDir>
#include <iostream>
#include <filebrowser.h>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
