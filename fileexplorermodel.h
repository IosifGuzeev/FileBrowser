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
    std::vector<fileStat> filesStat;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};
#endif // FILEEXPLORERMODEL_H
