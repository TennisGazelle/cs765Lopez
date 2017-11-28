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
    void sellAllNow(Market& market, unsigned int timestep);
    void doAction(Market& market, unsigned int timestep);
    void finalizeActions(Market& market, unsigned int timestep);
    double getMoney() const;
    Stock* getFocus() const;

    double getCorrelationBetween(Stock* left, Stock* right);

    void print() const;

private:
    map<Stock*, pair<float, float>> assets;
    double money;
    Stock* focus;
    int offset;
    enum {BUY, SELL} nextAction;
};


#endif //MAIN_PORTFOLIO_H
