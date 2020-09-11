file(GLOB_RECURSE PROJECT_HEADERS *.hpp)
file(GLOB_RECURSE PROJECT_SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${PROJECT_NAME} PUBLIC
	-DGLFW_INCLUDE_NONE
	-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
)
target_link_libraries(${PROJECT_NAME} PUBLIC 
    glfw glad imgui implot 
    spdlog span-lite toml11 
    hackrf
)
if(WIN32)
    # These dependencies are just for copying DLLs on Windows
    add_dependencies(${PROJECT_NAME} libusb-win32 pthreads-win32)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/res/"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res/")

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/experimental:external" "/external:W0" "/external:anglebrackets" "/W4" "/WX")
	target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELWITHDEBINFO>:/INCREMENTAL:NO>" "$<$<CONFIG:RELWITHDEBINFO>:/PROFILE>")
else()
    target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>" "$<$<CONFIG:DEBUG>:-g>")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
