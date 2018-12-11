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
                                   "Genre",
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

    return 5;
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
                   return QString::fromStdString(composition->getGenresString());
               case 3:
                   return (composition->getReleaseDate()).toString("dd.MM.yyyy");
               case 4:
                   return QString::number(composition->getPopularity());
           }
       }
       return QVariant();
}

void compositionsModel::emitPeparation(){
    emit layoutAboutToBeChanged();
}

void compositionsModel::emitChanged(){
    emit layoutChanged();
}

void compositionsModel::sort(int column, Qt::SortOrder order)
{

    switch(column) {
            case 1:
                if (order==Qt::AscendingOrder) {
                    std::sort(chart->compositions.begin(), chart->compositions.end(),
                              [](const std::shared_ptr<Composition>& a, const std::shared_ptr<Composition>& b) {
                                    return a->getName()<b->getName();
                              });
                } else {
                    std::sort(chart->compositions.begin(), chart->compositions.end(),
                              [](const std::shared_ptr<Composition>& a, const std::shared_ptr<Composition>& b) {
                                    return a->getName()>b->getName();
                              });
                }
                break;
            case 4:
                if (order==Qt::AscendingOrder) {
                    std::sort(chart->compositions.begin(), chart->compositions.end(),
                              [](const std::shared_ptr<Composition>& a, const std::shared_ptr<Composition>& b) {
                                    return a->getPopularity()<b->getPopularity();
                              });
                } else {
                    std::sort(chart->compositions.begin(), chart->compositions.end(),
                              [](const std::shared_ptr<Composition>& a, const std::shared_ptr<Composition>& b) {
                                    return a->getPopularity()>b->getPopularity();
                              });
                }
                break;

        }
    emit dataChanged(index(0,0),index(static_cast<int>(chart->artists.size()),5));
}
