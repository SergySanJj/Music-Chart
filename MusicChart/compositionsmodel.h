#ifndef COMPOSITIONSMODEL_H
#define COMPOSITIONSMODEL_H

#include "chart.h"
#include <QAbstractTableModel>

class compositionsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit compositionsModel(Chart &_chart, QObject *parent = nullptr);
    explicit compositionsModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void emitPeparation();

    void emitChanged();

    void sort(int column, Qt::SortOrder order= Qt::AscendingOrder) override;

private:
    Chart *chart=nullptr;
};

#endif // COMPOSITIONSMODEL_H
