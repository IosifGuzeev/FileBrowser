#include <QApplication>
#include <QDir>
#include <iostream>
#include <filebrowser.h>
#include "mainwindow.h"
#include <QChart>
#include <QFileInfo>
#include <QBarSeries>
#include <QBarSet>
#include <QPieSeries>
#include <QPieSlice>
#include <QStackedBarSeries>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
