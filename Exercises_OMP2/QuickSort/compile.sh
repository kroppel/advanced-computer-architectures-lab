#!/bin/bash
DIR=`dirname $0`

g++-9 -std=c++11 -fopenmp "$DIR"/QuickSort.cpp -o build/quicksort
./build/quicksort
