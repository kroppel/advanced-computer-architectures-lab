#!/bin/bash
DIR=`dirname $0`

g++ -std=c++11 -O3 -fopenmp -I"$DIR"/include ${DIR}/RC4.cpp -o ./build/rc4
./build/rc4
