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
