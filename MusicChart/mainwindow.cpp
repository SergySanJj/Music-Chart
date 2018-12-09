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
    compModel = new compositionsModel(chart,this);

    ui->ArtistsView->setModel(artModel);
    ui->ArtistsView->setColumnWidth(0,150);
    ui->ArtistsView->setColumnWidth(1,100);

    ui->compositionsView->setModel(compModel);
    ui->compositionsView->setColumnWidth(0,150);
    ui->compositionsView->setColumnWidth(1,150);
    ui->compositionsView->setColumnWidth(2,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}
