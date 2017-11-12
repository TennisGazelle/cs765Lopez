//
// Created by Daniel Lopez on 11/10/17.
//

#ifndef MAIN_MARKET_H
#define MAIN_MARKET_H


#include "Stock.h"

class Market : public vector<Stock> {
public:
    void print() const;
};


#endif //MAIN_MARKET_H
