cmake_minimum_required(VERSION 3.16)
project(hackrf_sna)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_TESTING
    OFF
    CACHE BOOL "")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_subdirectory(vendor)
add_subdirectory(src)

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res/"
          "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res/")
