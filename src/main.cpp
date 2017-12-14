#include <iostream>
#include <Portfolio.h>

#include <teexgraph/Graph.h>
#include <AdjMatrix.h>

#include "config.h"

using namespace std;

bool shootWithProbability(double prob) {
    double shot = double(rand())/double(RAND_MAX);
    return (shot <= prob);
}

void outputMatrixToFile(const string& filename, const AdjMatrix& matrix, Market& market, double threshold) {
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
        indeces[i] = shootWithProbability(1);
        if (i+offset >= indeces.size()) {
            indeces[i] = false;
        }
    }
    return indeces;
}

void evaluate(Market& market, vector< vector<DetailedEdge> >& edges) {
    ofstream fout(FILE_HEADER + "phi" + FILE_TSV_EXTENSION);

    fout << "\t\t" << "\\hline" << endl;
    fout << "\t\t" << "$\\phi$ & Value \\\\" << endl;

    fout << "\t\t" << "\\hline" << endl;
    fout << "\t\t" << "\\hline" << endl;
    for (unsigned int offset = 0; offset < edges.size(); offset++) {
        double phi = 0.0;
        for (auto edge : edges[offset]) {
            phi += market.compareStocks(edge.r, edge.c);
        }
        fout << "\t\t";
        if (offset < MAX_OFFSET) {
            fout << offset;
        } else if (offset == PEARSON_W_SQUARE_V_SQUARE_ROOT) {
            fout << "PEARSON_SQUARE_ROOT";
        } else if (offset == PEARSON_W_LOG_V_EXP) {
            fout << "PEARSON_LOG_EXP";
        } else if (offset == PEARSON_W_CUBE_V_CUBE_ROOT) {
            fout << "PEARSON_CUBE_ROOT";
        }
        fout << "\t&\t" << phi << " \\\\" << endl;
        cout << "phi value for offset of " << offset << " : " << phi << endl;
    }
    fout << "\t\t" << "\\hline" << endl;
}

int main(int argc, char *argv[]) {
    srand((unsigned int)time(nullptr));

    Market market;
    market.init();
    PropertyMatrix properties; // -1.0 to 1.0 by 0.01 increments

    // declare the indexes at which to
    vector<bool> actionIndexes = defineActionTimes(market[0].data.size(), 0);

    vector< vector<DetailedEdge> > edges;
    edges.reserve(53);

    for (unsigned int offset = 0; offset < 1; offset++) {
        AdjMatrix correlationMatrix(market.size());
        cout << "working on offset " << offset << endl;
        vector<Portfolio> portfolios = market.initPortfolios(offset, actionIndexes);
        correlationMatrix.fillCorrelationMatrix(market, portfolios);
        correlationMatrix.varyEdgeThreshold(properties, offset);
        edges.push_back(correlationMatrix.outputTop10EdgeWeights("offset-" + to_string(offset)));
    }

    AdjMatrix correlationMatrix(market.size());
    cout << "working on pearson" << endl;
    correlationMatrix.fillPearsonCorrelation(market, SQUARE_V_SQUARE_ROOT);
    correlationMatrix.varyEdgeThreshold(properties, PEARSON_W_SQUARE_V_SQUARE_ROOT);
    edges.push_back(correlationMatrix.outputTop10EdgeWeights("Pearson-SQUARE_V_SQUARE_ROOT"));

    correlationMatrix.fillPearsonCorrelation(market, LOG_V_EXP);
    correlationMatrix.varyEdgeThreshold(properties, PEARSON_W_LOG_V_EXP);
    edges.push_back(correlationMatrix.outputTop10EdgeWeights("Pearson-LOG_V_EXP"));

    correlationMatrix.fillPearsonCorrelation(market, CUBE_V_CUBE_ROOT);
    correlationMatrix.varyEdgeThreshold(properties, PEARSON_W_CUBE_V_CUBE_ROOT);
    edges.push_back(correlationMatrix.outputTop10EdgeWeights("Pearson-CUBE_V_CUBE_ROOT"));

    evaluate(market, edges);

    // output to file
    properties.outputAllPropertiesToFile();

    return 0;
}