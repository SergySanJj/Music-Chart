#include "artist.h"


Artist::Artist(const std::string &_name, const std::vector<Genres> &_preferedGenres):
    ChartItem (_name), preferedGenres(_preferedGenres) {
    seed = generateSeed(_name);
}

void Artist::addComposition(std::shared_ptr<Composition> composition)
{
    compositions.push_back(composition);
}

std::string Artist::getName() const { return name; }

int Artist::getSeed() const { return seed; }

double Artist::getPopularity() const { return popularity; }

double Artist::avgCompositionsPopularity(){
    double res = 0.0;
    int compCount = 0;
    for (auto composition:compositions)
    {
        res+= composition->getPopularity();
        compCount++;
    }
    res = res/compCount;

    return res;
}

void Artist::updatePopularity(QDate currentDate)
{

}

bool Artist::compositionExists(const std::string &_composition)
{
    for (auto composition:compositions)
    {
        if (composition->getName() == _composition)
            return true;
    }
    return false;
}

