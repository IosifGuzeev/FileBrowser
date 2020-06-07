#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H
#pragma once
#include <utility>
#include <vector>
#include <QAbstractTableModel>

class FileExplorerModel final : public QAbstractTableModel
{
    Q_OBJECT

public:
    using fileStat = std::pair<std::string, std::string>;
    FileExplorerModel(std::vector<fileStat> data = std::vector<fileStat>(), QObject* parent = nullptr);

private:
    //Представляемые нами данные
    std::vector<fileStat> filesStat;

    //Реализация метода возвращающего количество строк (используется для построения таблицы)
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    //Реализация метода возвращающего количество столбцов (используется для построения таблицы)
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    //Возвращает данные лежащие в ячейке с индексом index для действий с кодом role
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    //Возвращает заголовок столбца/строки (зависит от значения orientation) таблицы для действия с кодом role
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};
#endif // FILEEXPLORERMODEL_H
