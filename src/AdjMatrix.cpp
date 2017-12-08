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

pair<double, double> getValueDistribution(vector<double>& values)  {
    double sum = 0.0, average = 0.0, variance = 0.0;

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

    r_i_avg = getValueDistribution(d_i).first;
    r_j_avg = getValueDistribution(d_j).first;
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

vector<double> AdjMatrix::getValues() const {
    vector<double> values(size()*size());
    for (const auto& row : (*this)) {
        for (const auto& col : row) {
            values.push_back(abs(col));
        }
    }
    return values;
}

void AdjMatrix::varyEdgeThreshold(PropertyMatrix& propertyMatrix, unsigned int offset) const {
    vector<double> values = getValues();

    sort(values.begin(), values.end());

    unsigned int count = 0;
    for (double t = -1.0; t < 1.01; t += 0.01) {
        while (count < values.size() && values[count] < t) {
            count ++;
        }

        // get density of graph at this point
        Graph g;
        g.loadFromMatrixWithThreshold((*this), t, marketStockNames);

        Property property = propertyMatrix.at(t, offset);

        property.density = g.density(FULL);
        property.avgDegree = g.averageDegree(FULL);
//        property.avgDistance = g.averageDistance(FULL, 1.0);
        property.percentOfEdges = double(count)/double(values.size());
        property.clusteringCoefficient = g.averageClusteringCoefficient(FULL);

        propertyMatrix.assignAt(t, offset, property);
    }
}

