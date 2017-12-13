//
// Created by Daniel Lopez on 11/10/17.
//

#include <iostream>
#include <cmath>
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
//        cout << "buying " << numStocksToOwn << " of " << market[i].symbol << " at price " << market[i].data[timeToBuy] << endl;
        float equity = numStocksToOwn * market[i].data[timeToBuy];
        money -= equity;
        assets[&market[i]].first = numStocksToOwn;
        assets[&market[i]].second -= equity;
    }
}

void Portfolio::sellAll(Market &market, unsigned int timestep) {
    unsigned int timeToSell = timestep;
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
        float numStocksOwned = assets[&market[i]].first;
        float profit = numStocksOwned * market[i].data[timeToSell];
        money += profit;
//        cout << "selling " << numStocksOwned << " of " << market[i].symbol << " at price " << market[i].data[timeToSell] << endl;
        assets[&market[i]].first = 0;
        assets[&market[i]].second += profit;
    }
}

void Portfolio::sellAllNow(Market &market, unsigned int timestep) {
    // for everything that I have
    for (unsigned int i = 0; i < market.size(); i++) {
        float numStocksOwned = assets[&market[i]].first;
        float profit = numStocksOwned * market[i].data[timestep];
        assets[&market[i]].first = 0;
        assets[&market[i]].second += profit;
        money += profit;
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
//    if (nextAction == SELL)
//        doAction(market, timestep);
    sellAllNow(market, timestep);
}

void Portfolio::print() const {
    cout << "Portfolio [" << money << "," << offset << "]: " << endl;
//    for (auto instance : assets) {
//        cout << "--" << instance.first->symbol << " : number owned " << instance.second.first << ", profit made " << instance.second.second << endl;
//    }
}

double Portfolio::getCorrelationBetween(Stock *left, Stock *right) {
    // have we ever seen these before?
    if (assets.find(left) == assets.end() || assets.find(right) == assets.end()) {
        // no correlation
        return 0.0;
    }

    // avoid self loops and div/0 errors
    if (assets[left].second == assets[right].second) {
        return 1.0; 
    }

    // if abs(left) > abs(right), swap them
    if (abs(assets[left].second) > abs(assets[right].second)) {
        swap(left, right);
    }

    if (assets[right].second == 0.0) {
        return 1.0;
    }

    // start making the thing
    double logReturnLeft = (assets[left].second);
    double logReturnRight = (assets[right].second);
    // DEBUGGING REASONS
    return logReturnLeft/logReturnRight;

    double e_ij = 2*(logReturnLeft + logReturnRight)/(abs(logReturnLeft) + abs(logReturnRight));
    return e_ij-1;
}

double Portfolio::getMoney() const {
    return money;
}

Stock* Portfolio::getFocus() const {
    return focus;
}