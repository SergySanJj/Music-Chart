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

    ui->artistName->setValidator(new QRegExpValidator(QRegExp("([a-z]|[0-9]| )*",Qt::CaseSensitivity::CaseInsensitive)));

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
    std::string name = ui->artistName->text().toStdString();

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
