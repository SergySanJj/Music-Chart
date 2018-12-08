#pragma once

#include "artist.h"
#include "composition.h"

#include <vector>
#include <memory>

class Chart
{
public:
    Chart();

private:
    std::vector<std::shared_ptr<Artist> > artists;
    std::vector<std::shared_ptr<Composition> > compositions;
};

