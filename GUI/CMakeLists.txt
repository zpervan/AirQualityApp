cmake_minimum_required(VERSION 3.15)

project(AirQualityGui)

add_subdirectory(DearImgui)

add_library(AirQualityGui
        STATIC
        air_quality_gui.h
        air_quality_gui.cpp
        Components/main_menu_bar.h
        )

target_link_libraries(AirQualityGui
        PRIVATE
        ImGui
        )
