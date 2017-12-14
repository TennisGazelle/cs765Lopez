//
// Created by Daniel Lopez on 12/6/17.
//

#include <iostream>
#include <cmath>
#include <teexgraph/Graph.h>
#include <Matrix.h>
#include <config.h>
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

void AdjMatrix::fillPearsonCorrelation(Market &m, PearsonKernel pk) {
    marketStockNames.clear();
    for (unsigned int i = 0; i < m.size(); i++) {
        marketStockNames.push_back(m[i].symbol);
        for (unsigned int j = 0; j < m.size(); j++) {
            (*this)[i][j] = this->getPearsonCorrelationBetween(i, j, m, pk);
        }
    }
}

double AdjMatrix::getPearsonCorrelationBetween(int i, int j, Market &market, PearsonKernel pk) {
    double r_i_avg, r_j_avg;
    vector<double> d_i, d_j;

    if (i == j)
        return 1;

    d_i = market[i].percentChanges;
    d_j = market[j].percentChanges;

    r_i_avg = Matrix::getValueDistribution(d_i).first;
    r_j_avg = Matrix::getValueDistribution(d_j).first;
    for (unsigned int index = 0; index < d_i.size(); index++) {
        d_i[index] -= r_i_avg;
        d_j[index] -= r_j_avg;
    }

    double numerator = 0.0;
    double denominator_left = 0.0, denominator_right = 0.0;
    for (unsigned int index = 0; index < d_i.size(); index++) {
        numerator += d_i[index]*d_j[index];

        // apply the correct function
        switch (pk) {
            default:
            case SQUARE_V_SQUARE_ROOT:
                denominator_left += pow(d_i[index], 2);
                denominator_right += pow(d_j[index], 2);
                break;
            case LOG_V_EXP:
                denominator_left += exp(abs(d_i[index]));
                denominator_right += exp(abs(d_j[index]));
                break;
            case CUBE_V_CUBE_ROOT:
                denominator_left += abs(pow(d_i[index], 3));
                denominator_right += abs(pow(d_j[index], 3));
                break;
        }
    }

    switch (pk) {
        default:
        case SQUARE_V_SQUARE_ROOT:
            denominator_left = sqrt(denominator_left);
            denominator_right = sqrt(denominator_right);
            break;
        case LOG_V_EXP:
            denominator_left = log(denominator_left);
            denominator_right = log(denominator_right);
            break;
        case CUBE_V_CUBE_ROOT:
            denominator_left = cbrt(denominator_left);
            denominator_right = cbrt(denominator_right);
    }

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
    auto *g = new Graph();
    for (unsigned int thousandth = 0; thousandth < 1000; thousandth += 5) {
        double t = double(thousandth) / 1000.0;
        while (count < values.size() && values[count] < t) {
            count ++;
        }

        // generate graph and get stats at this point
        Property property;
        g->clear();
        g->loadFromMatrixWithThreshold((*this), t, marketStockNames);

        property.density = g->density(FULL);
        property.avgDegree = g->averageDegree(FULL);
        property.avgDistance = g->averageDistance(FULL, 1.0);
        property.percentOfEdges = double(count)/double(values.size());
        property.clusteringCoefficient = g->averageClusteringCoefficient(FULL);

        vector<double> temp;
        temp = g->betweennessCentrality(FULL, 1.0);
        property.betweennessDistribution = Matrix::getValueDistribution(temp);
        property.betweennessRange = Matrix::getValueRange(temp);

        temp = g->outdegreeCentrality();
        property.outdegreeDistribution = Matrix::getValueDistribution(temp);
        property.outdegreeRange = Matrix::getValueRange(temp);

        temp = g->pageRankCentrality();
        property.pagerankDistribution = Matrix::getValueDistribution(temp);
        property.pagerankRange = Matrix::getValueRange(temp);

        temp = g->closenessCentrality(FULL, 1.0);
        property.closenessDistribution = Matrix::getValueDistribution(temp);
        property.closenessRange = Matrix::getValueRange(temp);

        propertyMatrix.assignAt(thousandth / 5, offset, property);
    }
    delete g;
}

vector<pair<unsigned int, unsigned int> > AdjMatrix::top10EdgeWeights() const {
    vector<pair<pair<unsigned int, unsigned int>, double> > top10(10);
    map<pair<unsigned int, unsigned int>, double> quickMapping;

    for (unsigned int r = 0; r < size(); r++) {
        for (unsigned int c = r + 1; c < at(r).size(); c++) {
            quickMapping[{r, c}] = (*this)[r][c];
        }
    }

    partial_sort_copy(quickMapping.begin(),
                      quickMapping.end(),
                      top10.begin(),
                      top10.end(),
                      [](pair<pair<unsigned int, unsigned int>, double> const &l,
                         pair<pair<unsigned int, unsigned int>, double> const &r) {
                          return l.second > r.second;
                      });
    vector<pair<unsigned int, unsigned int> > top10Keys;
    top10Keys.reserve(10);

    for (const pair<pair<unsigned int, unsigned int>, double> &both : top10) {
        top10Keys.push_back(both.first);
    }

    return top10Keys;
}

vector<DetailedEdge> AdjMatrix::outputTop10EdgeWeights(const string& filename) const {
    string full_filename = FILE_HEADER + "edges/" + filename + FILE_TSV_EXTENSION;
    ofstream fout(full_filename);
    auto locations = top10EdgeWeights();
    vector<DetailedEdge> edges;
    edges.reserve(10);

    for (auto l : locations) {
        fout << marketStockNames[l.first] << "\t" << marketStockNames[l.second] << "\t" << at(l.first)[l.second] << endl;
        edges.push_back({
                marketStockNames[l.first],
                marketStockNames[l.second],
                l.first,
                l.second,
                at(l.first)[l.second]});
    }
    fout.close();

    return edges;
}