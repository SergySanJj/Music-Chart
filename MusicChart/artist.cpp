#include "artist.h"

Artist::Artist(const std::string &_name, const std::vector<Genres> &_preferredGenres):
    ChartItem (_name), preferredGenres(_preferredGenres) {
}

void Artist::addComposition(std::shared_ptr<Composition> &composition)
{
    compositions.push_back(composition);
}

double Artist::avgCompositionsPopularity(QDate currentDate){
    double res = 0.0;
    int compCount = 0;

    double maxPop = -1000.0;

    for (auto &composition:compositions)
    {
        if (currentDate>=composition->getReleaseDate() && composition->getPopularity()>=1.0)
        {
            res+= composition->getPopularity();
            compCount++;

            if (maxPop < composition->getPopularity())
            {
                maxPop = composition->getPopularity();
                signatureComposition = composition;
            }
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

bool Artist::isPreferredGenre(Genres _genre) {
    for (auto &genre:preferredGenres)
        if (_genre == genre)
            return true;
    return false;
}

bool Artist::isSignature(const std::shared_ptr<Composition> &_composition)
{
    if (signatureComposition == nullptr)
        return true;

    if (signatureComposition == _composition)
        return true;
    else
        return false;
}

std::string Artist::getGenresString()
{
    std::string res;
    for (auto &genre:preferredGenres)
        res += getGenreString(genre) + " ";
    return res;
}

