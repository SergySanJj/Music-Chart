#include "composition.h"

Composition::Composition(std::shared_ptr<Artist> &_artist, const std::string &_name, Genres _genre, QDate _releaseDate)
    : ChartItem (_name), artist(_artist), genre(_genre), releaseDate(_releaseDate)
{

    std::mt19937 mt(static_cast<std::size_t>(seed));

    std::uniform_real_distribution<double> coef(1.0, 5.0);

    stognationAfter = static_cast<int>(ChartItem::regressAfter*coef(mt));
}

void Composition::updatePopularity(QDate currentDate)
{
    if (currentDate < releaseDate)
    {
        popularity = 0.0;
        return;
    }

    /*
    if (popularity<=0.05)
    {
        popularity = artist->getPopularity()/2.0 + 0.06;
        return;
    }*/

    auto delta = currentDate.toJulianDay() - releaseDate.toJulianDay();

    std::mt19937 mt(static_cast<std::size_t>(seed+delta));

    double start;
    double end;    

    if (delta >= stognationAfter)
    {
        start = -1.0;
        end = 1.0;
    }
    else {
       start = 0.0;
       end = 2.0;
    }

    double randCoef;

    if (artist->isPreferredGenre(genre))
        randCoef = 2.0;
    else
        randCoef = 1.0;

    std::uniform_real_distribution<double> dist(start, end);

    std::uniform_real_distribution<double> genreStrenght(0.05, 0.25);
    std::uniform_real_distribution<double> artistStrenght(0.10, 0.30);

    double k1 = genreStrenght(mt);
    double k2 = artistStrenght(mt);
    double k3 = 1.0 - k1 - k2;

    std::shared_ptr<Composition> thisPtr = std::make_shared<Composition>(*this);

    if (artist->isSignature(thisPtr))
    {
        k1 = 0.05;
        k2 = 0.10;
        k3 = 0.85;
    }

    double genreAvg = GenrePopularity::at(this->genre)*k1;

    double artistAvg = this->artist->avgCompositionsPopularity(currentDate)*k2;

    double compPrediction = popularity*k3;

    popularity = compPrediction + genreAvg + artistAvg + dist(mt)*randCoef;

    normalizeNegative();
}

std::string Composition::getArtistName() const { return artist->getName(); }

QDate Composition::getReleaseDate() const { return releaseDate; }

Genres Composition::getGenre() const { return genre; }

void Composition::setZeroPopularity() { popularity = 0.0; }

std::string Composition::getGenresString() const
{
    return getGenreString(genre);
}

void Composition::normalizeNegative(){
    if (popularity<0.0)
        popularity=0.0;
}
