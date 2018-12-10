#include "genres.h"

//std::vector<std::string> Genres::genres = {"Rock","Pop","Hip-Hop","House","Alternative","Chillout"};


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
    }
}

std::vector<double> createGenrePopularityVector()
{
    std::vector<double> res(Genres::Chillout+1,0.0);
    return res;
}

double linearNormalize(double x, double a, double b)
{
    if (std::abs(b-a) <= std::numeric_limits<double>::epsilon())
        return x;
    return 10.0*(x-a)/(b-a);
}

std::vector<double> GenrePopularity::popularity = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
