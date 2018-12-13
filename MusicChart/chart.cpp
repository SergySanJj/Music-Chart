#include "chart.h"


Chart::Chart()
{

}

bool Chart::addArtist(const std::string &_name, const std::vector<Genres> &_preferredGenres)
{
    if (_name.empty())
        return false;

    if (checkArtistExistance(_name))
        return false;

    /// all artists must have some preferred genres in this system
    if (_preferredGenres.empty())
        return false;

    artists.push_back(std::make_shared<Artist>(_name, _preferredGenres));

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
    setZeroPopularities();

    QDate dateIter = QDate(1970,1,5);


    while (dateIter<=currentDate)
    {
        updateStep(dateIter);

        dateIter = dateIter.addMonths(1);
    }
}

std::pair<QVector<double>, QVector<double> > Chart::getCompositionHistory(const QDate &currentDate, std::size_t row){
    long long begin = compositions[row]->getReleaseDate().toJulianDay();
    long long end = currentDate.toJulianDay();

    if (end<begin)
        return std::make_pair(QVector<double>(),QVector<double>());

    QVector<double> x(static_cast<int>(end-begin+1));
    QVector<double> y(static_cast<int>(end-begin+1));

    setZeroPopularities();

    QDate dateIter = QDate(1970,1,5);

    int cnt = 0;

    QDate release = compositions[row]->getReleaseDate();

    while (dateIter<=currentDate)
    {
        updateStep(dateIter);

        if (dateIter>=release)
        {
            x[cnt] = cnt;
            y[cnt] = compositions[row]->getPopularity();
            cnt++;
        }
        dateIter = dateIter.addMonths(1);
    }

    return std::make_pair(x,y);
}

void Chart::updateStep(const QDate &currIterationDate)
{
    //auto currIterationDate = QDate::fromJulianDay(i);

    // update genres
     updateGenrePopularity(currIterationDate);

    // update artists
     updateArtistsPopularity(currIterationDate);

    // update compositions
    updateCompositionsPopularity(currIterationDate);

    //normalizePopularity();
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

std::string Chart::getCompositionString(std::size_t row) const {
    return compositions[row]->getArtistName() + " - " + compositions[row]->getName();
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

double Chart::getCompositionPopularity(std::size_t row) const
{
    return compositions[row]->getPopularity();
}

QDate Chart::getCompositionReleaseDate(std::size_t row) const
{
    return  compositions[row]->getReleaseDate();
}


