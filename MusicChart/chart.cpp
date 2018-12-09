#include "chart.h"


Chart::Chart()
{

}

bool Chart::addArtist(const std::string &_name, const std::vector<Genres> &_preferedGenres)
{
    if (_name.empty())
        return false;

    if (checkArtistExistance(_name))
        return false;

    /// all artists must have some prefered genres in this system
    if (_preferedGenres.empty())
        return false;

    artists.push_back(std::make_shared<Artist>(_name, _preferedGenres));

    return true;
}

bool Chart::addComposition(const std::string &_artist, const std::string &_name, Genres _genre, QDate _releaseDate)
{
    if (_name.empty())
        return false;

    std::shared_ptr<Artist> addTo = nullptr;
    for (auto &artist:artists)
    {
        if (artist->getName()==_artist)
        {
            addTo = artist;
            break;
        }
    }

    if (!addTo)
        return false;

    if (addTo->compositionExists(_name))
        return false;

    std::shared_ptr<Composition> newComposition = std::make_shared<Composition>(addTo, _name, _genre, _releaseDate);

    compositions.push_back(newComposition);
    addTo->addComposition(newComposition);

    return true;
}

void Chart::update(QDate currentDate)
{
    normalizePopularity();

    auto iterations = currentDate.toJulianDay();
    for (auto i=QDate(1900,1,1).toJulianDay(); i<iterations; i+=7)
    {
        auto currIterationDate = QDate::fromJulianDay(i);

        // update genres
         updateGenrePopularity();

        // update compositions
        updateCompositionsPopularity(currIterationDate);

        // update artists
        updateArtistsPopularity(currIterationDate);

        normalizePopularity();
    }
}

bool Chart::checkArtistExistance(const std::string &_name) const
{
    for (auto &artist:artists)
    {
        if (artist->getName() == _name)
            return true;
    }
    return false;
}

void Chart::updateGenrePopularity(){
    genrePopularity = createGenrePopularityVector();
    std::vector<double> genreCnt = createGenrePopularityVector();
    for (auto &composition:compositions)
    {
        genrePopularity[composition->getGenre()]+=composition->getPopularity();
        genreCnt[composition->getGenre()]+=1;
    }
    for (std::size_t i=0;i<genreCnt.size();i++)
    {
        if (std::abs(genreCnt[i])>0.001)
            genrePopularity[i] = genrePopularity[i]/genreCnt[i];
        else {
            genrePopularity[i] = 0.0;
        }
    }
}

void Chart::updateArtistsPopularity(QDate currentDate)
{
    for (auto &artist:artists)
    {
        artist->updatePopularity(currentDate);
    }
}

void Chart::updateCompositionsPopularity(QDate currentDate)
{
    for (auto &composition:compositions)
    {
        composition->updatePopularity(currentDate);
    }
}

void Chart::normalizePopularity(){
    double minPopularity = std::numeric_limits<double>::max();
    double maxPopularity = std::numeric_limits<double>::min();

    /// search min max popularity
    for (auto &artist:artists)
    {
        if (artist->getPopularity()<minPopularity)
            minPopularity = artist->getPopularity();

        if (artist->getPopularity()>maxPopularity)
            maxPopularity = artist->getPopularity();
    }

    for (auto &composition:compositions)
    {
        if (composition->getPopularity()<minPopularity)
            minPopularity = composition->getPopularity();

        if (composition->getPopularity()>maxPopularity)
            maxPopularity = composition->getPopularity();
    }

    for (auto &genrePop:genrePopularity)
    {
        if (genrePop<minPopularity)
            minPopularity = genrePop;

        if (genrePop>maxPopularity)
            maxPopularity = genrePop;
    }

    /// normalize
    for (auto &artist:artists)
        artist->normalize(minPopularity,maxPopularity);

    for (auto &composition:compositions)
        composition->normalize(minPopularity,maxPopularity);

    for (auto &genrePop:genrePopularity)
        genrePop = linearNormalize(genrePop,minPopularity,maxPopularity);


}
