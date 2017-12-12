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

enum PearsonKernel {
    SQUARE_V_SQUARE_ROOT,
    LOG_V_EXP,
    SINE_V_ARCSINE,
};

class AdjMatrix : public Matrix {
public:
    AdjMatrix(unsigned int size);

    void fillCorrelationMatrix(Market &m, vector<Portfolio>& pfs);
    double getAvgCorrelationBetween(int i, int j, Market& market, vector<Portfolio>& portfolios);

    void fillPearsonCorrelation(Market &m, PearsonKernel pk = SQUARE_V_SQUARE_ROOT);

    double getPearsonCorrelationBetween(int i, int j, Market &market, PearsonKernel pk);

    void makeGraph(Market &m);

    void varyEdgeThreshold(PropertyMatrix& propertyMatrix, unsigned int offset) const;

    vector<pair<unsigned int, unsigned int> > top10EdgeWeights() const;

    vector<string> marketStockNames;
};


#endif //STOCKCOMPLEXNETWORKS_ADJMATRIX_H
