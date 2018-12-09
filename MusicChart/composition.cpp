#include "composition.h"

Composition::Composition(std::shared_ptr<Artist> _artist, std::string _name, Genres _genre, QDateTime _releaseDate, double _popularity):
    artist(_artist), name(std::move(_name)), genre(_genre), releaseDate(_releaseDate), popularity(_popularity){}
