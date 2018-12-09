#pragma once

#include <vector>
#include <string>
#include <limits>
#include <cmath>

/// Rock stays first, Chillout - last
enum Genres{ Rock=0, Pop, HipHop, House, Alternative, Chillout };

std::string getGenreString(Genres genre);

std::vector<double> createGenrePopularityVector();

double linearNormalize(double x, double a, double b);
