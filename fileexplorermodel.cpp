#include "fileexplorermodel.h"
#define COLUMNS_COUNT 2

FileExplorerModel::FileExplorerModel(std::vector<fileStat> data, QObject* parent):QAbstractTableModel(parent), filesStat(data)
{
}

int FileExplorerModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return filesStat.size();
}

int FileExplorerModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return COLUMNS_COUNT;
}

QVariant FileExplorerModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || filesStat.size() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();

    switch (index.column())
    {
        case 0:
            return filesStat[index.column()].first.c_str();

        case 1:
        {
            return filesStat[index.column()].second.c_str();
        }
        default:
            QVariant();
    }
}

QVariant FileExplorerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Vertical)
        return section;

    switch (section)
    {
    case 0:
        return trUtf8("Название");

    case 1:
        return trUtf8("Размер в процентах");

    default:
        return QVariant();
    }
    return QVariant();

}
