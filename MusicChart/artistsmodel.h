#ifndef ARTISTSMODEL_H
#define ARTISTSMODEL_H

#include "chart.h"

#include <QAbstractTableModel>

class artistsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit artistsModel(QObject *parent = nullptr);
    explicit artistsModel(Chart &_chart, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool addArtist(const std::string &_name, const std::vector<Genres> &_preferedGenres);

    void emitPeparation();

    void emitChanged();

private:
    Chart *chart=nullptr;
};

#endif // ARTISTSMODEL_H
