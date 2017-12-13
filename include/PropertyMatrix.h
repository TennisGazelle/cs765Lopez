//
// Created by daniellopez on 12/7/17.
//

#ifndef STOCKCOMPLEXNETWORKS_PROPERTYMATRIX_H
#define STOCKCOMPLEXNETWORKS_PROPERTYMATRIX_H

#include <vector>
#include <teexgraph/Graph.h>

using namespace std;

struct Property {
    double density;
    double avgDegree;
    double avgDistance;
    double percentOfEdges;
    double clusteringCoefficient;
    pair<double, double> betweennessDistribution;
    pair<double, double> betweennessRange;

    pair<double, double> outdegreeDistribution;
    pair<double, double> outdegreeRange;

    pair<double, double> pagerankDistribution;
    pair<double, double> pagerankRange;

    Graph *g;
};

enum PropertyEnum {
    DENSITY,
    AVG_DEGREE,
    AVG_DISTANCE,
    PERCENT_EDGES,
    CLUSTERING_COEFFICIENT,

    BETWEENNESS_DISTRIBUTION_AVG,
    BETWEENNESS_DISTRIBUTION_STD_DEV,
    BETWEENESS_RANGE_MIN,
    BETWEENESS_RANGE_MAX,

    OUTDEGREE_DISTRIBUTION_AVG,
    OUTDEGREE_DISTRIBUTION_STD_DEV,
    OUTDEGREE_RANGE_MIN,
    OUTDEGREE_RANGE_MAX,

    PAGERANK_DISTRIBUTION_AVG,
    PAGERANK_DISTRIBUTION_STD_DEV,
    PAGERANK_RANGE_MIN,
    PAGERANK_RANGE_MAX,
};

string to_string(PropertyEnum pe);

// rows are offsets
// columns are percentage threshold
class PropertyMatrix : public vector< vector<Property> > {
public:
    PropertyMatrix();

    ~PropertyMatrix();

    const Property& at(double threshold, unsigned int offset) const;
    Property& at(double threshold, unsigned int offset);
    void assignAt(double threshold, unsigned int offset, const Property& incomingProp);

    void outputAllPropertiesToFile() const;

    void outputToFile(PropertyEnum propertyChoice) const;

    vector<vector<pair<unsigned int, unsigned int> > > top10StrongestEdgesLocations;
    vector<vector<pair<unsigned int, unsigned int> > > getTop10StrongestEdges() const;
private:

    int thresholdToIndex(double threshold) const;
    string fileHeader = "../out/", fileExtension = ".csv";
};


#endif //STOCKCOMPLEXNETWORKS_PROPERTYMATRIX_H
