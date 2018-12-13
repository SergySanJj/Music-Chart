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
#include <QVector>

class Chart
{
public:
    Chart();

    bool addArtist(const std::string &_name, const std::vector<Genres> &_preferredGenres);

    bool addComposition(const std::string &_artist, const std::string &_name, Genres _genre, QDate _releaseDate);

    //bool addComposition(std::shared_ptr<Artist> _artist, const std::string &_name, Genres _genre, QDateTime _releaseDate);

    void update(const QDate &currentDate);

    bool checkArtistExistance(const std::string &_name) const;

    std::string getCompositionString(std::size_t row) const;

    std::pair<QVector<double>,QVector<double> > getCompositionHistory(const QDate &currentDate, std::size_t row);

    double getCompositionPopularity(std::size_t row) const;

    QDate getCompositionReleaseDate(std::size_t row) const;

    std::size_t getArtistIndex(const std::string &artistName) const;

    std::string getCompositionArtistName(std::size_t row) const;

protected:

    void updateStep(const QDate &currIterationDate);

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

