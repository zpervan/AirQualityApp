#!/usr/bin/env bash

echo "Triggering build configuration..."

rm -rf build && mkdir build && cd build
cmake ..

echo "Triggering build configuration... DONE!"

echo "Building project..."

make

echo "Building project... DONE!"

echo "Running tests..."
cd GUI/Utility/

./AirMeasurementFetcherTest --gtest_color=yes
./DateTimeTest --gtest_color=yes
./JsonParserTest --gtest_color=yes
./LinearRegressionTest --gtest_color=yes

echo "Running tests...DONE!"
