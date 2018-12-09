#include "composition.h"

Composition::Composition(std::shared_ptr<Artist> &_artist, const std::string &_name, Genres _genre, QDate _releaseDate):
    ChartItem (_name), artist(_artist), genre(_genre), releaseDate(_releaseDate) {

}

void Composition::updatePopularity(QDate currentDate)
{
    if (currentDate<releaseDate)
    {
        popularity = 0.0;
        return;
    }
    auto delta = currentDate.toJulianDay() - releaseDate.toJulianDay();

    std::mt19937 mt(static_cast<std::size_t>(seed+delta));

    double start;
    double end;
    if (delta <= ChartItem::regressAfter)
    {
        start = -1.0;
        end = 1.0;
    }
    else {
       start = 0.0;
       end = 2.0;
    }
    std::uniform_real_distribution<double> dist(start, end);

    popularity += dist(mt);
}

double Composition::getPopularity() const { return popularity; }

std::string Composition::getName() const { return name; }

std::string Composition::getArtistName() const { return artist->getName(); }

QDate Composition::getReleaseDate() const { return releaseDate; }

Genres Composition::getGenre() const { return genre; }

void Composition::normalize(double a, double b){
    ChartItem::normalize(a,b);
}
