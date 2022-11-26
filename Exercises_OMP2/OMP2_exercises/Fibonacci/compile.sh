#!/bin/bash
DIR=`dirname $0`

g++ -std=c++11 -fopenmp -I"$DIR"/include "$DIR"/Fibonacci.cpp -o build/fibonacci
./build/fibonacci

