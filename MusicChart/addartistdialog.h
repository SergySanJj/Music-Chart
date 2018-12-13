#ifndef ADDARTISTDIALOG_H
#define ADDARTISTDIALOG_H

#include "genres.h"

#include <vector>
#include <string>

#include <QDialog>
#include <QRegExpValidator>
#include <QCheckBox>

namespace Ui {
class AddArtistDialog;
}

class AddArtistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddArtistDialog(QWidget *parent = nullptr);
    ~AddArtistDialog();

public slots:
    void onAdd();

signals:
    void sendArtistData(std::string _name,  std::vector<Genres> _preferredGenres);

private:
    Ui::AddArtistDialog *ui;
    std::vector<QCheckBox*> genreCheckBoxes;
};

#endif // ADDARTISTDIALOG_H
