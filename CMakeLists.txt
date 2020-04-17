cmake_minimum_required(VERSION 3.12)
project(AirQualityApp CXX)

# Define C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the GUI subfolder
add_subdirectory(GUI)

# Compiling the runner executable
add_executable(AirQualityApp runner.cpp)

# Linking needed libraries with the main executable
target_link_libraries(AirQualityApp
        PRIVATE
        AirQualityGui
        pthread
        )
