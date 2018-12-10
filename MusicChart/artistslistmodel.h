#ifndef ARTISTSLISTMODEL_H
#define ARTISTSLISTMODEL_H

#include "chart.h"

#include <QAbstractListModel>

class artistsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit artistsListModel(Chart &_chart, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    Chart *chart;
};

#endif // ARTISTSLISTMODEL_H
