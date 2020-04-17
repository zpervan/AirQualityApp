project(AirQualityGui)

add_subdirectory(Utility)

# TODO: Create set variables for header and src files
add_library(AirQualityGui
        STATIC
        air_quality_gui.h
        air_quality_gui.cpp
        Components/main_menu_bar.h
        Components/window.h
        Components/config.h
        Components/process_data.h
        Components/data.h
        )

target_link_libraries(AirQualityGui
        PRIVATE
        DearImGui
        DataScraper
        JsonParser
        DateTime
        pthread
        )
