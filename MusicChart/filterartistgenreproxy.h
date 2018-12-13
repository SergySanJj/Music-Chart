#ifndef FILTERARTISTGENREPROXY_H
#define FILTERARTISTGENREPROXY_H

#include <QSortFilterProxyModel>

class filterArtistGenreProxy: public QSortFilterProxyModel{
    Q_OBJECT
public:
    explicit filterArtistGenreProxy(QObject* parent= nullptr):
        QSortFilterProxyModel(parent){
        //general parameters for the custom model
        artistRegExp.setCaseSensitivity(Qt::CaseInsensitive);
        genreRegExp.setCaseSensitivity(Qt::CaseInsensitive);
        genreRegExp.setPatternSyntax(QRegExp::RegExp);
        artistRegExp.setPatternSyntax(QRegExp::RegExp);
    }

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const  override{
        QModelIndex artistIndex = sourceModel()->index(sourceRow, 0, sourceParent);
        QModelIndex genreIndex = sourceModel()->index(sourceRow, 2, sourceParent);

        QString artist = sourceModel()->data(artistIndex).toString();
        QString genre = sourceModel()->data(genreIndex).toString();

        return (artist.contains(artistRegExp) && genre.contains(genreRegExp));
    }
public slots:
    void setArtistFilter(const QString& regExp){
        artistRegExp.setPattern(regExp);
        invalidateFilter();
    }
    void setGenreFilter(const QString& regExp){
        genreRegExp.setPattern(regExp);
        invalidateFilter();
    }
private:
    QRegExp artistRegExp;
    QRegExp genreRegExp;
};

#endif // FILTERARTISTGENREPROXY_H
