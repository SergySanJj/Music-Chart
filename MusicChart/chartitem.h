#pragma once

#include "genres.h"

#include <string>
#include <random>

#include <QDate>

class ChartItem
{
public:
protected:
    /// no empty constructor
    //ChartItem();

    /// Creation is available only for derived classes
    ChartItem(std::string _name, double _popularity=1.0);

    virtual ~ChartItem()=default;


    std::string getName() const { return name; }

    double getPopularity() const { return popularity; }

    int getSeed() const { return seed; }

    void normalize(double a, double b);

    virtual void updatePopularity(QDate currentDate)=0;

    std::string name;
    double popularity;
    int seed;

   static const int regressAfter = 365;

private:
   int generateSeed(const std::string &s) const;
};


