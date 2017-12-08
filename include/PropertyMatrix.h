//
// Created by daniellopez on 12/7/17.
//

#ifndef STOCKCOMPLEXNETWORKS_PROPERTYMATRIX_H
#define STOCKCOMPLEXNETWORKS_PROPERTYMATRIX_H

#include <vector>

using namespace std;

struct Property {
    double density;
    double avgDegree;
    double avgDistance;
    double percentOfEdges;
    double clusteringCoefficient;
};

enum PropertyEnum {
    DENSITY,
    AVG_DEGREE,
    AVG_DISTANCE,
    PERCENT_EDGES,
    CLUSTERING_COEFFICIENT,
};

// rows are offsets
// columns are percentage threshold
class PropertyMatrix : public vector< vector<Property> > {
public:
    PropertyMatrix();

    const Property& at(double threshold, unsigned int offset) const;
    Property& at(double threshold, unsigned int offset);
    void assignAt(double threshold, unsigned int offset, const Property& incomingProp);

private:
    int thresholdToIndex(double threshold) const;

};


#endif //STOCKCOMPLEXNETWORKS_PROPERTYMATRIX_H
