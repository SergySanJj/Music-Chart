#pragma once

#include <string>
#include <QDateTime>

class ChartItem
{
public:
    /// no empty constructor
    //ChartItem();

    virtual ~ChartItem()=default;

    ChartItem(std::string _name, double _popularity=1.0);

protected:
    std::string getName() const { return name; }

    double getPopularity() const { return popularity; }

    int getSeed() const { return seed; }

    virtual void updatePopularity(QDateTime currentDate)=0;

    std::string name;
    double popularity;
    int seed;

   int generateSeed(const std::string &s) const;
};


