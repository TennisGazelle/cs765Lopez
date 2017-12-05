//
// Created by Daniel Lopez on 11/10/17.
//

#include <iostream>
#include "Market.h"

void Market::init(const vector<string>& names) {
    for (const auto& sn : names) {
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