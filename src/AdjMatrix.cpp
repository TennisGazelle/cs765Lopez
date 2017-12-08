//
// Created by Daniel Lopez on 12/6/17.
//

#include <iostream>
#include <cmath>
#include <teexgraph/Graph.h>
#include "AdjMatrix.h"

AdjMatrix::AdjMatrix(unsigned int size) {
    resize(size);
    for (auto& r : (*this)) {
        r.resize(size);
    }
}

void AdjMatrix::fillCorrelationMatrix(Market &m, vector<Portfolio> &pfs) {
    marketStockNames.clear();
    for (unsigned int i = 0; i < m.size(); i++) {
        marketStockNames.push_back(m[i].symbol);
        for (unsigned int j = 0; j < m.size(); j++) {
            (*this)[i][j] = this->getAvgCorrelationBetween(i, j, m, pfs);
        }
    }

}

double AdjMatrix::getAvgCorrelationBetween(int i, int j, Market &market, vector<Portfolio> &portfolios) {
    double sum = 0.0;
    for (auto& p : portfolios) {
        sum += p.getCorrelationBetween(&market[i], &market[j]);
        if (isnan(sum)) {
            cout << endl;
            cout << i << "," << j << ": " << p.getFocus()->symbol << " ";
            p.print();
        }
    }
    return (sum/double(portfolios.size()));
}

void AdjMatrix::makeGraph(Market &m) {
    double threshold = 0.0;
    Graph g;

    g.loadFromMatrixWithThreshold((*this), threshold, marketStockNames);

    vector<double> centralities = g.pageRankCentrality();

    if (centralities.size() == 0) {
        cout << "There were no centralities for a threshold of " << threshold << endl;
    } else {
        for (unsigned int i = 0; i < marketStockNames.size(); i++) {
            cout << marketStockNames[i] << ": " << centralities[i] << endl;
        }
    }


}

vector<double> AdjMatrix::getValues() const {
    vector<double> values(size()*size());
    for (const auto& row : (*this)) {
        for (const auto& col : row) {
            values.push_back(abs(col));
        }
    }
    return values;
}

void AdjMatrix::varyThreshold(PropertyMatrix& propertyMatrix) const {
    vector<double> values = getValues();

    sort(values.begin(), values.end());

    vector<double> percentageValuesLowerThan;
    unsigned int count = 0;
    for (double t = -1.0; t < 1.01; t += 0.01) {
        while (count < values.size() && values[count] < t) {
            count ++;
        }

//        percentageValuesLowerThan.push_back(double(count)/double(values.size()));
        propertyMatrix.at(t, 0).percentOfEdges = double(count)/double(values.size());
    }

//    return percentageValuesLowerThan;
}

pair<double, double> AdjMatrix::getEdgeWeightDistribution() const {
    double sum = 0.0, average = 0.0, variance = 0.0;
    vector<double> values = getValues();

    for (auto& v : values) {
        sum += v;
    }
    average = sum/values.size();

    sum = 0;
    for (auto& v : values) {
        sum += pow(average - v ,2);
    }
    variance = sum/(values.size()-1);

    return {average, variance};
}