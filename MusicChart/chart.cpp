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

void Chart::update(const QDate &currentDate)
{
    //normalizePopularity();
    setZeroPopularities();

    auto iterations = currentDate.toJulianDay();

    for (auto i=QDate(1950,1,1).toJulianDay(); i<iterations; i+=7)
    {
        auto currIterationDate = QDate::fromJulianDay(i);

        // update genres
         updateGenrePopularity(currentDate);

        // update artists
         updateArtistsPopularity(currIterationDate);

        // update compositions
        updateCompositionsPopularity(currIterationDate);

        //normalizePopularity();
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

void Chart::updateGenrePopularity(const QDate &currentDate){
    std::vector<double> genreCnt = createGenrePopularityVector();

    for (int i=Genres::Rock;i<=Genres::Chillout;i++)
    {
        GenrePopularity::at(Genres(i)) = 0.0;
    }

    for (auto &composition:compositions)
    {
        if (composition->getReleaseDate()<=currentDate && composition->getPopularity()>=1.0)
        {
            GenrePopularity::at(composition->getGenre()) += composition->getPopularity();
            genreCnt[composition->getGenre()]+=1.0;
        }
    }
    for (std::size_t i=Genres::Rock;i<=Genres::Chillout;i++)
    {
        if (std::abs(genreCnt[i])>0.001)
            GenrePopularity::at(Genres(i)) = GenrePopularity::at(Genres(i))/genreCnt[i];
        else {
            GenrePopularity::at(Genres(i)) = 0.0;
        }
    }
}

void Chart::updateArtistsPopularity(const QDate &currentDate)
{
    for (auto &artist:artists)
    {
        artist->updatePopularity(currentDate);
    }
}

void Chart::updateCompositionsPopularity(const QDate &currentDate)
{
    for (auto &composition:compositions)
    {
        if (composition->getReleaseDate()<=currentDate)
            composition->updatePopularity(currentDate);
    }
}

void Chart::normalizePopularity(){
    double minPopularityArtist = std::numeric_limits<double>::max();
    double maxPopularityArtist = std::numeric_limits<double>::min();

    double minPopularityComposition = std::numeric_limits<double>::max();
    double maxPopularityComposition = std::numeric_limits<double>::min();

    double minPopularityGenre = std::numeric_limits<double>::max();
    double maxPopularityGenre = std::numeric_limits<double>::min();

    /// search min max popularity
    for (auto &artist:artists)
    {
        if (artist->getPopularity()<minPopularityArtist)
            minPopularityArtist = artist->getPopularity();

        if (artist->getPopularity()>maxPopularityArtist)
            maxPopularityArtist = artist->getPopularity();
    }

    for (auto &composition:compositions)
    {
        if (composition->getPopularity()<minPopularityComposition)
            minPopularityComposition = composition->getPopularity();

        if (composition->getPopularity()>maxPopularityComposition)
            maxPopularityComposition = composition->getPopularity();
    }

    for (int i=0;i<=Genres::Chillout;i++)
    {
        double genrePop = GenrePopularity::at(Genres(i));
        if (genrePop<minPopularityGenre)
            minPopularityGenre = genrePop;

        if (genrePop>maxPopularityGenre)
            maxPopularityGenre = genrePop;
    }

    /// normalize
    for (auto &artist:artists)
        artist->normalize(minPopularityArtist,maxPopularityArtist);

    for (auto &composition:compositions)
        composition->normalize(minPopularityComposition,maxPopularityComposition);

    for (int i=0;i<=Genres::Chillout;i++)
    {
        GenrePopularity::at(Genres(i)) = linearNormalize(GenrePopularity::at(Genres(i)),minPopularityGenre,maxPopularityGenre);
    }

}

void Chart::setZeroPopularities()
{
    for (int i=0;i<=Genres::Chillout;i++)
    {
        GenrePopularity::at(Genres(i)) = 0.0;
    }

    for (auto &artist:artists)
    {
        artist->setZeroPopularity();
    }

    for (auto &composition:compositions)
    {
        composition->setZeroPopularity();
    }

}
