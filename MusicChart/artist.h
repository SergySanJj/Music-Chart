#pragma once

#include "composition.h"
#include "genres.h"

#include <vector>
#include <memory>

class Composition;

class Artist
{
public:
    Artist();
private:
    std::string name;
    std::vector<Genres> preferedGenres;
    std::vector<std::shared_ptr<Composition> > compositions;
};
