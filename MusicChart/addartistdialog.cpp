#include "addartistdialog.h"
#include "ui_addartistdialog.h"

AddArtistDialog::AddArtistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddArtistDialog)
{
    ui->setupUi(this);

    for (int genre=Genres::Rock;genre!=Genres::Chillout;genre++)
    {
        auto newCheckBox = new QCheckBox();

        newCheckBox->setText(QString::fromStdString(getGenreString(Genres(genre))));

        ui->GenresLayout->layout()->addWidget(newCheckBox);

        genreCheckBoxes.push_back(newCheckBox);
    }

    connect(ui->AddButton,SIGNAL(clicked()),this,SLOT(onAdd()));
    connect(ui->CancelButton,SIGNAL(clicked()),this,SLOT(close()));
}

AddArtistDialog::~AddArtistDialog()
{
    delete ui;
}

void AddArtistDialog::onAdd()
{
    std::vector<Genres> selectedGenres;
    std::string name = ui->artistName->toPlainText().toStdString();

    int cnt = 0;
    for (auto &box:genreCheckBoxes)
    {
        if (box->isChecked())
            selectedGenres.push_back(Genres(cnt));
        cnt++;
    }

    emit sendArtistData(name,selectedGenres);

    close();
}
