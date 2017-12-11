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

void outputPropertyMatrixToFile(const string& fileHeader, const PropertyMatrix& matrix, PropertyEnum pe) {
    char delimeter = ',';
    ofstream fout(fileHeader);
    fout << delimeter;
    for (double t = 0.0; t < 1.01; t += 0.01) {
        fout << t << delimeter;
    }
    fout << endl;

    for (unsigned int r = 0; r < matrix.size(); r++) {
        if (r < MAX_OFFSET)
            fout << r;
        else
            fout << "PEARSON";
        fout << delimeter;
        for (unsigned int c = 100; c < matrix[r].size(); c++) {
            switch (pe) {
                case DENSITY:
                    fout << matrix[r][c].density;
                    break;
                case AVG_DEGREE:
                    fout << matrix[r][c].avgDegree;
                    break;
                case AVG_DISTANCE:
                    fout << matrix[r][c].avgDistance;
                    break;
                case PERCENT_EDGES:
                    fout << matrix[r][c].percentOfEdges;
                    break;
                case CLUSTERING_COEFFICIENT:
                    fout << matrix[r][c].clusteringCoefficient;
                    break;

                case BETWEENNESS_DISTRIBUTION_AVG:
                    fout << matrix[r][c].betweennessDistribution.first;
                    break;
                case BETWEENNESS_DISTRIBUTION_STD_DEV:
                    fout << matrix[r][c].betweennessDistribution.second;
                    break;
                case BETWEENESS_RANGE_MIN:
                case BETWEENESS_RANGE_MAX:
                    break;

                case OUTDEGREE_DISTRIBUTION_AVG:
                    fout << matrix[r][c].outdegreeDistribution.first;
                    break;
                case OUTDEGREE_DISTRIBUTION_STD_DEV:
                    fout << matrix[r][c].outdegreeDistribution.second;
                    break;
                case OUTDEGREE_RANGE_MIN:
                case OUTDEGREE_RANGE_MAX:
                    break;

                case PAGERANK_DISTRIBUTION_AVG:
                    fout << matrix[r][c].pagerankDistribution.first;
                    break;
                case PAGERANK_DISTRIBUTION_STD_DEV:
                    fout << matrix[r][c].pagerankDistribution.second;
                    break;
                case PAGERANK_RANGE_MIN:
                case PAGERANK_RANGE_MAX:
                    break;
            }
            fout << delimeter;
        }
        fout << endl;
    }
    fout.close();
}

vector<bool> defineActionTimes(unsigned int size, unsigned int offset) {
    vector<bool> indeces(size);
    for (unsigned int i = 0; i < indeces.size(); i++) {
        indeces[i] = shootWithProbability(0.5);
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
    PropertyMatrix properties; // -1.0 to 1.0 by 0.01 increments

    // declare the indexes at which to
    vector<bool> actionIndexes = defineActionTimes(market[0].data.size(), 0);

    for (unsigned int offset = 0; offset < MAX_OFFSET; offset++) {
        AdjMatrix correlationMatrix(market.size());
        cout << "working on offset " << offset << endl;
        vector<Portfolio> portfolios = market.initPortfolios(offset, actionIndexes);
        correlationMatrix.fillCorrelationMatrix(market, portfolios);
        correlationMatrix.varyEdgeThreshold(properties, offset);
    }

    AdjMatrix correlationMatrix(market.size());
    cout << "working on pearson" << endl;
    correlationMatrix.fillPearsonCorrelation(market);
    correlationMatrix.varyEdgeThreshold(properties, MAX_OFFSET);

    outputPropertyMatrixToFile("../out/density_map.csv", properties, DENSITY);
    outputPropertyMatrixToFile("../out/avg_degree_map.csv", properties, AVG_DEGREE);
//    outputPropertyMatrixToFile("../out/avg_distance_map.csv", properties, AVG_DISTANCE);
    outputPropertyMatrixToFile("../out/percent_edges_map.csv", properties, PERCENT_EDGES);
    outputPropertyMatrixToFile("../out/clustering_coef_map.csv", properties, CLUSTERING_COEFFICIENT);
//    outputPropertyMatrixToFile("../out/betweenness_avg.csv", properties, BETWEENNESS_DISTRIBUTION_AVG);
//    outputPropertyMatrixToFile("../out/betweenness_std_dev.csv", properties, BETWEENNESS_DISTRIBUTION_STD_DEV);
    outputPropertyMatrixToFile("../out/out_degree_avg.csv", properties, OUTDEGREE_DISTRIBUTION_AVG);
    outputPropertyMatrixToFile("../out/out_degree_std_dev.csv", properties, OUTDEGREE_DISTRIBUTION_STD_DEV);
    outputPropertyMatrixToFile("../out/pagerank_avg.csv", properties, PAGERANK_DISTRIBUTION_AVG);
    outputPropertyMatrixToFile("../out/pagerank_std_dev.csv", properties, PAGERANK_DISTRIBUTION_STD_DEV);
    return 0;
}