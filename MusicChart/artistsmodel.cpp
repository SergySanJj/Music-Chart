#include "artistsmodel.h"

artistsModel::artistsModel(QObject *parent) : QAbstractTableModel(parent)
    {}

artistsModel::artistsModel(Chart &_chart, QObject *parent)
    : QAbstractTableModel(parent)
{
    chart = &_chart;
}

QVariant artistsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                QStringList headers{
                                   "Name",
                                   "Popularity"
                                    };
                return headers[section];
            }
        }

    return QVariant();
}

int artistsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
            return 0;

    return static_cast<int>(chart->artists.size());
}

int artistsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
           return 0;

   return 2;
}

QVariant artistsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
           return QVariant();

       if (role == Qt::DisplayRole) {

           int row = index.row();
           int column = index.column();
           std::shared_ptr<Artist> artist = chart->artists[static_cast<std::size_t>(row)];
           switch(column) {
               case 0:
                   return QString::fromStdString(artist->getName());
               case 1:
                   return QString::number(artist->getPopularity());
           }
       }
       return QVariant();
}

bool artistsModel::addArtist(const std::string &_name, const std::vector<Genres> &_preferedGenres)
{
    emit layoutAboutToBeChanged();
    this->insertRow(static_cast<int>(chart->artists.size()));
    bool res = chart->addArtist(_name, _preferedGenres);
    emit layoutChanged();
    return res;
}

void artistsModel::emitPeparation()
{
    emit layoutAboutToBeChanged();
}

void artistsModel::emitChanged(){
    emit layoutChanged();
}