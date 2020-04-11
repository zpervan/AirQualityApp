project(DearImGui CXX)

# Specify header files
set(HEADERS
        imconfig.h
        imgui.h
        imgui_impl_glfw.h
        imgui_impl_opengl3.h
        imgui_internal.h
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h
        )

# Specify source files
set(SOURCES
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_impl_glfw.cpp
        imgui_impl_opengl3.cpp
        imgui_widgets.cpp
        )

# Create a library
add_library(DearImGui
        STATIC
        ${HEADERS}
        ${SOURCES}
        )

# In order to work with DearImGui, link it with graphics libraries
target_link_libraries(DearImGui
        PRIVATE
        glfw
        GLEW
        GLU
        GL
        )
