//
// Created by daniellopez on 12/7/17.
//

#include <config.h>
#include "PropertyMatrix.h"

PropertyMatrix::PropertyMatrix() {
    resize(MAX_OFFSET);
    for (auto& r : (*this)) {
        r.resize(200);
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