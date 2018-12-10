#include "artistslistmodel.h"

artistsListModel::artistsListModel(Chart &_chart, QObject *parent)
    : QAbstractListModel(parent)
{
    chart = &_chart;
}

int artistsListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return static_cast<int>(chart->artists.size());
}

QVariant artistsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole) {
        int row = index.row();
        return QString::fromStdString(chart->artists[static_cast<std::size_t>(row)]->getName());
    }
    return QVariant();
}
