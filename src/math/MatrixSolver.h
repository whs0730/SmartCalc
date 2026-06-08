#pragma once

#include "math/Matrix.h"

#include <vector>

using namespace std;

class MatrixSolver {
private:
    Matrix getMinor(Matrix matrix, int removeRow, int removeCol);

public:
    double determinant(Matrix matrix);
    Matrix inverse(Matrix matrix);
    vector<double> solve(Matrix matrix, vector<double> answer);
};
