set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw glfw)
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

if(WIN32)
    set(LIBUSB_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/libusb-1.0.23-win32/include/libusb-1.0)
    set(THREADS_PTHREADS_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/pthreads-2.9.1-win32/include)
    if("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "Win32")
        set(LIBUSB_LIBRARIES ${PROJECT_SOURCE_DIR}/vendor/libusb-1.0.23-win32/MS32/dll/libusb-1.0.lib)
        set(THREADS_PTHREADS_WIN32_LIBRARY ${PROJECT_SOURCE_DIR}/vendor/pthreads-2.9.1-win32/lib/x86/pthreadVC2.lib)
    elseif("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "x64")
        set(LIBUSB_LIBRARIES ${PROJECT_SOURCE_DIR}/vendor/libusb-1.0.23-win32/MS64/dll/libusb-1.0.lib)
        set(THREADS_PTHREADS_WIN32_LIBRARY ${PROJECT_SOURCE_DIR}/vendor/pthreads-2.9.1-win32/lib/x64/pthreadVC2.lib)
    endif()
endif()
add_subdirectory(hackrf/host/libhackrf libhackrf)
target_include_directories(hackrf SYSTEM PUBLIC hackrf/host/libhackrf/src/)

# Dummy targets for copying DLLs on Windows
if(WIN32)
    add_custom_target(libusb-win32)
    add_custom_target(pthreads-win32)
    if("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "Win32")
        add_custom_command(TARGET libusb-win32 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${PROJECT_SOURCE_DIR}/vendor/libusb-1.0.23-win32/MS32/dll/libusb-1.0.dll
                "$<TARGET_FILE_DIR:hackrf>")
        add_custom_command(TARGET pthreads-win32 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${PROJECT_SOURCE_DIR}/vendor/pthreads-2.9.1-win32/dll/x32/pthreadVC2.dll
                "$<TARGET_FILE_DIR:hackrf>")
    elseif("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "x64")
        add_custom_command(TARGET libusb-win32 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${PROJECT_SOURCE_DIR}/vendor/libusb-1.0.23-win32/MS64/dll/libusb-1.0.dll
                "$<TARGET_FILE_DIR:hackrf>")
        add_custom_command(TARGET pthreads-win32 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${PROJECT_SOURCE_DIR}/vendor/pthreads-2.9.1-win32/dll/x64/pthreadVC2.dll
                "$<TARGET_FILE_DIR:hackrf>")
    endif()
endif()
