#pragma once

#include <vector>

using namespace std;

class Matrix {
private:
    int row;
    int col;
    vector<vector<double>> data;

public:
    Matrix(int r = 0, int c = 0);
    ~Matrix();

    int getRow() const;//获取行
    int getCol() const;//获取列

    double get(int r, int c) const;//获得元素值
    void set(int r, int c, double value);//设置元素值

    Matrix add(Matrix m) const;//矩阵加法
    Matrix sub(Matrix m) const;//矩阵减法
    Matrix dot(Matrix m) const;//矩阵乘法
    Matrix multiply(double num) const;//常数乘矩阵
    Matrix transpose() const;//矩阵转置
};
