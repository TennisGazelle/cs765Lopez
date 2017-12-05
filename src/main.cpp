#include <iostream>
#include <Portfolio.h>
#include <cmath>

#include <igraph/igraph.h>

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
    return log(sum/double(portfolios.size()));
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

vector<unsigned int> varyThreshold(const vector< vector<double> >& matrix) {
    vector<double> values;
    values.reserve(matrix.size()*matrix.size());
    for (const auto& row : matrix) {
        for (const auto& col : row) {
            values.push_back(abs(col));
        }
    }
    sort(values.begin(), values.end());

    vector<unsigned int> numValuesLowerThan;
    numValuesLowerThan.reserve(100);
    unsigned int count = 0;
    for (float t = 0.0; t < 3.0; t += 0.01) {
        while (count < values.size() && values[count] < t) {
            count ++;
        }
//        cout << "num of values lower than " << t << " : " << count << "[" << double(count)/double(values.size()) << "%]" << endl;
        numValuesLowerThan.push_back(count);
    }
    return numValuesLowerThan;
}

vector<Portfolio> initPortfolios(Market& market, unsigned int offset, vector<bool> actionIndexes) {
    vector<Portfolio> portfolios;
    // put in a focus for each one
    for (unsigned int i = 0; i < market.size(); i++) {
        portfolios.emplace_back(Portfolio(&market[i], offset));

        // for each data point
        for (unsigned int data_index = 0; data_index < market[0].data.size(); data_index++) {
            if (actionIndexes[data_index]) {
                portfolios[i].doAction(market, data_index);
                if (i == actionIndexes.size()-1) {
                    portfolios[i].finalizeActions(market, data_index);
                }
                if (isnan(portfolios[i].getMoney())) {
                    cout << "Portfolio [" << i << "," << market[i].symbol << "] became nan with action at timestep: " << data_index << endl;
                }
            }
        }
//        cout << "Created Portfolio [" << i << "," + market[i].symbol + "] - Total Return with offset " << offset << ": " << portfolios[i].getMoney() << endl;
    }

    return portfolios;
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

void makeGraph(const vector< vector<double> >& matrix) {
    igraph_t g;
    igraph_scg_matrix_t mat;

//    igraph_matrix_init(&matrix[0][0], matrix.size(), matrix.size());

    // matrix should be a square matrix
    for (unsigned int r = 0; r < matrix.size(); r++) {
        for (unsigned int c = 0; c < r; c++) {
            MATRIX(mat, r, c) = matrix[r][c];
        }
    }



}

int main(int argc, char *argv[]) {
//    srand((unsigned int)time(nullptr));
    srand(2);

    Market market;
    market.init(STOCK_NAMES);
    vector< vector<unsigned int> > countMap(MAX_OFFSET);

    // declare the indexes at which to
    for (unsigned int offset = 1; offset < 2; offset++) {
        cout << "working on offset " << offset << endl;
        vector<bool> actionIndexes                  = defineActionTimes(market[0].data.size(), offset);
        vector<Portfolio> portfolios                = initPortfolios(market, offset, actionIndexes);
        vector< vector<double> > correlationMatrix  = getCorrelationMatrix(market, portfolios);

        makeGraph(correlationMatrix);

        cout << "outputting..." << endl;
        outputCorrelationMatrixToFile("../out/correlation" + to_string(offset) + ".csv", correlationMatrix, market, 0.0);
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