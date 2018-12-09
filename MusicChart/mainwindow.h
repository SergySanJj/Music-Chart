#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chart.h"
#include "genres.h"

#include <random>

#include <QMainWindow>
#include <QDate>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Chart chart;
};

#endif // MAINWINDOW_H
