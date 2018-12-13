#include "filterartistgenreproxy.h"


filterArtistGenreProxy::filterArtistGenreProxy(QObject *parent):
    QSortFilterProxyModel(parent){

    artistRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    genreRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    genreRegExp.setPatternSyntax(QRegExp::RegExp);
    artistRegExp.setPatternSyntax(QRegExp::RegExp);
}

bool filterArtistGenreProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const{
    QModelIndex artistIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex genreIndex = sourceModel()->index(sourceRow, 2, sourceParent);

    QString artist = sourceModel()->data(artistIndex).toString();
    QString genre = sourceModel()->data(genreIndex).toString();

    return (artist.contains(artistRegExp) && genre.contains(genreRegExp));
}

void filterArtistGenreProxy::setArtistFilter(const QString &regExp){
    artistRegExp.setPattern(regExp);
    invalidateFilter();
}

void filterArtistGenreProxy::setGenreFilter(const QString &regExp){
    genreRegExp.setPattern(regExp);
    invalidateFilter();
}

void filterArtistGenreProxy::refilter(){
    invalidateFilter();
}
