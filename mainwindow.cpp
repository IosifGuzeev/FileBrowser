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

    chartView = new QChartView();
    chartAdapter = new BarChartAdapter();
    chartView->setChart(chartAdapter->MakeChart(fileBrowser->CalculateStats()));
    viewSplitter->addWidget(treeView);
    viewSplitter->addWidget(tableView);
    viewSplitter->addWidget(chartView);
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
    auto statType = new QComboBox(parent);
    statType->addItem("Each file");
    statType->addItem("By extention");

    //Добавляем ComboBox для выбора типа чарта
    auto chartType = new QComboBox(parent);
    chartType->addItem("Bar chart");
    chartType->addItem("Pie chart");

    //Splitter будет удобен при добавлении дополнительных виджетов в область menu
    auto horizonSplitter = new QSplitter(Qt::Orientation::Horizontal, parent);
    horizonSplitter->addWidget(statType);
    horizonSplitter->addWidget(chartType);
    setMenuWidget(horizonSplitter);

    //Соединяем сигнал об изменении ComboBox с новым сигналом обработки
    //Сигнал об измении стратегии сбора статистики
    connect(statType, SIGNAL(currentTextChanged(QString)),
            this, SLOT(on_stratSelectionSlot(QString)));
    //Сигнал об изменении вида графика
    connect(chartType, SIGNAL(currentTextChanged(QString)),
            this, SLOT(on_chartSelectionSlot(QString)));
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
    chartView->setChart(chartAdapter->MakeChart(data));
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
    chartView->setChart(chartAdapter->MakeChart(data));
}

void MainWindow::on_chartSelectionSlot(QString msg)
{
    delete chartAdapter;
    //Меняем чарт в зависимости от выбранного параметра в ComboBox
    if(msg == "Bar chart")
        chartAdapter = new BarChartAdapter();
    else if(msg == "Pie chart")
        chartAdapter = new PieChartAdapter();
    else
        throw std::exception("This option not impelmented yet!");
    //Обновляем отображение
    fileBrowser->SetDirectory(curentDirectory.toStdString());
    std::vector<FileExplorerModel::fileStat> data = fileBrowser->CalculateStats();
    chartView->setChart(chartAdapter->MakeChart(data));
}


MainWindow::~MainWindow()
{

}
