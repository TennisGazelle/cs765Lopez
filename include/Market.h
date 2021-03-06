//
// Created by Daniel Lopez on 11/10/17.
//

#ifndef MAIN_MARKET_H
#define MAIN_MARKET_H

class Portfolio;

#include "Stock.h"
#include "Portfolio.h"

class Market : public vector<Stock> {
public:
    void init();
    void print() const;
    vector<Portfolio> initPortfolios(unsigned int offset, vector<bool> actionIndexes);

    double compareStocks(unsigned int i, unsigned int j);

};


#endif //MAIN_MARKET_H
