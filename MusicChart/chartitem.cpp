#include "chartitem.h"

#include <iostream>


ChartItem::ChartItem(std::string _name, double _popularity): name(std::move(_name)), popularity(_popularity)
{
    seed = generateSeed(name);
}

void ChartItem::normalize(double a, double b)
{
    popularity = linearNormalize(popularity,a,b);
}

int ChartItem::generateSeed(const std::string &s) const{
    int res=0;
    int cnt=1;
    for (auto c:s)
    {
        res += c*cnt;
        cnt*=10;
        cnt = cnt % 100000;
    }
    //std::cout << s << " " << res << "\n";

    return res;
}
