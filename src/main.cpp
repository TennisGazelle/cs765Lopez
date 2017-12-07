#include <iostream>
#include <Portfolio.h>
#include <cmath>

#include <teexgraph/Graph.h>
#include <AdjMatrix.h>

#include "config.h"

using namespace std;

bool shootWithProbability(double prob) {
    double shot = double(rand())/double(RAND_MAX);
    return (shot <= prob);
}

void outputCorrelationMatrixToFile(const string& filename, const AdjMatrix& matrix, Market& market, double threshold) {
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

void outputEdgeListToFile(const string& filename, const AdjMatrix& matrix, Market& market, double threshold) {
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
    srand((unsigned int)time(nullptr));

    Market market;
    market.init();
    AdjMatrix countMap(MAX_OFFSET);

    // declare the indexes at which to
    for (unsigned int offset = 1; offset < MAX_OFFSET; offset++) {
        srand(2);
        AdjMatrix correlationMatrix(market.size());
        cout << "working on offset " << offset << endl;
        vector<bool> actionIndexes                  = defineActionTimes(market[0].data.size(), offset);
        vector<Portfolio> portfolios                = market.initPortfolios(offset, actionIndexes);

        correlationMatrix.fillCorrelationMatrix(market, portfolios);
        correlationMatrix.makeGraph(market);

        cout << "outputting..." << endl;
        outputCorrelationMatrixToFile("../out/correlation" + to_string(offset) + ".csv", correlationMatrix, market, 0.0);
        outputEdgeListToFile("../out/edge_list" + to_string(offset) + ".csv", correlationMatrix, market, .8);
        countMap[offset-1] = correlationMatrix.varyThreshold();
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