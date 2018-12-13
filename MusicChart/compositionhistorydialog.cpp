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

    ui->HistoryPlot->graph(0)->setBrush(QBrush(QColor(200,200,200,20)));
    ui->HistoryPlot->graph(0)->setPen(QPen(QColor(253, 166, 116),3));

    ui->HistoryPlot->xAxis->setLabel("months after release");
    ui->HistoryPlot->yAxis->setLabel("popularity");

    double maxX = (date.toJulianDay()- chart->getCompositionReleaseDate(row).toJulianDay())/30.0 - 1;

    ui->HistoryPlot->xAxis->setRange(0, maxX);
    ui->HistoryPlot->yAxis->setRange(0, 200);

    ui->HistoryPlot->setBackground(QBrush(QColor(120,120,120)));

    ui->HistoryPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->HistoryPlot->yAxis->setBasePen(QPen(Qt::white, 1));

    ui->HistoryPlot->xAxis->setTickLabelColor(QColor(240,240,240));
    ui->HistoryPlot->yAxis->setTickLabelColor(QColor(240,240,240));

    ui->HistoryPlot->xAxis->setLabelColor(QColor(250,250,250));
    ui->HistoryPlot->yAxis->setLabelColor(QColor(250,250,250));

    ui->HistoryPlot->replot();
}

compositionHistoryDialog::~compositionHistoryDialog()
{
    delete ui;
}
