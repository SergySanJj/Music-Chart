#pragma once

#include "artist.h"
#include "composition.h"

#include <vector>
#include <memory>

class Chart
{
public:
    Chart();

    bool addArtist(std::string _name, std::vector<Genres> _preferedGenres, double _popularity);

    bool addComposition(std::string _artist, std::string _name, Genres _genre, QDateTime _releaseDate, double _popularity);

    bool addComposition(std::shared_ptr<Artist> _artist, std::string _name, Genres _genre, QDateTime _releaseDate, double _popularity);

    void update();

private:
    std::vector<std::shared_ptr<Artist> > artists;
    std::vector<std::shared_ptr<Composition> > compositions;
};

