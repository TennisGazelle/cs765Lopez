//
// Created by Daniel Lopez on 11/7/17.
//

#include <iostream>
#include "Stock.h"

void Stock::print() const {
    cout << symbol << ": ";
    for (float d : data) {
        cout << d << ", ";
    }
    cout << endl;
}