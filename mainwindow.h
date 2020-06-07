#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include "fileexplorermodel.h"
#include "filebrowser.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
private slots:

	void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);
    //Новый сигнал, отвечает за обработку изменения в ComboBox
    void on_stratSelectionSlot(QString msg);
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
private:
    FileBrowser* fileBrowser;
    FileExplorerModel *fileModel;
	QFileSystemModel *dirModel;
	QTreeView *treeView;
	QTableView *tableView;
    QString curentDirectory;
};

#endif // MAINWINDOW_H
