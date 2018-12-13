#include "compositionhistorydialog.h"
#include "ui_compositionhistorydialog.h"

compositionHistoryDialog::compositionHistoryDialog(Chart &_chart, QDate _date, std::size_t _row, QWidget *parent):
    QDialog(parent),
    ui(new Ui::compositionHistoryDialog)
{
    ui->setupUi(this);

    chart = &_chart;
    date = _date;
    row = _row;

    ui->nameLabel->setText(QString::fromStdString(chart->getCompositionString(row)));

    auto coords = chart->getCompositionHistory(date,0);

    ui->HistoryPlot->addGraph();
    ui->HistoryPlot->graph(0)->setData(coords.first, coords.second);

    ui->HistoryPlot->xAxis->setLabel("months after release");
    ui->HistoryPlot->yAxis->setLabel("popularity");

    double maxX = (date.toJulianDay()- chart->getCompositionReleaseDate(row).toJulianDay())/30.0 - 1;

    ui->HistoryPlot->xAxis->setRange(0, maxX);
    ui->HistoryPlot->yAxis->setRange(0, 200);
    ui->HistoryPlot->replot();
}

compositionHistoryDialog::~compositionHistoryDialog()
{
    delete ui;
}
