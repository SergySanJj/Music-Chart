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

    double getPopularity() const;

    std::string getName() const;

    std::string getArtistName() const;

    QDate getReleaseDate() const;

    Genres getGenre() const;

    void normalize(double a, double b);

    std::string getGenresString()
    {
        return getGenreString(genre);
    }

private:
    std::shared_ptr<Artist> artist;
    Genres genre;
    QDate releaseDate;
};
