//
// Created by daniellopez on 12/7/17.
//

#include <config.h>
#include "PropertyMatrix.h"

string to_string(const PropertyEnum pe) {
    switch (pe) {
        case DENSITY:
            return "DENSITY";
        case AVG_DEGREE:
            return "AVG_DEGREE";
        case AVG_DISTANCE:
            return "AVG_DISTANCE";
        case PERCENT_EDGES:
            return "PERCENT_EDGES";
        case CLUSTERING_COEFFICIENT:
            return "CLUSTERING_COEFFICIENT";

        case BETWEENNESS_DISTRIBUTION_AVG:
            return "BETWEENNESS_DISTRIBUTION_AVG";
        case BETWEENNESS_DISTRIBUTION_STD_DEV:
            return "BETWEENNESS_DISTRIBUTION_STD_DEV";
        case BETWEENESS_RANGE_MIN:
            return "BETWEENESS_RANGE_MIN";
        case BETWEENESS_RANGE_MAX:
            return "BETWEENESS_RANGE_MAX";

        case OUTDEGREE_DISTRIBUTION_AVG:
            return "OUTDEGREE_DISTRIBUTION_AVG";
        case OUTDEGREE_DISTRIBUTION_STD_DEV:
            return "OUTDEGREE_DISTRIBUTION_STD_DEV";
        case OUTDEGREE_RANGE_MIN:
            return "OUTDEGREE_RANGE_MIN";
        case OUTDEGREE_RANGE_MAX:
            return "OUTDEGREE_RANGE_MAX";

        case PAGERANK_DISTRIBUTION_AVG:
            return "PAGERANK_DISTRIBUTION_AVG";
        case PAGERANK_DISTRIBUTION_STD_DEV:
            return "PAGERANK_DISTRIBUTION_STD_DEV";
        case PAGERANK_RANGE_MIN:
            return "PAGERANK_RANGE_MIN";
        case PAGERANK_RANGE_MAX:
            return "PAGERANK_RANGE_MAX";
    }
}

PropertyMatrix::PropertyMatrix() {
    resize(MAX_OFFSET + 3); // for the three pearson variants
    for (auto& r : (*this)) {
        r.resize(200);
    }
}

PropertyMatrix::~PropertyMatrix() {
    for (auto &r : (*this)) {
        for (auto &v : r) {
            if (v.g != nullptr) {
                delete v.g;
            }
        }
    }
}

void PropertyMatrix::assignAt(double threshold, unsigned int offset, const Property &incomingProp) {
    (*this)[offset][thresholdToIndex(threshold)] = incomingProp;
}

const Property& PropertyMatrix::at(double threshold, unsigned int offset) const {
    // transform threshold to column
    return vector::at(offset)[thresholdToIndex(threshold)];
}

Property& PropertyMatrix::at(double threshold, unsigned int offset) {
    return vector::at(offset)[thresholdToIndex(threshold)];
}

int PropertyMatrix::thresholdToIndex(double threshold) const {
    if (threshold < -1.0 || threshold > 1.0) {
        return -1;
    }
    threshold = (threshold + 1.0)/2.0;
    return int(threshold * 200.0);
}

void PropertyMatrix::outputAllPropertiesToFile() const {
    outputToFile(DENSITY);
    outputToFile(AVG_DEGREE);
    outputToFile(AVG_DISTANCE);
    outputToFile(PERCENT_EDGES);
    outputToFile(CLUSTERING_COEFFICIENT);

    outputToFile(BETWEENNESS_DISTRIBUTION_AVG);
    outputToFile(BETWEENNESS_DISTRIBUTION_STD_DEV);
    outputToFile(BETWEENESS_RANGE_MIN);
    outputToFile(BETWEENESS_RANGE_MAX);

    outputToFile(OUTDEGREE_DISTRIBUTION_AVG);
    outputToFile(OUTDEGREE_DISTRIBUTION_STD_DEV);
    outputToFile(OUTDEGREE_RANGE_MIN);
    outputToFile(OUTDEGREE_RANGE_MAX);

    outputToFile(PAGERANK_DISTRIBUTION_AVG);
    outputToFile(PAGERANK_DISTRIBUTION_STD_DEV);
    outputToFile(PAGERANK_RANGE_MIN);
    outputToFile(PAGERANK_RANGE_MAX);
}

void PropertyMatrix::outputToFile(PropertyEnum propertyChoice) const {
    string filename = fileHeader + to_string(propertyChoice) + fileExtension;

    char delimeter = ',';
    ofstream fout(filename);
    fout << delimeter;
    for (double t = 0.0; t < 1.01; t += 0.01) {
        fout << t << delimeter;
    }
    fout << endl;

    for (unsigned int r = 0; r < size(); r++) {
        if (r < MAX_OFFSET)
            fout << r;
        else if (r == PEARSON_W_SQUARE_V_SQUARE_ROOT)
            fout << "PEARSON_SQUARE_ROOT";
        else if (r == PEARSON_W_LOG_V_EXP)
            fout << "PEARSON_LOG_EXP";
        else
            fout << "PEARSON_SINE_ARCSINE";

        fout << delimeter;
        for (unsigned int c = 100; c < (*this)[r].size(); c++) {
            switch (propertyChoice) {
                case DENSITY:
                    fout << (*this)[r][c].density;
                    break;
                case AVG_DEGREE:
                    fout << (*this)[r][c].avgDegree;
                    break;
                case AVG_DISTANCE:
                    fout << (*this)[r][c].avgDistance;
                    break;
                case PERCENT_EDGES:
                    fout << (*this)[r][c].percentOfEdges;
                    break;
                case CLUSTERING_COEFFICIENT:
                    fout << (*this)[r][c].clusteringCoefficient;
                    break;

                case BETWEENNESS_DISTRIBUTION_AVG:
                    fout << (*this)[r][c].betweennessDistribution.first;
                    break;
                case BETWEENNESS_DISTRIBUTION_STD_DEV:
                    fout << (*this)[r][c].betweennessDistribution.second;
                    break;
                case BETWEENESS_RANGE_MIN:
                    fout << (*this)[r][c].betweennessRange.first;
                    break;
                case BETWEENESS_RANGE_MAX:
                    fout << (*this)[r][c].betweennessRange.second;
                    break;

                case OUTDEGREE_DISTRIBUTION_AVG:
                    fout << (*this)[r][c].outdegreeDistribution.first;
                    break;
                case OUTDEGREE_DISTRIBUTION_STD_DEV:
                    fout << (*this)[r][c].outdegreeDistribution.second;
                    break;
                case OUTDEGREE_RANGE_MIN:
                    fout << (*this)[r][c].outdegreeRange.first;
                    break;
                case OUTDEGREE_RANGE_MAX:
                    fout << (*this)[r][c].outdegreeRange.second;
                    break;

                case PAGERANK_DISTRIBUTION_AVG:
                    fout << (*this)[r][c].pagerankDistribution.first;
                    break;
                case PAGERANK_DISTRIBUTION_STD_DEV:
                    fout << (*this)[r][c].pagerankDistribution.second;
                    break;
                case PAGERANK_RANGE_MIN:
                    fout << (*this)[r][c].pagerankRange.first;
                    break;
                case PAGERANK_RANGE_MAX:
                    fout << (*this)[r][c].pagerankRange.second;
                    break;
            }
            fout << delimeter;
        }
        fout << endl;
    }
    fout.close();
}

vector<vector<pair<unsigned int, unsigned int> > > PropertyMatrix::getTop10StrongestEdges() const {
    return top10StrongestEdgesLocations;
}