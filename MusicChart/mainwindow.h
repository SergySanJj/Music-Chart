#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chart.h"
#include "genres.h"

#include "artistsmodel.h"
#include "artistslistmodel.h"
#include "artistsboxmodel.h"
#include "compositionsmodel.h"

#include "filterartistgenreproxy.h"

#include "addartistdialog.h"
#include "addcompositiondialog.h"
#include "compositionhistorydialog.h"

#include <random>

#include <QMainWindow>
#include <QDate>
#include <QThread>
#include <QFile>


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

    void showCompositionHistoryButtonClicked();

    void artistChosen(const QModelIndex &current);

    void compositionChosen(const QModelIndex &current);

private:
    Ui::MainWindow *ui;

    void updateWeekDay();

    void addTestArtistAndCompositions();

    /// Stores chart object that is used in models
    Chart chart;

    /// Chart models for tables and lists
    artistsModel* artModel;
    artistsBoxModel* artListModel;
    compositionsModel* compModel;

    /// Models for sort/filter
    filterArtistGenreProxy *compProxy;
    QSortFilterProxyModel *artProxy;

    std::vector<QCheckBox*> genreCheckBoxes;
};

#endif // MAINWINDOW_H
