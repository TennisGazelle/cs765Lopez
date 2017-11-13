//
// Created by Daniel Lopez on 11/7/17.
//

#include <iostream>
#include <fstream>
#include "Stock.h"

void Stock::print() const {
    cout << symbol << ": ";
    for (float d : data) {
        cout << d << ", ";
    }
    cout << endl;
}

void Stock::getValuesFromFile() {
    data.clear();
    data.reserve(100);
    // given your stock symbol
    string filename = "../in/" + symbol + ".log";
    ifstream fin;
    fin.clear();
    fin.open(filename.c_str());
    while(fin.good()) {
        float temp;
        fin >> temp;
        data.push_back(temp);
    }
    data.erase(data.end()-1);
    fin.close();
}