//
// Created by Daniel Lopez on 11/7/17.
//

#include <iostream>
#include <fstream>
#include <assert.h>
#include "Stock.h"

Stock::Stock(const string &incomingSymbol) : symbol(incomingSymbol) {
    getValuesFromFile();
    calcPChanges();
}

void Stock::print() const {
    cout << symbol << ": ";
    for (float d : data) {
        cout << d << ", ";
    }
    cout << endl;
}

void Stock::getValuesFromFile() {
    if (symbol.empty()) {
        data.push_back(-1);
        throw logic_error("Symbol name is empty");
    }

    const static int MAX_SIZE = 180;

    data.clear();
    data.reserve(MAX_SIZE);
    // given your stock symbol
    string filename = "../in/" + symbol + ".log";
    ifstream fin;
    fin.clear();
    fin.open(filename.c_str());
    while(fin.good()) {
        float temp;
        fin >> temp;
        data.push_back(temp);
        if (data.size() > MAX_SIZE)
            break;
    }
    data.erase(data.end()-1);
    fin.close();
}

void Stock::calcPChanges() {
    percentChanges.clear();
    for (unsigned int i = 1; i < data.size(); i++) {
        percentChanges.push_back(data[i] / data[i - 1] * 1000);
    }
}