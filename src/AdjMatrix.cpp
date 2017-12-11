//
// Created by Daniel Lopez on 12/6/17.
//

#include <iostream>
#include <cmath>
#include <teexgraph/Graph.h>
#include <Matrix.h>
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
        for (unsigned int j = i; j < m.size(); j++) {
            (*this)[i][j] = this->getAvgCorrelationBetween(i, j, m, pfs);
            (*this)[j][i] = (*this)[i][j];
        }
    }
}

double AdjMatrix::getAvgCorrelationBetween(int i, int j, Market &market, vector<Portfolio> &portfolios) {
    double sum = 0.0;
    for (auto& p : portfolios) {
        sum += p.getCorrelationBetween(&market[i], &market[j]);
        assert (!isnan(sum));
    }
    return (sum/double(portfolios.size()));
}

void AdjMatrix::fillPearsonCorrelation(Market &m) {
    marketStockNames.clear();
    for (unsigned int i = 0; i < m.size(); i++) {
        marketStockNames.push_back(m[i].symbol);
        for (unsigned int j = 0; j < m.size(); j++) {
            (*this)[i][j] = this->getPearsonCorrelationBetween(i, j, m);
        }
    }
}

double AdjMatrix::getPearsonCorrelationBetween(int i, int j, Market &market) {
    double r_i_avg, r_j_avg;
    vector<double> d_i, d_j;

    d_i = market[i].percentChanges;
    d_j = market[j].percentChanges;

    r_i_avg = Matrix::getValueDistribution(d_i).first;
    r_j_avg = Matrix::getValueDistribution(d_j).first;
    for (int index = 0; index < d_i.size(); index++) {
        d_i[index] -= r_i_avg;
        d_j[index] -= r_j_avg;
    }

    double numerator = 0.0;
    double denominator_left = 0.0, denominator_right = 0.0;
    for (int index = 0; index < d_i.size(); index++) {
        numerator += d_i[index]*d_j[index];
        denominator_left += pow(d_i[index], 2);
        denominator_right += pow(d_j[index], 2);
    }

    denominator_left = sqrt(denominator_left);
    denominator_right = sqrt(denominator_right);

    return numerator / (denominator_left * denominator_right);
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

void AdjMatrix::varyEdgeThreshold(PropertyMatrix& propertyMatrix, unsigned int offset) const {
    vector<double> values = getValues();

    sort(values.begin(), values.end());

    unsigned int count = 0;
    for (double t = 0.0; t < 1.01; t += 0.01) {
        while (count < values.size() && values[count] < t) {
            count ++;
        }

        // generate graph and get stats at this point
        Graph g;
        g.loadFromMatrixWithThreshold((*this), t, marketStockNames);

        Property property = propertyMatrix.at(t, offset);

        property.density = g.density(FULL);
        property.avgDegree = g.averageDegree(FULL);
//        property.avgDistance = g.averageDistance(FULL, 1.0);
        property.percentOfEdges = double(count)/double(values.size());
        property.clusteringCoefficient = g.averageClusteringCoefficient(FULL);

//        property.betweennessDistribution = Matrix::getValueDistribution(g.betweennessCentrality(FULL, 1.0));
        property.outdegreeDistribution = Matrix::getValueDistribution(g.outdegreeCentrality());
        property.pagerankDistribution = Matrix::getValueDistribution(g.pageRankCentrality());

        propertyMatrix.assignAt(t, offset, property);
    }
}

