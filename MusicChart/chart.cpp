#include "chart.h"


Chart::Chart()
{

}

bool Chart::addArtist(const std::string &_name, const std::vector<Genres> &_preferedGenres)
{
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

    std::shared_ptr<Artist> addTo = nullptr;
    for (auto artist:artists)
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

bool Chart::checkArtistExistance(const std::string &_name) const
{
    for (auto artist:artists)
    {
        if (artist->getName() == _name)
            return true;
    }
    return false;
}
