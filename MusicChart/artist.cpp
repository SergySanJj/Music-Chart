#include "artist.h"


Artist::Artist(std::string _name, std::vector<Genres> _preferedGenres, double _popularity):
    name(std::move(_name)), preferedGenres(std::move(_preferedGenres)), popularity(_popularity) {}
