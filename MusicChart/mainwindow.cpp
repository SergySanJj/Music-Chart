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
    chart.addComposition("Eminem","It's a kind of",Genres::HipHop,QDate(1996,3,17));
    chart.addComposition("Lady Gaga","It's a kind",Genres::Pop,QDate(2006,3,17));

    artModel = new artistsModel(chart,this);
    artListModel = new artistsListModel(chart,this);
    compModel = new compositionsModel(chart,this);

    ui->dateEdit->setDate(QDate::currentDate());

    ui->ArtistsView->setModel(artModel);
    ui->ArtistsView->setColumnWidth(0,150);
    ui->ArtistsView->setColumnWidth(1,100);

    ui->compositionsView->setModel(compModel);
    ui->compositionsView->setColumnWidth(0,150);
    ui->compositionsView->setColumnWidth(1,150);
    ui->compositionsView->setColumnWidth(2,100);
    ui->compositionsView->setColumnWidth(3,100);


    connect(ui->AddArtist, SIGNAL(clicked()),this,SLOT(addArtistButtonClicked()));
    connect(ui->AddComposition, SIGNAL(clicked()),this,SLOT(addCompositionButtonClicked()));
    connect(ui->updateButton,SIGNAL(clicked()),this,SLOT(updateButtonClicked()));
    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)),this, SLOT(updateButtonClicked()));

    updateButtonClicked();

    ui->updatingLabel->setStyleSheet("color: rgba(0,0,0,0);");

    updateWeekDay();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete artModel;
    delete compModel;
}

void MainWindow::addArtistSlot(const std::string &_name, const std::vector<Genres> &_preferedGenres)
{
    artModel->addArtist(_name,_preferedGenres);

    updateButtonClicked();
}

void MainWindow::addCompositionSlot(const std::string &_artist, const std::string &_name, Genres _genre, QDate _releaseDate)
{
    chart.addComposition(_artist,_name,_genre,_releaseDate);

    updateButtonClicked();
}

void MainWindow::addArtistButtonClicked()
{
    auto dial = new AddArtistDialog(this);

    connect(dial, SIGNAL(sendArtistData(std::string,std::vector<Genres>)),this,SLOT(addArtistSlot(std::string,std::vector<Genres>)));

    dial->exec();
}

void MainWindow::addCompositionButtonClicked()
{
    auto dial = new addCompositionDialog(chart,this);

    connect(dial, SIGNAL(sendCompositionData(std::string,std::string, Genres, QDate)),this,SLOT(addCompositionSlot(std::string,std::string, Genres, QDate)));

    dial->exec();
}

void MainWindow::updateButtonClicked()
{
     style()->unpolish(ui->updatingLabel);
     ui->updatingLabel->setStyleSheet("color: rgba(110,110,110,255);");
     style()->polish(ui->updatingLabel);

    artModel->layoutAboutToBeChanged();
    compModel->layoutAboutToBeChanged();

    std::thread worker([&](){
        chart.update(ui->dateEdit->date());
    });


    artModel->layoutChanged();
    compModel->layoutChanged();

    if (worker.joinable()){
        worker.join();
        style()->unpolish(ui->updatingLabel);
        ui->updatingLabel->setStyleSheet("color: rgba(0,0,0,0);");
        style()->polish(ui->updatingLabel);
    }

    updateWeekDay();
}

void MainWindow::updateWeekDay(){
    QString dayOfWeek;
    int currDay = ui->dateEdit->date().dayOfWeek();
    switch (currDay)
    {
    case 1:
        dayOfWeek = "Mon";
        break;
    case 2:
        dayOfWeek = "Tue";
        break;
    case 3:
        dayOfWeek = "Wed";
        break;
    case 4:
        dayOfWeek = "Thu";
        break;
    case 5:
        dayOfWeek = "Fri";
        break;
    case 6:
        dayOfWeek = "Sat";
        break;
    case 7:
        dayOfWeek = "Sun";
        break;
    default:
        dayOfWeek = "Unknown";
        break;
    }
    ui->WeekDay->setText(dayOfWeek);
}
