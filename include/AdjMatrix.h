//
// Created by Daniel Lopez on 12/6/17.
//

#ifndef STOCKCOMPLEXNETWORKS_ADJMATRIX_H
#define STOCKCOMPLEXNETWORKS_ADJMATRIX_H

#include <vector>
#include "Portfolio.h"
#include "PropertyMatrix.h"
#include "Matrix.h"

using namespace std;

class AdjMatrix : public Matrix {
public:
    AdjMatrix(unsigned int size);

    void fillCorrelationMatrix(Market &m, vector<Portfolio>& pfs);
    double getAvgCorrelationBetween(int i, int j, Market& market, vector<Portfolio>& portfolios);

    void fillPearsonCorrelation(Market &m);
    double getPearsonCorrelationBetween(int i, int j, Market& market);

    void makeGraph(Market &m);

    void varyEdgeThreshold(PropertyMatrix& propertyMatrix, unsigned int offset) const;


    vector<string> marketStockNames;
};


#endif //STOCKCOMPLEXNETWORKS_ADJMATRIX_H
