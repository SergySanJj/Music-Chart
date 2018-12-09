#include "compositionsmodel.h"

compositionsModel::compositionsModel(Chart &_chart, QObject *parent)
    : QAbstractTableModel(parent)
{
    chart = &_chart;
}

compositionsModel::compositionsModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant compositionsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                QStringList headers{
                                   "Artist",
                                   "Name",
                                   "Release",
                                   "Popularity"
                                    };
                return headers[section];
            }
        }

    return QVariant();
}

int compositionsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return static_cast<int>(chart->compositions.size());
}

int compositionsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 4;
}

QVariant compositionsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
           return QVariant();

       if (role == Qt::DisplayRole) {

           int row = index.row();
           int column = index.column();
           std::shared_ptr<Composition> composition = chart->compositions[static_cast<std::size_t>(row)];
           switch(column) {
               case 0:
                   return QString::fromStdString(composition->getArtistName());
               case 1:
                   return QString::fromStdString(composition->getName());
               case 2:
                   return (composition->getReleaseDate()).toString("MM dd yyyy");
               case 3:
                   return QString::number(composition->getPopularity());
           }
       }
       return QVariant();
}
