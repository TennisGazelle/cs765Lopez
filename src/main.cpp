#include <iostream>
#include <Portfolio.h>
#include <cmath>

#include <teexgraph/Graph.h>

#include "Logger.h"
#include "config.h"

using namespace std;

bool shootWithProbability(double prob) {
    double shot = double(rand())/double(RAND_MAX);
    return (shot <= prob);
}

double getSumOfCorrelationsBetweenPortfoliosAtIndex(int i, int j, vector<Stock>& market, vector<Portfolio>& portfolios) {
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

vector< vector<double> > getCorrelationMatrix(Market &m, vector<Portfolio>& pfs) {
    vector< vector<double> > correlation;
    correlation.resize(m.size());
    for (auto& row : correlation) {
        row.resize(m.size());
    }

    for (unsigned int i = 0; i < m.size(); i++) {
        for (unsigned int j = 0; j < m.size(); j++) {
            correlation[i][j] = getSumOfCorrelationsBetweenPortfoliosAtIndex(i, j, m, pfs);
        }
    }

    return correlation;
}

void outputCorrelationMatrixToFile(const string& filename, const vector< vector<double> >& matrix, Market& market, double threshold) {
    ofstream fout(filename);
    for (unsigned int i = 0; i < market.size(); i++) {
        cout << "," << market[i].symbol;
        fout << "," << market[i].symbol;
    }
    cout << endl;
    fout << endl;
    unsigned int count_edges = 0;
    for (unsigned int i = 0; i < market.size(); i++) {
        cout << market[i].symbol;
        fout << market[i].symbol;
        for (unsigned int j = 0; j < market.size(); j++) {
            cout << ",";
            fout << ",";
            double c = matrix[i][j];
            if (i != j && (c > threshold || c < -threshold)) {
                count_edges++;
                cout << c;
                fout << c;
            }
        }
        cout << endl;
        fout << endl;
    }
    fout.close();
    cout << count_edges/2 << " total edges." << endl;
}

void outputEdgeListToFile(const string& filename, const vector< vector<double> >& matrix, Market& market, double threshold) {
    ofstream fout(filename);
    for (unsigned int r = 0; r < matrix.size(); r++) {
        for (unsigned int c = 0; c < r; c++) {
            if (matrix[r][c] > threshold || matrix[r][c] < -threshold) {
                fout << market[r].symbol << " " << market[c].symbol << endl;
            }
        }
    }
    fout.close();
}

vector<double> varyThreshold(const vector< vector<double> >& matrix) {
    vector<double> values;
    values.reserve(matrix.size()*matrix.size());
    for (const auto& row : matrix) {
        for (const auto& col : row) {
            values.push_back(abs(col));
        }
    }
    sort(values.begin(), values.end());
//    cout << "highest correrlation value is: " << (values.back()) << endl;

    vector<double> percentageValuesLowerThan;
    unsigned int count = 0;
    for (double t = -1.0; t < 1.01; t += 0.01) {
        while (count < values.size() && values[count] < t) {
            count ++;
        }
//        cout << "num of values lower than " << t << " : " << count << "[" << double(count)/double(values.size()) << "%]" << endl;
        percentageValuesLowerThan.push_back(double(count)/double(values.size()));
    }
    return percentageValuesLowerThan;
}

vector<bool> defineActionTimes(unsigned int size, unsigned int offset) {
    vector<bool> indeces(size);
    for (unsigned int i = 0; i < indeces.size(); i++) {
        indeces[i] = shootWithProbability(.24);
        if (i+offset >= indeces.size()) {
            indeces[i] = false;
        }
    }
    return indeces;
}

void makeGraph(const vector< vector<double> >& matrix, const Market& market) {
    Graph g;
    vector<string> stockNames(matrix.size());

    for(unsigned int i = 0; i < stockNames.size(); i++) {
        stockNames[i] = market[i].symbol;
    }
    g.loadFromMatrixWithThreshold(matrix, 0.9, stockNames);

    vector<double> centralities = g.pageRankCentrality();

    for (unsigned int i = 0; i < stockNames.size(); i++) {
        cout << stockNames[i] << ": " << centralities[i] << endl;
    }
}

int main(int argc, char *argv[]) {
//    srand((unsigned int)time(nullptr));
    srand(2);

    Market market;
    market.init(STOCK_NAMES);
    vector< vector<double> > countMap(MAX_OFFSET);

    // declare the indexes at which to
    for (unsigned int offset = 1; offset < MAX_OFFSET; offset++) {
        cout << "working on offset " << offset << endl;
        vector<bool> actionIndexes                  = defineActionTimes(market[0].data.size(), offset);
        vector<Portfolio> portfolios                = market.initPortfolios(offset, actionIndexes);
        vector< vector<double> > correlationMatrix  = getCorrelationMatrix(market, portfolios);

        makeGraph(correlationMatrix, market);

        cout << "outputting..." << endl;
        outputCorrelationMatrixToFile("../out/correlation" + to_string(offset) + ".csv", correlationMatrix, market, 0.0);
        outputEdgeListToFile("../out/edge_list" + to_string(offset) + ".csv", correlationMatrix, market, .8);
        countMap[offset-1] = varyThreshold(correlationMatrix);
    }

    for (unsigned int r = 0; r < MAX_OFFSET-1; r++) {
        cout << r+1 << ": ";
        for (unsigned int c = 0; c < countMap[r].size(); c++) {
            cout << countMap[r][c] << ", ";
        }
        cout << endl;
    }

    return 0;
}