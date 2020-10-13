set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")

set(VENDOR_DIR ${PROJECT_SOURCE_DIR}/vendor)

# glfw
set(GLFW_BUILD_DOCS
    OFF
    CACHE INTERNAL "")
set(GLFW_BUILD_TESTS
    OFF
    CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES
    OFF
    CACHE INTERNAL "")
set(GLFW_INSTALL
    OFF
    CACHE INTERNAL "")
add_subdirectory(glfw)
target_include_directories(glfw SYSTEM PUBLIC glfw/include/)
target_compile_definitions(glfw INTERFACE -DGLFW_INCLUDE_NONE)

# glad
add_library(glad glad/include/glad/glad.h glad/src/glad.c)
target_include_directories(glad SYSTEM PUBLIC glad/include/)

# imgui
add_library(
  imgui
  imgui/imgui.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp
  imgui/imgui_widgets.cpp imgui/examples/imgui_impl_opengl3.cpp
  imgui/examples/imgui_impl_glfw.cpp)
target_include_directories(imgui SYSTEM PUBLIC imgui/ imgui/examples/)
target_compile_definitions(imgui PUBLIC -DIMGUI_IMPL_OPENGL_LOADER_GLAD)
target_link_libraries(imgui PUBLIC glfw glad)

# glog
set(WITH_GFLAGS
    OFF
    CACHE INTERNAL "")
set(WITH_UNWIND
    OFF
    CACHE INTERNAL "")
add_subdirectory(glog)

# span-lite
add_library(span-lite INTERFACE)
target_include_directories(span-lite SYSTEM INTERFACE span-lite/include/)

# toml11
add_library(toml11 INTERFACE)
target_include_directories(toml11 SYSTEM INTERFACE toml11/)

# eventpp
add_library(eventpp INTERFACE)
target_include_directories(eventpp SYSTEM INTERFACE eventpp/include)

# implot
add_library(implot implot/implot.cpp implot/implot_demo.cpp
                   implot/implot_items.cpp)
target_include_directories(implot SYSTEM PUBLIC implot/)
target_link_libraries(implot PUBLIC imgui)

# cppzmq
set(CPPZMQ_BUILD_TESTS
    OFF
    CACHE INTERNAL "")
set(ZMQ_BUILD_TESTS
    OFF
    CACHE INTERNAL "")
set(ENABLE_DRAFTS
    OFF
    CACHE INTERNAL "")
set(ENABLE_CURVE
    OFF
    CACHE INTERNAL "")
set(WITH_DOCS
    OFF
    CACHE INTERNAL "")
set(WITH_PERF_TOOL
    OFF
    CACHE INTERNAL "")
add_subdirectory(libzmq)
add_subdirectory(cppzmq)

# SoapySDR
if(WIN32)
  # Set common path of PothosSDR for locating SoapySDR on Windows
  set(POTHOS_SDR_ROOT
      "C:/Program Files/PothosSDR"
      CACHE STRING "")
  set(POTHOS_SDR_INCLUDE
      ${POTHOS_SDR_ROOT}/include
      CACHE INTERNAL "")
  set(POTHOS_SDR_LIB
      ${POTHOS_SDR_ROOT}/lib
      CACHE INTERNAL "")
  set(SoapySDR_DIR
      ${POTHOS_SDR_ROOT}/cmake
      CACHE INTERNAL "")
endif()
find_package(SoapySDR "0.4.0" CONFIG REQUIRED)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC glfw
         glad
         imgui
         implot
         glog
         span-lite
         toml11
         eventpp
         cppzmq
         SoapySDR)
