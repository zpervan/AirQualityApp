cmake_minimum_required(VERSION 3.15)
project(AirQualityApp CXX)

# Define C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add needed subfolders
add_subdirectory(GUI)
add_subdirectory(Utility)

# Compiling the Executable
add_executable(AirQualityApp runner.cpp)

# Linking needed libraries with the main executable
target_link_libraries(AirQualityApp
        PRIVATE
        DataScraper
        JsonParser
        AirQualityGui
        )
