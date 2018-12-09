#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chart.addArtist("Queen",{Genres::Rock});
    chart.addArtist("Eminem",{Genres::HipHop});
    chart.addArtist("Lady Gaga",{Genres::Pop});

    chart.addComposition("Queen","It's a kind of magic",Genres::Rock,QDate(1986,3,17));

    artModel = new artistsModel(chart,this);

    ui->ArtistsView->setModel(artModel);
    ui->ArtistsView->setColumnWidth(0,150);
}

MainWindow::~MainWindow()
{
    delete ui;
}
