#include "composition.h"

Composition::Composition(std::shared_ptr<Artist> _artist, const std::string &_name, Genres _genre, QDateTime _releaseDate):
    ChartItem (_name), artist(_artist), genre(_genre), releaseDate(_releaseDate) {

}

void Composition::updatePopularity(QDateTime currentDate)
{

}

double Composition::getPopularity() const { return popularity; }
