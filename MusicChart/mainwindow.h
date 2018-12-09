#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chart.h"
#include "genres.h"

#include "artistsmodel.h"
#include "compositionsmodel.h"

#include "addartistdialog.h"

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

public slots:
    void addArtistSlot(const std::string &_name, const std::vector<Genres> &_preferedGenres);
    void addCompositionSlot(const std::string &_artist, const std::string &_name, Genres _genre, QDate _releaseDate);
    void addArtistButtonClicked();
    void addCompositionButtonClicked();
    void updateButtonClicked();

private:
    Ui::MainWindow *ui;

    Chart chart;

    artistsModel* artModel;
    compositionsModel* compModel;
};

#endif // MAINWINDOW_H
