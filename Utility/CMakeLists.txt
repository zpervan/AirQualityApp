project(Utility)

add_library(DataScraper
        STATIC
        DataScraper/data_scraper.h
        DataScraper/data_scraper.cpp
        )

target_link_libraries(DataScraper
        PRIVATE
        curl
        )

###### TESTING ######

add_subdirectory(ThirdParty/GoogleTest)

enable_testing()

# Add test executables
add_executable(DataScraperTest
        DataScraper/Test/data_scraper_test.cpp
        )

# Link needed libraries
target_link_libraries(DataScraperTest
        DataScraper
        gtest
        gtest_main
        )

add_test(TestAll
        DataScraperTest
        )
