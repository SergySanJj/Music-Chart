#include "addcompositiondialog.h"
#include "ui_addcompositiondialog.h"

addCompositionDialog::addCompositionDialog(Chart &chart, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addCompositionDialog)
{
    ui->setupUi(this);

    artListModel = new artistsListModel(chart,this);

    ui->dateEdit->setDate(QDate::currentDate());

    ui->ArtistBox->setModel(artListModel);

    ui->NameText->setValidator(new QRegExpValidator(QRegExp("([a-z]|[0-9]| )*",Qt::CaseSensitivity::CaseInsensitive)));

    for (int i=Genres::Rock;i<=Genres::Chillout;i++)
    {
        ui->GenreBox->addItem(QString::fromStdString(getGenreString(Genres(i))));
    }

    connect(ui->AddButton,SIGNAL(clicked()),this,SLOT(onAddButtonClicked()));
    connect(ui->CancelButton,SIGNAL(clicked()),this,SLOT(close()));

}

addCompositionDialog::~addCompositionDialog()
{
    delete ui;
}

void addCompositionDialog::onAddButtonClicked()
{
    emit sendCompositionData(ui->ArtistBox->currentText().toStdString(),ui->NameText->text().toStdString(),Genres(ui->GenreBox->currentIndex()),ui->dateEdit->date());
    this->close();
}
