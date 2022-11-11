#!/bin/bash
DIR=`dirname $0`

g++ -O3 -std=c++11 -fopenmp -I"$DIR"/include "$DIR"/main.cpp "$DIR"/src/MatrixMultiplication.cpp -o ./build/matrix_mul_O3

./build/matrix_mul_O3
#g++-8 -O0 -std=c++14 -fopenmp -I"$DIR"/include "$DIR"/main.cpp "$DIR"/src/MatrixMultiplication.cpp -o ./build/matrix_mul_O0
