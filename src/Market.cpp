//
// Created by Daniel Lopez on 11/10/17.
//

#include <iostream>
#include "Market.h"

void Market::print() const {
    cout << "Market:" << endl;
    for (unsigned int i = 0; i < size(); i++) {
        at(i).print();
    }
}