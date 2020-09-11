set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw vendor/glfw)
target_include_directories(glfw SYSTEM PUBLIC glfw/include/)

add_library(glad glad/include/glad/glad.h glad/src/glad.c)
target_include_directories(glad SYSTEM PUBLIC glad/include/)

add_library(imgui
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/examples/imgui_impl_opengl3.cpp
    imgui/examples/imgui_impl_glfw.cpp
)
target_include_directories(imgui SYSTEM PUBLIC 
	imgui/
    imgui/examples/
)
target_compile_definitions(imgui PUBLIC
    -DIMGUI_IMPL_OPENGL_LOADER_GLAD
)
target_link_libraries(imgui PUBLIC glfw glad)

add_library(spdlog INTERFACE)
target_include_directories(spdlog SYSTEM INTERFACE spdlog/include/)

add_library(span-lite INTERFACE)
target_include_directories(span-lite SYSTEM INTERFACE span-lite/include/)

add_library(toml11 INTERFACE)
target_include_directories(toml11 SYSTEM INTERFACE toml11/)

add_library(implot
    implot/implot.cpp
    implot/implot_demo.cpp
    implot/implot_items.cpp
)
target_include_directories(implot SYSTEM PUBLIC implot/)
target_link_libraries(implot PUBLIC imgui)
