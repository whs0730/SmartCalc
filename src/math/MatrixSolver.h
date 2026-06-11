#pragma once
//矩阵计算模块
#include "math/Matrix.h"

#include <vector>

using namespace std;

class MatrixSolver {
private:
    Matrix getMinor(Matrix matrix, int removeRow, int removeCol);

public:
    double determinant(Matrix matrix);             // 计算行列式
    Matrix inverse(Matrix matrix);                 // 计算逆矩阵
    vector<double> solve(                          // 求解线性方程组
        Matrix matrix,
        vector<double> answer
    );
};
