#ifndef ARTISTSBOXMODEL_H
#define ARTISTSBOXMODEL_H

#include "chart.h"

#include <QAbstractListModel>

class artistsBoxModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit artistsBoxModel(Chart &_chart,QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    Chart *chart;
};

#endif // ARTISTSBOXMODEL_H
