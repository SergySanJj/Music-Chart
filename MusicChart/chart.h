#pragma once

#include "artist.h"
#include "composition.h"

#include <vector>
#include <memory>
#include <QDate>
#include <random>

class Chart
{
public:
    Chart();

    bool addArtist(const std::string &_name, const std::vector<Genres> &_preferedGenres);

    bool addComposition(const std::string &_artist, const std::string &_name, Genres _genre, QDate _releaseDate);

    //bool addComposition(std::shared_ptr<Artist> _artist, const std::string &_name, Genres _genre, QDateTime _releaseDate);

    void update();

    bool checkArtistExistance(const std::string &_name) const;

protected:
    std::vector<std::shared_ptr<Artist> > artists;
    std::vector<std::shared_ptr<Composition> > compositions;

    //std::vector<std::shared_ptr<Artist> > currentArtists;
    //std::vector<std::shared_ptr<Composition> > currentCompositions;

    friend class artistsModel;
    friend class compositionsModel;
};

