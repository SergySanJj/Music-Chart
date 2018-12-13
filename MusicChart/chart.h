#pragma once

#include "artist.h"
#include "composition.h"
#include "genres.h"

#include <vector>
#include <memory>
#include <random>
#include <cmath>
#include <limits>

#include <QDate>

class Chart
{
public:
    Chart();

    bool addArtist(const std::string &_name, const std::vector<Genres> &_preferredGenres);

    bool addComposition(const std::string &_artist, const std::string &_name, Genres _genre, QDate _releaseDate);

    //bool addComposition(std::shared_ptr<Artist> _artist, const std::string &_name, Genres _genre, QDateTime _releaseDate);

    void update(const QDate &currentDate);

    bool checkArtistExistance(const std::string &_name) const;

protected:
    void updateGenrePopularity(const QDate &currentDate);

    void updateArtistsPopularity(const QDate &currentDate);

    void updateCompositionsPopularity(const QDate &currentDate);

    void normalizePopularity();

    void setZeroPopularities();

    std::vector<std::shared_ptr<Artist> > artists;
    std::vector<std::shared_ptr<Composition> > compositions;

    friend class artistsModel;
    friend class artistsListModel;
    friend class compositionsModel;
    friend class artistsBoxModel;
};

