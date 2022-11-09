#pragma once

const int ROWS = 2*512;
const int COLS = 2*512;

void sequentialMatrixMatrixMul(int** A, int** B, int** C);

void openmpMatrixMatrixMul(int** A, int** B, int** C);

void sequentialMatrixVectorMul_v1(int** A, int** B, int** C);

void sequentialMatrixVectorMul_v2(int** A, int** B, int** C);
