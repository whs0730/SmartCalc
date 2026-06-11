#include "math/MatrixSolver.h"

#include <cmath>
#include <stdexcept>

// 使用第一行展开计算行列式。
double MatrixSolver::determinant(Matrix matrix) {
    if (matrix.getRow() != matrix.getCol()) {
        throw std::invalid_argument(
            "Determinant requires a square matrix."
        );
    }

    int size = matrix.getRow();

    if (size == 0) {
        throw std::invalid_argument("Matrix cannot be empty.");
    }

    if (size == 1) {
        return matrix.get(0, 0);
    }

    if (size == 2) {
        return matrix.get(0, 0) * matrix.get(1, 1)
            - matrix.get(0, 1) * matrix.get(1, 0);
    }

    double result = 0;

    for (int col = 0; col < size; col++) {
        Matrix minorMatrix = getMinor(matrix, 0, col);
        double number = matrix.get(0, col) * determinant(minorMatrix);

        if (col % 2 == 0) {
            result += number;
        }
        else {
            result -= number;
        }
    }

    return result;
}

// 使用高斯-约旦消元法计算逆矩阵。
Matrix MatrixSolver::inverse(Matrix matrix) {
    if (matrix.getRow() != matrix.getCol()) {
        throw std::invalid_argument("Inverse requires a square matrix.");
    }

    int size = matrix.getRow();

    if (size == 0) {
        throw std::invalid_argument("Matrix cannot be empty.");
    }

    Matrix result(size, size);

    for (int i = 0; i < size; i++) {
        result.set(i, i, 1);
    }

    for (int col = 0; col < size; col++) {
        int maxRow = col;

        for (int row = col + 1; row < size; row++) {
            if (
                std::abs(matrix.get(row, col))
                > std::abs(matrix.get(maxRow, col))
            ) {
                maxRow = row;
            }
        }

        if (std::abs(matrix.get(maxRow, col)) < 0.0000001) {
            throw std::invalid_argument("Matrix has no inverse.");
        }

        if (maxRow != col) {
            for (int j = 0; j < size; j++) {
                double temp = matrix.get(col, j);
                matrix.set(col, j, matrix.get(maxRow, j));
                matrix.set(maxRow, j, temp);

                temp = result.get(col, j);
                result.set(col, j, result.get(maxRow, j));
                result.set(maxRow, j, temp);
            }
        }

        double mainNumber = matrix.get(col, col);

        for (int j = 0; j < size; j++) {
            matrix.set(col, j, matrix.get(col, j) / mainNumber);
            result.set(col, j, result.get(col, j) / mainNumber);
        }

        for (int row = 0; row < size; row++) {
            if (row == col) {
                continue;
            }

            double number = matrix.get(row, col);

            for (int j = 0; j < size; j++) {
                matrix.set(
                    row,
                    j,
                    matrix.get(row, j) - number * matrix.get(col, j)
                );
                result.set(
                    row,
                    j,
                    result.get(row, j) - number * result.get(col, j)
                );
            }
        }
    }

    return result;
}

// 使用高斯消元和回代求解线性方程组。
vector<double> MatrixSolver::solve(Matrix matrix,vector<double> answer) {
    if (matrix.getRow() != matrix.getCol()) {
        throw std::invalid_argument(
            "Equation matrix must be square."
        );
    }

    int size = matrix.getRow();

    if (size == 0 || answer.size() != static_cast<unsigned int>(size)) {
        throw std::invalid_argument("Equation size is incorrect.");
    }

    for (int col = 0; col < size; col++) {
        int maxRow = col;

        for (int row = col + 1; row < size; row++) {
            if (
                std::abs(matrix.get(row, col))
                > std::abs(matrix.get(maxRow, col))
            ) {
                maxRow = row;
            }
        }

        if (std::abs(matrix.get(maxRow, col)) < 0.0000001) {
            throw std::invalid_argument(
                "Equation has no unique solution."
            );
        }

        if (maxRow != col) {
            for (int j = 0; j < size; j++) {
                double temp = matrix.get(col, j);
                matrix.set(col, j, matrix.get(maxRow, j));
                matrix.set(maxRow, j, temp);
            }

            double temp = answer[col];
            answer[col] = answer[maxRow];
            answer[maxRow] = temp;
        }

        for (int row = col + 1; row < size; row++) {
            double number =
                matrix.get(row, col) / matrix.get(col, col);

            for (int j = col; j < size; j++) {
                matrix.set(
                    row,
                    j,
                    matrix.get(row, j) - number * matrix.get(col, j)
                );
            }

            answer[row] = answer[row] - number * answer[col];
        }
    }

    vector<double> result(size, 0);

    for (int row = size - 1; row >= 0; row--) {
        double value = answer[row];

        for (int col = row + 1; col < size; col++) {
            value -= matrix.get(row, col) * result[col];
        }

        result[row] = value / matrix.get(row, row);
    }

    return result;
}

// 删除指定行和列，得到余子式矩阵。
Matrix MatrixSolver::getMinor(Matrix matrix,int removeRow,int removeCol) {
    int size = matrix.getRow();
    Matrix result(size - 1, size - 1);
    int resultRow = 0;

    for (int row = 0; row < size; row++) {
        if (row == removeRow) {
            continue;
        }

        int resultCol = 0;

        for (int col = 0; col < size; col++) {
            if (col == removeCol) {
                continue;
            }

            result.set(resultRow, resultCol, matrix.get(row, col));
            resultCol++;
        }

        resultRow++;
    }

    return result;
}
