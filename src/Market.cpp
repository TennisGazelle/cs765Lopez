//
// Created by Daniel Lopez on 11/10/17.
//

#include <iostream>
#include <cmath>
#include <config.h>
#include "Market.h"

void Market::init() {
    for (const auto& sn : STOCK_NAMES) {
        emplace_back(Stock(sn));
    }
}

void Market::print() const {
    cout << "Market:" << endl;
    for (unsigned int i = 0; i < size(); i++) {
        at(i).print();
    }
    cout << endl;
}

vector<Portfolio> Market::initPortfolios(unsigned int offset, vector<bool> actionIndexes) {
    vector<Portfolio> portfolios;
    // put in a focus for each one
    for (unsigned int i = 0; i < size(); i++) {
        portfolios.emplace_back(Portfolio(&at(i), offset));

        // for each data point
        for (unsigned int data_index = 0; data_index < at(0).data.size(); data_index++) {
            if (actionIndexes[data_index]) {
                portfolios[i].doAction((*this), data_index);
                if (i == actionIndexes.size()-1) {
                    portfolios[i].finalizeActions((*this), data_index);
                }
                if (isnan(portfolios[i].getMoney())) {
                    cout << "Portfolio [" << i << "," << at(i).symbol << "] became nan with action at timestep: " << data_index << endl;
                }
            }
        }
    }

    return portfolios;
}