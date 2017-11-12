//
// Created by Daniel Lopez on 11/10/17.
//

#include <iostream>
#include "Portfolio.h"

Portfolio::Portfolio() : money(1000), focus(nullptr), offset(0) {

}

Portfolio::Portfolio(Stock *pFocus, int pOffset) : money(1000), focus(pFocus), offset(pOffset) {

}

void Portfolio::buyAll(Market &market, unsigned int timestep) {
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
        cout << "buying " << numStocksToOwn << " of " << market[i].symbol << endl;
        money -= numStocksToOwn;
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
        cout << "selling at timestep: " << timeToSell << endl;
        cout << "market[i].data.size is " << market[i].data.size() << endl;
        if (timeToSell > market[i].data.size()) {
            continue;
        }
        // sell anything that I have for that price
        float numStocksOwned = assets[&market[i]];
        money += numStocksOwned * market[i].data[timeToSell];
        cout << "selling " << numStocksOwned << " of " << market[i].symbol << " at price " << market[i].data[timeToSell] << endl << endl;
        assets[&market[i]] = 0;
    }
}

void Portfolio::print() const {
    cout << "Portfolio [" << money << "," << offset << "]: " << endl;
    for (auto instance : assets) {
        cout << "--" << instance.first->symbol << " : " << instance.second << endl;
    }
}

