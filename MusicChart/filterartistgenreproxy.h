#ifndef FILTERARTISTGENREPROXY_H
#define FILTERARTISTGENREPROXY_H

#include <QSortFilterProxyModel>

class filterArtistGenreProxy: public QSortFilterProxyModel{
    Q_OBJECT

public:
    explicit filterArtistGenreProxy(QObject* parent= nullptr);

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const  override;

public slots:
    void setArtistFilter(const QString& regExp);

    void setGenreFilter(const QString& regExp);

    void refilter();

private:
    QRegExp artistRegExp;
    QRegExp genreRegExp;
};

#endif // FILTERARTISTGENREPROXY_H
