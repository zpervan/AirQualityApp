#!/usr/bin/env bash

display_help()
{
    echo "A script to build and run the AirQuality application with various options"
    echo -e "To run the standalone application, just run this script \e[4mwithout\e[0m any flags!"
    echo
    echo "Usage: $0 [option...] {configure|build|test}"
    echo
    echo "-h, --help        Displays the help message"
    echo "-c, --configure   Configure the project in release mode"
    echo "-b, --build       Build the project in release mode"
    echo "-t, --test        Run tests"
    echo "-c, --clean       Clean the generated files inside the build folder"
}

position_to_working_directory()
{
    DIR="${BASH_SOURCE%/*}"

    if [[ "$DIR" == "." ]];
        then cd ..;
    fi

    echo "-- Current working directory: $PWD"
}

configure_release()
{
    position_to_working_directory
    echo "-- Configuring build..."
    rm -rf build && mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    echo -e "-- Configuring build... \e[32mDONE!\e[0m"
}

build()
{
    echo "-- Building project..."
    make -j2
    echo -e "-- Building project... \e[32mDONE!\e[0m"
}

configure_and_build_release()
{
    configure_release
    build
}

run_application()
{
    configure_release
    build

    echo "Running application..."
    ./AirQualityApp
    echo -e "Application \e[32mterminated\e[0m"
}

run_tests()
{
    configure_release
    build

    echo "Running tests..."
    cd GUI/Utility/

    ./AirMeasurementFetcherTest --gtest_color=yes
    ./DateTimeTest --gtest_color=yes
    ./JsonParserTest --gtest_color=yes
    ./LinearRegressionTest --gtest_color=yes
    echo -e "Running tests...\e[32mDONE!\e["
}

clean_build()
{
    position_to_working_directory
    cd build
    rm -rf .
}

case "$1" in
    "-h" | "--help" ) display_help;;
    "-c" | "--configure" ) configure_release;;
    "-b" | "--build" ) configure_and_build_release;;
    "-t" | "--test" ) run_tests;;
    "-c" | "--clean" ) clean_build;;
    *) run_application ;;
esac
