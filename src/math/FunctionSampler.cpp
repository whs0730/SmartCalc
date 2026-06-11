#include "math/FunctionSampler.h"

#include <stdexcept>
vector<SamplePoint> FunctionSampler::sample(double start,double end,int pointCount,double (*function)(double)) const {
    if (start >= end) {
        throw invalid_argument(
            "Sample interval start must be less than end."
        );
    }

    if (pointCount < 2) {
        throw invalid_argument(
            "At least two sample points are required."
        );
    }

    if (function == 0) {
        throw invalid_argument("Sample function cannot be null.");
    }

    vector<SamplePoint> result(pointCount);
    double step = (end - start) / (pointCount - 1);

    for (int i = 0; i < pointCount; i++) {
        double x = start + step * i;
        result[i].x = x;
        result[i].y = function(x);
    }
    return result;
}
