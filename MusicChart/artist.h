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

    Artist(const std::string &_name, const std::vector<Genres> &_preferedGenres);

    void addComposition(std::shared_ptr<Composition> &composition);

    double avgCompositionsPopularity(QDate currentDate);

    void updatePopularity(QDate currentDate);

    bool compositionExists(const std::string &_composition);

    void setZeroPopularity();

    bool isPreferedGenre(Genres _genre);

private:
    std::vector<Genres> preferedGenres;

    std::vector<std::shared_ptr<Composition> > compositions;
};
