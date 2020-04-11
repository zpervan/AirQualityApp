project(AirQualityGui)

add_subdirectory(Utility)

add_library(AirQualityGui
        STATIC
        air_quality_gui.h
        air_quality_gui.cpp
        Components/main_menu_bar.h
        Components/window.h
        Components/config.h
        )

target_link_libraries(AirQualityGui
        PRIVATE
        DearImGui
        )
