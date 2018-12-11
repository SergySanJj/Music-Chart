#pragma once

#include "genres.h"

#include <string>
#include <random>

#include <QDate>

class ChartItem
{
public:
    virtual std::string getName() const { return name; }

    virtual double getPopularity() const { return popularity; }

    virtual int getSeed() const { return seed; }

    virtual void normalize(double a, double b);
protected:
    /// no empty constructor
    //ChartItem();

    /// Creation is available only for derived classes
    ChartItem(std::string _name, double _popularity=1.0);

    virtual ~ChartItem()=default;

    virtual void updatePopularity(QDate currentDate)=0;

    std::string name;
    double popularity;
    int seed;

   static const int regressAfter = 365;

private:
   int generateSeed(const std::string &s) const;
};


