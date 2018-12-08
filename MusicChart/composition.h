#pragma once

#include "artist.h"
#include "genres.h"

#include <memory>
#include <QDateTime>

class Artist;

class Composition
{
public:
    Composition();

private:
    std::string name;
    Genres genre;
    QDateTime releaseDate;
    std::shared_ptr<Artist> artist;
};
