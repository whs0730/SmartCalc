#include "math/Matrix.h"

#include <stdexcept>

Matrix::Matrix(int r, int c) {
    // 行列数必须同时为 0，或者同时为正数。
    if (r < 0 || c < 0) {
        throw invalid_argument("Matrix row and column cannot be negative.");
    }

    if ((r == 0 && c != 0) || (r != 0 && c == 0)) {
        throw invalid_argument(
            "Matrix row and column must both be zero or both be positive."
        );
    }

    row = r;
    col = c;
    data = vector<vector<double>>(row, vector<double>(col, 0));
}

Matrix::~Matrix() {
}

int Matrix::getRow() const {
    return row;
}

int Matrix::getCol() const {
    return col;
}

double Matrix::get(int r, int c) const {
    if (r < 0 || r >= row || c < 0 || c >= col) {
        throw out_of_range("Matrix index is out of range.");
    }

    return data[r][c];
}

void Matrix::set(int r, int c, double value) {
    if (r < 0 || r >= row || c < 0 || c >= col) {
        throw out_of_range("Matrix index is out of range.");
    }

    data[r][c] = value;
}

Matrix Matrix::add(Matrix m) const {
    if (row != m.row || col != m.col) {
        throw invalid_argument("Two matrices must have the same size.");
    }

    Matrix result(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            result.data[i][j] = data[i][j] + m.data[i][j];
        }
    }

    return result;
}

Matrix Matrix::sub(Matrix m) const {
    if (row != m.row || col != m.col) {
        throw invalid_argument("Two matrices must have the same size.");
    }

    Matrix result(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            result.data[i][j] = data[i][j] - m.data[i][j];
        }
    }

    return result;
}

Matrix Matrix::dot(Matrix m) const {
    if (col != m.row) {
        throw invalid_argument(
            "The first matrix column must equal the second matrix row."
        );
    }

    Matrix result(row, m.col);

    // result[i][j] 是当前行和当前列对应元素乘积之和。
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < m.col; j++) {
            for (int k = 0; k < col; k++) {
                result.data[i][j] += data[i][k] * m.data[k][j];
            }
        }
    }

    return result;
}

Matrix Matrix::multiply(double num) const {
    Matrix result(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            result.data[i][j] = data[i][j] * num;
        }
    }

    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(col, row);

    // 转置后原来的行列位置互换。
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            result.data[j][i] = data[i][j];
        }
    }

    return result;
}
