//
// Created by Daniel Lopez on 12/10/17.
//

#ifndef STOCKCOMPLEXNETWORKS_MATRIX_H
#define STOCKCOMPLEXNETWORKS_MATRIX_H

#include <vector>

using namespace std;

class Matrix : public vector<vector<double> > {
public:
    vector<double> getValues() const;

    pair<double, double> getValueDistribution() const;

    static pair<double, double> getValueDistribution(vector<double> values);

    static pair<double, double> getValueRange(vector<double> &values);
};


#endif //STOCKCOMPLEXNETWORKS_MATRIX_H
