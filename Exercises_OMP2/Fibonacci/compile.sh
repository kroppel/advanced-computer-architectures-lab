#!/bin/bash
DIR=`dirname $0`

g++-9 -std=c++11 -fopenmp "$DIR"/Fibonacci.cpp -o fibonacci

