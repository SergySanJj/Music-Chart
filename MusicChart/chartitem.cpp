#include "chartitem.h"



ChartItem::ChartItem(std::string _name, double _popularity): name(std::move(_name)), popularity(_popularity)
{
    seed = generateSeed(name);
}

int ChartItem::generateSeed(const std::string &s) const{
    int res=0;
    int cnt=1;
    for (auto c:s)
    {
        res += c*cnt;
        cnt*=10;
    }
    return res;
}
