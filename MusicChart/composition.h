#pragma once

#include "chartitem.h"
#include "artist.h"
#include "genres.h"

#include <memory>
#include <QDateTime>

class Artist;

class Composition : public ChartItem
{
public:
    /// no empty constructor
    //Composition();

    Composition(std::shared_ptr<Artist> _artist, const std::string &_name, Genres _genre, QDateTime _releaseDate);

    void updatePopularity(QDateTime currentDate);

    double getPopularity() const;

private:
    std::shared_ptr<Artist> artist;
    Genres genre;
    QDateTime releaseDate;
};
