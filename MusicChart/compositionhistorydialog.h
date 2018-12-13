#ifndef COMPOSITIONHISTORYDIALOG_H
#define COMPOSITIONHISTORYDIALOG_H

#include "qcustomplot.h"
#include "chart.h"

#include <QDialog>
#include <QVector>
#include <QDate>


namespace Ui {
class compositionHistoryDialog;
}

class compositionHistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit compositionHistoryDialog(Chart &_chart, QDate _date, std::size_t _row, QWidget *parent = nullptr);
    ~compositionHistoryDialog();

private:
    Ui::compositionHistoryDialog *ui;

    Chart *chart;

    QDate date;

    std::size_t row;
};

#endif // COMPOSITIONHISTORYDIALOG_H
