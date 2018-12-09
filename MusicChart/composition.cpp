#include "composition.h"

Composition::Composition(std::shared_ptr<Artist> _artist, const std::string &_name, Genres _genre, QDate _releaseDate):
    ChartItem (_name), artist(_artist), genre(_genre), releaseDate(_releaseDate) {

}

void Composition::updatePopularity(QDate currentDate)
{

}

double Composition::getPopularity() const { return popularity; }

std::string Composition::getName() const { return name; }

std::string Composition::getArtistName() const { return artist->getName(); }

QDate Composition::getReleaseDate() const { return releaseDate; }
