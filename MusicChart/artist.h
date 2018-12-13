#pragma once

#include "chartitem.h"
#include "composition.h"
#include "genres.h"

#include <vector>
#include <memory>
#include <random>

#include <QDate>

class Composition;

class Artist : public ChartItem
{
public:
    /// no empty constructor
    //Artist();

    ~Artist()=default;

    Artist(const std::string &_name, const std::vector<Genres> &_preferredGenres);

    void addComposition(std::shared_ptr<Composition> &composition);

    double avgCompositionsPopularity(QDate currentDate);

    void updatePopularity(QDate currentDate);

    bool compositionExists(const std::string &_composition);

    void setZeroPopularity();

    bool isPreferredGenre(Genres _genre);

    bool isSignature(const std::shared_ptr<Composition> &_composition);

    std::string getGenresString();

private:
    std::vector<Genres> preferredGenres;

    std::vector<std::shared_ptr<Composition> > compositions;

    /// Composition with max popularity
    std::shared_ptr<Composition> signatureComposition;
};
