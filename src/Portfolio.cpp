//
// Created by Daniel Lopez on 11/10/17.
//

#include <iostream>
#include "Portfolio.h"

Portfolio::Portfolio() : money(1000), focus(nullptr), offset(0) {
    nextAction = BUY;
}

Portfolio::Portfolio(Stock *pFocus, int pOffset) : money(1000), focus(pFocus), offset(pOffset) {
    nextAction = BUY;
}

void Portfolio::buyAll(Market &market, unsigned int timestep) {
    // assure that we are not buying at the last timestep
    if (timestep == market[0].data.size()-1)
        return;

    unsigned int timeToBuy;
    // buying $100 for everyone
    for (unsigned int i = 0; i < market.size(); i++) {
        timeToBuy = timestep;
        if (focus != nullptr && focus->symbol != market[i].symbol) {
            timeToBuy += offset;
        }

        // how much is $100 of this stock?
        if (timeToBuy > market[i].data.size()) {
            continue;
        }

        float numStocksToOwn = 100.0f / market[i].data[timeToBuy];
//        cout << "buying " << numStocksToOwn << " of " << market[i].symbol << endl;
        money -= numStocksToOwn * market[i].data[timeToBuy];
        assets[&market[i]] = numStocksToOwn;
    }
}

void Portfolio::sellAll(Market &market, unsigned int timestep) {
    unsigned int timeToSell;
    // for each item in the list
    for (unsigned int i = 0; i < market.size(); i++) {
        timeToSell = timestep;
        if (focus != nullptr && focus->symbol != market[i].symbol) {
            timeToSell += offset;
        }
        if (timeToSell > market[i].data.size()) {
            timeToSell = (unsigned int) market[i].data.size()-1;
        }
        // sell anything that I have for that price
        float numStocksOwned = assets[&market[i]];
        money += numStocksOwned * market[i].data[timeToSell];
//        cout << "selling " << numStocksOwned << " of " << market[i].symbol << " at price " << market[i].data[timeToSell] << endl;
        assets[&market[i]] = 0;
    }
}

void Portfolio::doAction(Market &market, unsigned int timestep) {
    if (nextAction == BUY) {
        buyAll(market, timestep);
        nextAction = SELL;
    } else {
        sellAll(market, timestep);
        nextAction = BUY;
    }
}

void Portfolio::finalizeActions(Market &market, unsigned int timestep) {
    if (nextAction == SELL)
        doAction(market, timestep);
}

void Portfolio::print() const {
    cout << "Portfolio [" << money << "," << offset << "]: " << endl;
    for (auto instance : assets) {
        cout << "--" << instance.first->symbol << " : " << instance.second << endl;
    }
}
