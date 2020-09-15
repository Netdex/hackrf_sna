cmake_minimum_required(VERSION 3.16)
project(hackrf_sna)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_TESTING OFF CACHE BOOL "")

add_subdirectory(src)
add_subdirectory(vendor)
