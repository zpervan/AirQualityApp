project(Utility)

# Create libraries
add_library(AirMeasurementFetcher
        STATIC
        AirMeasurementFetcher/air_measurement_fetcher.h
        AirMeasurementFetcher/air_measurement_fetcher.cpp
        )

target_link_libraries(AirMeasurementFetcher
        PRIVATE
        curl
        )

add_library(DateTime
        STATIC
        DateTime/date_time.h
        DateTime/date_time.cpp
        )

add_library(JsonParser
        STATIC
        JsonParser/json_parser.cpp
        JsonParser/json_parser.h
        DataTypes/data_types.h
        )

add_library(LinearRegression
        STATIC
        Algorithms/linear_regression.cpp
        Algorithms/linear_regression.h
        )

###### TESTING ######
add_subdirectory(ThirdParty)

enable_testing()

# Add test executables
add_executable(AirMeasurementFetcherTest
        AirMeasurementFetcher/Test/air_measurement_fetcher_test.cpp
        )

add_executable(DateTimeTest
        DateTime/Test/date_time_test.cpp
        )

add_executable(JsonParserTest
        JsonParser/Test/json_parser_test.cpp
        )

add_executable(LinearRegressionTest
        Algorithms/Test/linear_regression_test.cpp
        )

# Link libraries needed for testing
set(GTest_Libs
        gtest
        gtest_main
        )


target_link_libraries(AirMeasurementFetcherTest
        AirMeasurementFetcher
        DateTime
        ${GTest_Libs}
        )

target_link_libraries(DateTimeTest
        DateTime
        ${GTest_Libs}
        )

target_link_libraries(JsonParserTest
        JsonParser
        DateTime
        ${GTest_Libs}
        )

target_link_libraries(LinearRegressionTest
        LinearRegression
        ${GTest_Libs}
        )

# Creates a named test suite for given tests
add_test(TestAll
        AirMeasurementFetcherTest
        DataTimeTest
        JsonParserTest
        LinearRegressionTest
        )
