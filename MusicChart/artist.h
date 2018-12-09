#pragma once

#include "composition.h"
#include "genres.h"

#include <vector>
#include <memory>

class Composition;

class Artist
{
public:
    /// no empty constructor
    //Artist();
    ~Artist()=default;

    Artist(std::string _name, std::vector<Genres> _preferedGenres, double _popularity);

    void addComposition(std::shared_ptr<Composition> composition);

private:
    std::string name;
    std::vector<Genres> preferedGenres;
    double popularity;
    std::vector<std::shared_ptr<Composition> > compositions;
};
