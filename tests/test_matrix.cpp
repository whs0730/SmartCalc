#include "math/Matrix.h"
#include "math/MatrixSolver.h"

#include <cmath>
#include<iostream>
#include <cassert>
#include <stdexcept>

using namespace std;

void testAdd() {
    Matrix a(2, 2);
    Matrix b(2, 2);

    a.set(0, 0, 1);
    a.set(0, 1, 2);
    a.set(1, 0, 3);
    a.set(1, 1, 4);

    b.set(0, 0, 5);
    b.set(0, 1, 6);
    b.set(1, 0, 7);
    b.set(1, 1, 8);

    Matrix result = a.add(b);

    assert(result.get(0, 0) == 6);
    assert(result.get(0, 1) == 8);
    assert(result.get(1, 0) == 10);
    assert(result.get(1, 1) == 12);
}

void testSub() {
    Matrix a(2, 2);
    Matrix b(2, 2);

    a.set(0, 0, 5);
    a.set(0, 1, 6);
    a.set(1, 0, 7);
    a.set(1, 1, 8);

    b.set(0, 0, 1);
    b.set(0, 1, 2);
    b.set(1, 0, 3);
    b.set(1, 1, 4);

    Matrix result = a.sub(b);

    assert(result.get(0, 0) == 4);
    assert(result.get(1, 1) == 4);
}

void testDot() {
    Matrix a(2, 3);
    Matrix b(3, 2);

    a.set(0, 0, 1);
    a.set(0, 1, 2);
    a.set(0, 2, 3);
    a.set(1, 0, 4);
    a.set(1, 1, 5);
    a.set(1, 2, 6);

    b.set(0, 0, 7);
    b.set(0, 1, 8);
    b.set(1, 0, 9);
    b.set(1, 1, 10);
    b.set(2, 0, 11);
    b.set(2, 1, 12);

    Matrix result = a.dot(b);

    assert(result.get(0, 0) == 58);
    assert(result.get(0, 1) == 64);
    assert(result.get(1, 0) == 139);
    assert(result.get(1, 1) == 154);
}

void testTranspose() {
    Matrix a(2, 3);

    a.set(0, 0, 1);
    a.set(0, 1, 2);
    a.set(0, 2, 3);
    a.set(1, 0, 4);
    a.set(1, 1, 5);
    a.set(1, 2, 6);

    Matrix result = a.transpose();

    assert(result.getRow() == 3);
    assert(result.getCol() == 2);
    assert(result.get(2, 1) == 6);
}

void testError() {
    bool hasError = false;

    try {
        Matrix a(2, 2);
        Matrix b(3, 3);
        Matrix result = a.add(b);
    } catch (invalid_argument&) {
        hasError = true;
    }

    assert(hasError);
}

void testDeterminant() {
    Matrix matrix(3, 3);

    matrix.set(0, 0, 6);
    matrix.set(0, 1, 1);
    matrix.set(0, 2, 1);
    matrix.set(1, 0, 4);
    matrix.set(1, 1, -2);
    matrix.set(1, 2, 5);
    matrix.set(2, 0, 2);
    matrix.set(2, 1, 8);
    matrix.set(2, 2, 7);

    MatrixSolver solver;
    assert(solver.determinant(matrix) == -306);
}

void testInverse() {
    Matrix matrix(2, 2);

    matrix.set(0, 0, 4);
    matrix.set(0, 1, 7);
    matrix.set(1, 0, 2);
    matrix.set(1, 1, 6);

    MatrixSolver solver;
    Matrix result = solver.inverse(matrix);

    assert(abs(result.get(0, 0) - 0.6) < 0.000001);
    assert(abs(result.get(0, 1) + 0.7) < 0.000001);
    assert(abs(result.get(1, 0) + 0.2) < 0.000001);
    assert(abs(result.get(1, 1) - 0.4) < 0.000001);
}

void testSolve() {
    Matrix matrix(2, 2);
    vector<double> answer(2);

    matrix.set(0, 0, 2);
    matrix.set(0, 1, 1);
    matrix.set(1, 0, 1);
    matrix.set(1, 1, -1);
    answer[0] = 5;
    answer[1] = 1;

    MatrixSolver solver;
    vector<double> result = solver.solve(matrix, answer);

    assert(abs(result[0] - 2) < 0.000001);
    assert(abs(result[1] - 1) < 0.000001);
}

void testSolverError() {
    Matrix matrix(2, 2);

    matrix.set(0, 0, 1);
    matrix.set(0, 1, 2);
    matrix.set(1, 0, 2);
    matrix.set(1, 1, 4);

    MatrixSolver solver;
    bool hasError = false;

    try {
        Matrix result = solver.inverse(matrix);
    } catch (invalid_argument&) {
        hasError = true;
    }

    assert(hasError);
}

int main() {
    testAdd();
    testSub();
    testDot();
    testTranspose();
    testError();
    testDeterminant();
    testInverse();
    testSolve();
    testSolverError();
    cout << "Matrix tests passed!" << endl;
    return 0;
}
