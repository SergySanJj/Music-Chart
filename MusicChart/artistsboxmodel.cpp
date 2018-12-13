#include "artistsboxmodel.h"

artistsBoxModel::artistsBoxModel(Chart &_chart, QObject *parent)
    : QAbstractListModel(parent)
{
    chart = &_chart;
}

int artistsBoxModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return static_cast<int>(chart->artists.size()+1);
}

QVariant artistsBoxModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole) {
        int row = index.row();
        if (row == 0)
            return QString("**all**");
        else
            return QString::fromStdString(chart->artists[static_cast<std::size_t>(row-1)]->getName());
    }
    return QVariant();
}
