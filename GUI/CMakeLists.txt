project(AirQualityGui)

add_subdirectory(Utility)

set(Gui_Components
        Components/main_menu_bar.h
        Components/window.h
        Components/config.h
        Components/process_data.h
        Components/data.h
        )

add_library(AirQualityGui
        STATIC
        air_quality_gui.h
        air_quality_gui.cpp
        ${Gui_Components}
        )

target_link_libraries(AirQualityGui
        PRIVATE
        AirMeasurementFetcher
        DearImGui
        DateTime
        JsonParser
        LinearRegression
        pthread
        )
