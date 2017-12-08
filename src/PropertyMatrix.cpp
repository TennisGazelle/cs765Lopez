//
// Created by daniellopez on 12/7/17.
//

#include "PropertyMatrix.h"

PropertyMatrix::PropertyMatrix() {

}

const Property& PropertyMatrix::at(double threshold, unsigned int offset) const {
    // transform threshold to column
    return vector::at(thresholdToIndex(threshold))[offset];
}

Property& PropertyMatrix::at(double threshold, unsigned int offset) {
    return vector::at(thresholdToIndex(threshold))[offset];
}

int PropertyMatrix::thresholdToIndex(double threshold) const {
    if (threshold < -1.0 || threshold > 1.0) {
        return -1;
    }
    threshold = (threshold + 1.0)/2.0;
    return int(threshold * 200.0);
}