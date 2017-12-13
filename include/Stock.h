//
// Created by Daniel Lopez on 11/7/17.
//

#ifndef MAIN_STOCK_H
#define MAIN_STOCK_H

#include <string>
#include <vector>

using namespace std;

class Stock {
public:
    Stock(const string& incomingSymbol);
    string symbol;
    vector<float> data;
    vector<double> percentChanges;
    void print() const;
    void getValuesFromFile();
    void calcPChanges();
};


#endif //MAIN_STOCK_H
