#pragma once

#include "chartitem.h"
#include "artist.h"
#include "genres.h"

#include <memory>
#include <random>

#include <QDate>

class Artist;

class Composition : public ChartItem
{
public:
    /// no empty constructor
    //Composition();

    Composition(std::shared_ptr<Artist> &_artist, const std::string &_name, Genres _genre, QDate _releaseDate);

    void updatePopularity(QDate currentDate);

    std::string getArtistName() const;

    QDate getReleaseDate() const;

    Genres getGenre() const;

    void setZeroPopularity();

    std::string getGenresString() const;

private:
    std::shared_ptr<Artist> artist;
    Genres genre;
    QDate releaseDate;

    int stognationAfter;

    void normalizeNegative();
};
