project(Utility)

# Create libraries
add_library(DataScraper
        STATIC
        DataScraper/data_scraper.h
        DataScraper/data_scraper.cpp
        )

target_link_libraries(DataScraper
        PRIVATE
        curl
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
add_executable(DataScraperTest
        DataScraper/Test/data_scraper_test.cpp
        )

add_executable(JsonParserTest
        JsonParser/Test/json_parser_test.cpp
        )

add_executable(LinearRegressionTest
        Algorithms/Test/linear_regression_test.cpp
        )

# Link libraries needed for testing
set(GTest_Libs gtest gtest_main)


target_link_libraries(DataScraperTest
        DataScraper
        ${GTest_Libs}
        )

target_link_libraries(JsonParserTest
        JsonParser
        ${GTest_Libs}
        )

target_link_libraries(LinearRegressionTest
        LinearRegression
        ${GTest_Libs}
        )

# Creates a named test suite for given tests
add_test(TestAll
        DataScraperTest
        JsonParserTest
        LinearRegressionTest
        )
