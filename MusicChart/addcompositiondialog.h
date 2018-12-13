#ifndef ADDCOMPOSITIONDIALOG_H
#define ADDCOMPOSITIONDIALOG_H

#include "chart.h"
#include "genres.h"
#include "artistslistmodel.h"

#include <QDialog>
#include <QRegExpValidator>

namespace Ui {
class addCompositionDialog;
}

class addCompositionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addCompositionDialog(Chart &chart, QWidget *parent = nullptr);
    ~addCompositionDialog();
public slots:
    void onAddButtonClicked();
signals:
    void sendCompositionData(const std::string &_artist, const std::string &_name, Genres _genre, QDate _releaseDate);

private:
    Ui::addCompositionDialog *ui;
    artistsListModel* artListModel;
};

#endif // ADDCOMPOSITIONDIALOG_H
