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

        case CLOSENESS_DISTRIBUTION_AVG:
            return "CLOSENESS_DISTRIBUTION_AVG";
        case CLOSENESS_DISTRIBUTION_STD_DEV:
            return "CLOSENESS_DISTRIBUTION_STD_DEV";
        case CLOSENESS_RANGE_MIN:
            return "CLOSENESS_RANGE_MIN";
        case CLOSENESS_RANGE_MAX:
            return "CLOSENESS_RANGE_MAX";
    }
}

PropertyMatrix::PropertyMatrix() {
    resize(MAX_OFFSET + 3); // for the three pearson variants
    for (auto& r : (*this)) {
        r.resize(200);
    }
}

PropertyMatrix::~PropertyMatrix() {

}

void PropertyMatrix::assignAt(double threshold, unsigned int offset, const Property &incomingProp) {
    (*this)[offset][thresholdToIndex(threshold)] = incomingProp;
}

void PropertyMatrix::assignAt(unsigned int threshold, unsigned int offset, const Property &incomingProp) {
    (*this)[offset][threshold] = incomingProp;
}

const Property& PropertyMatrix::at(double threshold, unsigned int offset) const {
    // transform threshold to column
    return vector::at(offset)[thresholdToIndex(threshold)];
}

Property& PropertyMatrix::at(double threshold, unsigned int offset) {
    return vector::at(offset)[thresholdToIndex(threshold)];
}

int PropertyMatrix::thresholdToIndex(double threshold) const {
    if (threshold < 0.0 || threshold > 1.0) {
        return -1;
    }
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

    outputToFile(CLOSENESS_DISTRIBUTION_AVG);
    outputToFile(CLOSENESS_DISTRIBUTION_STD_DEV);
    outputToFile(CLOSENESS_RANGE_MIN);
    outputToFile(CLOSENESS_RANGE_MAX);
}

void PropertyMatrix::outputToFile(PropertyEnum propertyChoice) const {
    string filename = fileHeader + to_string(propertyChoice) + fileExtension;

    char delimeter = ',';
    ofstream fout(filename);
    fout << delimeter;
    for (double t = 0.0; t < 1.001; t += 0.005) {
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
            fout << "PEARSON_CUBE_ROOT";

        fout << delimeter;
        for (unsigned int c = 0; c < (*this)[r].size(); c++) {
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

                case CLOSENESS_DISTRIBUTION_AVG:
                    fout << (*this)[r][c].closenessDistribution.first;
                    break;
                case CLOSENESS_DISTRIBUTION_STD_DEV:
                    fout << (*this)[r][c].closenessDistribution.second;
                    break;
                case CLOSENESS_RANGE_MIN:
                    fout << (*this)[r][c].closenessRange.first;
                    break;
                case CLOSENESS_RANGE_MAX:
                    fout << (*this)[r][c].closenessRange.second;
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