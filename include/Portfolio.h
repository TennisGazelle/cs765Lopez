//
// Created by Daniel Lopez on 11/10/17.
//

#ifndef MAIN_PORTFOLIO_H
#define MAIN_PORTFOLIO_H

#include <map>

#include "Stock.h"
#include "Market.h"

using namespace std;

class Portfolio {
public:
    Portfolio();
    Portfolio(Stock* pFocus, int pOffset);
    void buyAll(Market& market, unsigned int timestep);
    void sellAll(Market& market, unsigned int timestep);
    void print() const;
    map<Stock*, float> assets;
    float money;
    Stock* focus;
    int offset;
};


#endif //MAIN_PORTFOLIO_H
