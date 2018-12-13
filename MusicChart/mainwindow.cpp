#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /// Test artists and compositions
    addTestArtistAndCompositions();



    artModel = new artistsModel(chart,this);
    artListModel = new artistsBoxModel(chart,this);
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
    ui->ArtistsView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->compositionsView->setModel(compProxy);
    ui->compositionsView->setColumnWidth(0,150);
    ui->compositionsView->setColumnWidth(1,150);
    ui->compositionsView->setColumnWidth(2,100);
    ui->compositionsView->setColumnWidth(3,100);
    ui->compositionsView->setSelectionBehavior(QAbstractItemView::SelectRows);

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
    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)),this, SLOT(updateButtonClicked()));
    connect(ui->filterButton,SIGNAL(clicked()),this,SLOT(filter()));
    connect(ui->clearFilterButton,SIGNAL(clicked()),this,SLOT(clearFilter()));

    connect(ui->compositionHistoryButton,SIGNAL(clicked()),this,SLOT(showCompositionHistoryButtonClicked()));

    connect(ui->ArtistsView, SIGNAL(clicked(QModelIndex)), this, SLOT(artistChosen(QModelIndex)));
    connect(ui->compositionsView, SIGNAL(clicked(QModelIndex)), this, SLOT(compositionChosen(QModelIndex)));

    updateButtonClicked();

    ui->updatingLabel->setStyleSheet("color: rgba(0,0,0,0);");

    updateWeekDay();

    artModel->sort(1,Qt::SortOrder::DescendingOrder);
    compModel->sort(4,Qt::SortOrder::DescendingOrder);

    ui->compositionsView->selectRow(0);
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

    chart.update(ui->dateEdit->date());


    artModel->layoutChanged();
    compModel->layoutChanged();


    style()->unpolish(ui->updatingLabel);
    ui->updatingLabel->setStyleSheet("color: rgba(0,0,0,0);");
    style()->polish(ui->updatingLabel);


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
            genreRegExp += box->text()+"|";
    }

    if (genreRegExp != "(")
        genreRegExp[genreRegExp.size()-1] = ')';
    else
        genreRegExp = ".*";

    compProxy->setGenreFilter(genreRegExp);

    // filter by artist
    if (ui->ArtistFilterBox->currentText() == "**all**")
        compProxy->setArtistFilter(".*");
    else
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

    ui->ArtistFilterBox->setCurrentIndex(0);
}

void MainWindow::showCompositionHistoryButtonClicked()
{
    artModel->layoutAboutToBeChanged();
    compModel->layoutAboutToBeChanged();

    std::size_t row = 0;
    row = static_cast<std::size_t>(
                compProxy->mapToSource(ui->compositionsView->currentIndex()).row());

    artModel->layoutChanged();
    compModel->layoutChanged();

    compositionHistoryDialog *dial =
            new compositionHistoryDialog(chart,ui->dateEdit->date(),row,this);

    dial->exec();
}

void MainWindow::artistChosen(const QModelIndex &current)
{
    ui->ArtistFilterBox->setCurrentIndex(current.row()+1);
    filter();
}

void MainWindow::compositionChosen(const QModelIndex &current)
{
    int row = static_cast<int>(chart.getArtistIndex(
                                   chart.getCompositionArtistName(
                                       static_cast<std::size_t>(
                                           compProxy->mapToSource(current).row()))));

    ui->ArtistsView->selectRow(row);
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

void MainWindow::addTestArtistAndCompositions()
{
    chart.addArtist("Queen",{Genres::Rock});
    chart.addArtist("Eminem",{Genres::HipHop});
    chart.addArtist("Lady Gaga",{Genres::Pop});
    chart.addArtist("Multigenre rocker",{Genres::Rock, Genres::Alternative});

    chart.addComposition("Queen","queen1",Genres::Rock,QDate(1986,3,17));
    chart.addComposition("Queen","queen2",Genres::Rock,QDate(1986,3,17));
    chart.addComposition("Queen","queen3",Genres::Rock,QDate(1986,3,17));
    chart.addComposition("Queen","queen4",Genres::Rock,QDate(1987,5,20));
    chart.addComposition("Queen","queen5",Genres::Alternative,QDate(1988,6,21));

    chart.addComposition("Eminem","eminem1",Genres::HipHop,QDate(1996,1,17));
    chart.addComposition("Eminem","eminem2",Genres::HipHop,QDate(1996,2,22));
    chart.addComposition("Eminem","eminem3",Genres::HipHop,QDate(2000,2,21));
    chart.addComposition("Eminem","eminem4",Genres::HipHop,QDate(2002,2,1));

    chart.addComposition("Lady Gaga","lady1",Genres::Pop,QDate(2006,3,17));
    chart.addComposition("Lady Gaga","lady2",Genres::Pop,QDate(2006,4,1));
    chart.addComposition("Lady Gaga","lady3",Genres::Pop,QDate(2006,5,17));
    chart.addComposition("Lady Gaga","lady4",Genres::Pop,QDate(2006,6,3));
    chart.addComposition("Lady Gaga","lady5",Genres::Pop,QDate(2007,7,11));
    chart.addComposition("Lady Gaga","lady6",Genres::Pop,QDate(2007,8,19));

    chart.addComposition("Multigenre rocker","mr1 rock",Genres::Rock,QDate(2003,8,19));
    chart.addComposition("Multigenre rocker","mr1 pop",Genres::Pop,QDate(2004,8,19));
    chart.addComposition("Multigenre rocker","mr1 alternative",Genres::Alternative,QDate(2005,8,19));
    chart.addComposition("Multigenre rocker","mr1 hip hop",Genres::HipHop,QDate(2015,8,19));
}
