#include "artist.h"

Artist::Artist(const std::string &_name, const std::vector<Genres> &_preferedGenres):
    ChartItem (_name), preferedGenres(_preferedGenres) {
}

void Artist::addComposition(std::shared_ptr<Composition> &composition)
{
    compositions.push_back(composition);
}

double Artist::avgCompositionsPopularity(QDate currentDate){
    double res = 0.0;
    int compCount = 0;
    for (auto &composition:compositions)
    {
        if (currentDate>=composition->getReleaseDate() && composition->getPopularity()>=1.0)
        {
            res+= composition->getPopularity();
            compCount++;
        }
    }
    if (compCount>0)
        res = res/compCount;

    return res;
}

void Artist::updatePopularity(QDate currentDate)
{
    if (compositions.empty())
    {
        popularity =0.0;
        return;
    }

    double avgComp = avgCompositionsPopularity(currentDate);
    if (avgComp<0.001)
    {
        popularity = 0.0;
        return;
    }

    std::mt19937 mt(static_cast<std::size_t>(seed+currentDate.toJulianDay()));
    std::uniform_real_distribution<double> dist(-0.5, 0.5);

    popularity = avgComp + dist(mt);
}

bool Artist::compositionExists(const std::string &_composition)
{
    for (auto &composition:compositions)
    {
        if (composition->getName() == _composition)
            return true;
    }
    return false;
}

void Artist::setZeroPopularity() { popularity = 0.0; }

bool Artist::isPreferedGenre(Genres _genre) {
    for (auto &genre:preferedGenres)
        if (_genre == genre)
            return true;
    return false;
}

std::string Artist::getGenresString()
{
    std::string res;
    for (auto &genre:preferedGenres)
        res += getGenreString(genre) + " ";
    return res;
}

