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
    //В случае некорректных индексов или неверных кодов ролей (не считывания) мы возвращаем пустую ячейку
    if (!index.isValid() || filesStat.size() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();

    switch (index.column())
    {
        //Первый столбец отвечает за имя элемента
        case 0:
            return filesStat[index.row()].first.c_str();
        //Второй столбец отвечает за статистику об элементе
        case 1:
            return filesStat[index.row()].second.c_str();
        default:
            QVariant();
    }
}

QVariant FileExplorerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //В случае неверного кода возвращаем пустую ячейку
    if (role != Qt::DisplayRole)
        return QVariant();
    //Вертикальными заголовками служат номера строк
    if (orientation == Qt::Vertical)
        return section;
    //Имена столбцов
    switch (section)
    {
    case 0:
        return trUtf8("Название");

    case 1:
        return trUtf8("Размер в процентах");

    default:
        return QVariant();
    }
}
