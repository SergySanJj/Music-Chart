#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chart.h"
#include "genres.h"

#include "artistsmodel.h"
#include "artistslistmodel.h"
#include "compositionsmodel.h"

#include "filterartistgenreproxy.h"

#include "addartistdialog.h"
#include "addcompositiondialog.h"

#include <random>

#include <QMainWindow>
#include <QDate>
#include <QThread>

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
    void addArtistSlot(const std::string &_name, const std::vector<Genres> &_preferredGenres);
    void addCompositionSlot(const std::string &_artist, const std::string &_name, Genres _genre, QDate _releaseDate);
    void addArtistButtonClicked();
    void addCompositionButtonClicked();
    void updateButtonClicked();

    void filter();

    void clearFilter();

private:
    Ui::MainWindow *ui;

    Chart chart;

    artistsModel* artModel;
    artistsListModel* artListModel;
    compositionsModel* compModel;

    filterArtistGenreProxy *compProxy;
    QSortFilterProxyModel *artProxy;

    std::vector<QCheckBox*> genreCheckBoxes;

    void updateWeekDay();

};

#endif // MAINWINDOW_H
