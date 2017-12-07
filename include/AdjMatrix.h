//
// Created by Daniel Lopez on 12/6/17.
//

#ifndef STOCKCOMPLEXNETWORKS_ADJMATRIX_H
#define STOCKCOMPLEXNETWORKS_ADJMATRIX_H

#include <vector>
#include "Portfolio.h"

using namespace std;

class AdjMatrix : public vector< vector<double> > {
public:
    AdjMatrix(unsigned int size);

    void fillCorrelationMatrix(Market &m, vector<Portfolio>& pfs);
    double getAvgCorrelationBetween(int i, int j, Market& market, vector<Portfolio>& portfolios);
    void makeGraph(Market &m);

    vector<double> getValues() const;
    vector<double> varyThreshold() const;
    pair<double, double> getEdgeWeightDistribution() const;


    vector<string> marketStockNames;
};


#endif //STOCKCOMPLEXNETWORKS_ADJMATRIX_H
