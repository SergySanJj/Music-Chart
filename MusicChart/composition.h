#pragma once

#include "artist.h"
#include "genres.h"

#include <memory>
#include <QDateTime>

class Artist;

class Composition
{
public:
    /// no empty constructor
    //Composition();

    Composition(std::shared_ptr<Artist> _artist, std::string _name, Genres _genre, QDateTime _releaseDate, double _popularity):
        artist(_artist), name(std::move(_name)), genre(_genre), releaseDate(_releaseDate), popularity(_popularity){}

    void updatePopularity(QDateTime currentDate);

private:
    std::shared_ptr<Artist> artist;
    std::string name;
    Genres genre;
    QDateTime releaseDate;
    double popularity;
};
