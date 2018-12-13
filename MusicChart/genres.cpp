#include "genres.h"

std::string getGenreString(Genres genre){
    switch (genre) {
    case Genres::Rock:
        return "Rock";
    case Genres::Pop:
        return "Pop";
    case Genres::HipHop:
        return "HipHop";
    case Genres::House:
        return "House";
    case Genres::Alternative:
        return "Alternative";
    case Genres::Chillout:
        return "Chillout";
    //default:
    //    return "Unknown";
    }
    return "Unknown";
}

std::vector<double> createGenrePopularityVector()
{
    std::vector<double> res(Genres::Chillout+1,0.0);
    return res;
}

double linearNormalize(double x, double a, double b)
{
    double res;
    if (std::abs(b-a) <= std::numeric_limits<double>::epsilon())
        res = x;
    else
        res = 9.0*(x-a)/(b-a)+1.0;

    if (res<= 0.01)
        res = 0.0;
    return res;
}

std::vector<double> GenrePopularity::popularity = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
