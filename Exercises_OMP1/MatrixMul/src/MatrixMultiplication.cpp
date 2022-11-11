#include "MatrixMultiplication.hpp"
#include <stdio.h>
#include <omp.h>

void sequentialMatrixMatrixMul(int** A, int** B, int** C) {
    for (int col = 0; col != COLS; ++col) {
        for (int row = 0; row != ROWS; ++row) {
			int sum = 0;
			for (int k = 0; k != COLS; ++k)
				sum += A[row][k] * B[k][col];
			C[row][col] = sum;
		}
	}
}

void openmpMatrixMatrixMul(int** A, int** B, int** C) {
#pragma omp parallel for num_threads(24)
    for (int col = 0; col != COLS; ++col) {
        for (int row = 0; row != ROWS; ++row) {
            int sum = 0;
            for (int k = 0; k != COLS; ++k)
                sum += A[row][k] * B[k][col];
            C[row][col] = sum;
        }
    }
}

