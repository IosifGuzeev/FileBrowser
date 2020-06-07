#include "mainwindow.h"
#include <QSplitter>
#include <QListView>
#include <QTreeView>
#include <QTextEdit>
#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QStatusBar>
#include <QDebug>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
	: //QWidget(parent)
	  QMainWindow(parent)
{
	//Устанавливаем размер главного окна
    this->setGeometry(100, 100, 1500, 600);
	this->setStatusBar(new QStatusBar(this));
	this->statusBar()->showMessage("Choosen Path: ");
	QString homePath = QDir::homePath();
    curentDirectory = homePath;
	// Определим  файловой системы:
    dirModel =  new QFileSystemModel(this);
	dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	dirModel->setRootPath(homePath);

    //Объект собирающий статистику об обозреваемой директории
    fileBrowser = new FileBrowser(homePath.toStdString());

    QSplitter *viewSplitter = new QSplitter(parent);
	//Показать как дерево, пользуясь готовым видом:
	treeView = new QTreeView();
	treeView->setModel(dirModel);
	treeView->expandAll();

	tableView = new QTableView;
    //Наша новая модель
    fileModel = new FileExplorerModel(fileBrowser->CalculateStats(), this);
    tableView->setModel(fileModel);
    viewSplitter->addWidget(treeView);
    viewSplitter->addWidget(tableView);
    setCentralWidget(viewSplitter);

	QItemSelectionModel *selectionModel = treeView->selectionModel();
	QModelIndex rootIx = dirModel->index(0, 0, QModelIndex());//корневой элемент

	QModelIndex indexHomePath = dirModel->index(homePath);
	QFileInfo fileInfo = dirModel->fileInfo(indexHomePath);

    treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//Выполняем соединения слота и сигнала который вызывается когда осуществляется выбор элемента в TreeView
	connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
			this, SLOT(on_selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
	//Пример организации установки курсора в TreeView относит ельно модельного индекса
	QItemSelection toggleSelection;
	QModelIndex topLeft;
	topLeft = dirModel->index(homePath);
	dirModel->setRootPath(homePath);

	toggleSelection.select(topLeft, topLeft);
	selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);

    //Добавлем ComboBox для выбора стратегии отображения
    auto comboBox = new QComboBox(parent);
    comboBox->addItem("Each file");
    comboBox->addItem("By extention");
    //Splitter будет удобен при добавлении дополнительных виджетов в область menu
    auto horizonSplitter = new QSplitter(Qt::Orientation::Horizontal, parent);
    horizonSplitter->addWidget(comboBox);
    setMenuWidget(horizonSplitter);
    //Соединяем сигнал об изменении ComboBox с новым сигналом обработки
    connect(comboBox, SIGNAL(currentTextChanged(QString)),
            this, SLOT(on_stratSelectionSlot(QString)));
}

//Слот для обработки выбора элемента в TreeView
//выбор осуществляется с помощью курсора

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
	Q_UNUSED(deselected);
	QModelIndex index = treeView->selectionModel()->currentIndex();
	QModelIndexList indexs =  selected.indexes();
	QString filePath = "";

	// Размещаем инфо в statusbar относительно выделенного модельного индекса

	if (indexs.count() >= 1) {
		QModelIndex ix =  indexs.constFirst();
		filePath = dirModel->filePath(ix);
		this->statusBar()->showMessage("Выбранный путь : " + dirModel->filePath(indexs.constFirst()));
    }
    curentDirectory = filePath;
    fileBrowser->SetDirectory(filePath.toStdString());
    std::vector<FileExplorerModel::fileStat> data = fileBrowser->CalculateStats();
    tableView->setModel(new FileExplorerModel(data));
}

void MainWindow::on_stratSelectionSlot(QString msg)
{
    //Меняем стратегию в зависимости от выбранного параметра в ComboBox
    if(msg == "By extention")
        fileBrowser->SetStrat(FileBrowser::Strategy::ByType);
    else if(msg == "Each file")
        fileBrowser->SetStrat(FileBrowser::Strategy::EachFile);
    else
        throw std::exception("This option not impelmented yet!");
    //Обновляем отображение
    fileBrowser->SetDirectory(curentDirectory.toStdString());
    std::vector<FileExplorerModel::fileStat> data = fileBrowser->CalculateStats();
    tableView->setModel(new FileExplorerModel(data));
}


MainWindow::~MainWindow()
{

}
