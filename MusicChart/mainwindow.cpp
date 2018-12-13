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


    compProxy = new filterArtistGenreProxy(this);
    artProxy = new QSortFilterProxyModel(this);

    compProxy->setSourceModel(compModel);
    artProxy->setSourceModel(artModel);


    ui->dateEdit->setDate(QDate::currentDate());

    ui->ArtistsView->setModel(artProxy);
    ui->ArtistsView->setColumnWidth(0,150);
    ui->ArtistsView->setColumnWidth(1,100);
    ui->ArtistsView->setColumnWidth(2,240);

    ui->compositionsView->setModel(compProxy);
    ui->compositionsView->setColumnWidth(0,150);
    ui->compositionsView->setColumnWidth(1,150);
    ui->compositionsView->setColumnWidth(2,100);
    ui->compositionsView->setColumnWidth(3,100);

    ui->ArtistFilterBox->setModel(artListModel);

    for (int genre=Genres::Rock;genre!=Genres::Chillout;genre++)
    {
        auto newCheckBox = new QCheckBox();

        newCheckBox->setText(QString::fromStdString(getGenreString(Genres(genre))));

        ui->GenresLayout->layout()->addWidget(newCheckBox);

        genreCheckBoxes.push_back(newCheckBox);
    }



    connect(ui->AddArtist, SIGNAL(clicked()),this,SLOT(addArtistButtonClicked()));
    connect(ui->AddComposition, SIGNAL(clicked()),this,SLOT(addCompositionButtonClicked()));
    connect(ui->updateButton,SIGNAL(clicked()),this,SLOT(updateButtonClicked()));
    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)),this, SLOT(updateButtonClicked()));
    connect(ui->filterButton,SIGNAL(clicked()),this,SLOT(filter()));
    connect(ui->clearFilterButton,SIGNAL(clicked()),this,SLOT(clearFilter()));

    updateButtonClicked();

    ui->updatingLabel->setStyleSheet("color: rgba(0,0,0,0);");

    updateWeekDay();

    /// TODO: here
    //compProxy->setFilterRegExp(QRegExp("Rock",Qt::CaseInsensitive,QRegExp::FixedString));
    //compProxy->setFilterKeyColumn(2);


    artModel->sort(1,Qt::SortOrder::DescendingOrder);
    compModel->sort(4,Qt::SortOrder::DescendingOrder);


    //ui->ArtistsView->sortByColumn(1,Qt::SortOrder::DescendingOrder);
    //ui->compositionsView->sortByColumn(4,Qt::SortOrder::DescendingOrder);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete artModel;
    delete compModel;
}

void MainWindow::addArtistSlot(const std::string &_name, const std::vector<Genres> &_preferredGenres)
{
    artModel->addArtist(_name,_preferredGenres);

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

    artModel->sort(1,Qt::SortOrder::DescendingOrder);
    compModel->sort(4,Qt::SortOrder::DescendingOrder);
}

void MainWindow::filter()
{
    // filter by genres
    QString genreRegExp = "(";
    for (auto &box:genreCheckBoxes)
    {
        if (box->checkState())
        {
            genreRegExp += box->text()+"|";
        }
    }
    if (genreRegExp != "(")
        genreRegExp[genreRegExp.size()-1] = ')';
    else
        genreRegExp = ".*";

    compProxy->setGenreFilter(genreRegExp);
    // filter by artist

    compProxy->setArtistFilter(ui->ArtistFilterBox->currentText());

}

void MainWindow::clearFilter()
{
    compProxy->setArtistFilter(".*");
    compProxy->setGenreFilter(".*");

    for (auto &box:genreCheckBoxes)
    {
        box->setCheckState(Qt::CheckState::Unchecked);
    }
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
