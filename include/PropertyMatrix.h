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
    double percentOfEdges;
};

// rows are offsets
// columns are percentage threshold
class PropertyMatrix : public vector< vector<Property> > {
public:
    PropertyMatrix();

    const Property& at(double threshold, unsigned int offset) const;
    Property& at(double threshold, unsigned int offset);

private:
    int thresholdToIndex(double threshold) const;

};


#endif //STOCKCOMPLEXNETWORKS_PROPERTYMATRIX_H
