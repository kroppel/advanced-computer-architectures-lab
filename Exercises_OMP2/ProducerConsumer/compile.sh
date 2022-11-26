#!/bin/bash
DIR=`dirname $0`

rm ./build/producerconsumer
g++ -std=c++11 -fopenmp "$DIR"/ProducerConsumer.cpp -o build/producerconsumer
./build/producerconsumer
