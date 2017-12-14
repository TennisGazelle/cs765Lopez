//
// Created by Daniel Lopez on 12/10/17.
//

#include <cmath>
#include <cfloat>
#include "Matrix.h"

vector<double> Matrix::getValues() const {
    vector<double> values(size() * size());
    for (const auto &row : (*this)) {
        for (const auto &col : row) {
            values.push_back(abs(col));
        }
    }
    return values;
}

pair<double, double> Matrix::getValueDistribution() const {
    vector<double> values = getValues();
    return getValueDistribution(values);
}

pair<double, double> Matrix::getValueDistribution(vector<double> values) {
    double sum = 0.0, average = 0.0, variance = 0.0;

    for (auto &v : values) {
        sum += v;
    }
    average = sum / values.size();
    if (isnan(average))
        average = 0;

    sum = 0;
    for (auto &v : values) {
        sum += pow(average - v, 2);
    }
    variance = sum / (values.size() - 1);
    if (isnan(variance))
        variance = 0;

    return {average, variance};
}

pair<double, double> Matrix::getValueRange(vector<double> &values) {
    double highest = 0.0, lowest = DBL_MAX;

    for (auto &v : values) {
        lowest = min(lowest, v);
        highest = max(highest, v);
    }

    return {lowest, highest};
}