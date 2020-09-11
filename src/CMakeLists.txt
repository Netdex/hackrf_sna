set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw vendor/glfw)

file(GLOB VENDORS_SOURCES 
    ${PROJECT_SOURCE_DIR}/vendor/glad/src/glad.c
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/examples/imgui_impl_opengl3.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/examples/imgui_impl_glfw.cpp
)

file(GLOB_RECURSE PROJECT_HEADERS *.hpp)
file(GLOB_RECURSE PROJECT_SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${VENDORS_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
	${PROJECT_SOURCE_DIR}/vendor/glad/include/
	${PROJECT_SOURCE_DIR}/vendor/glfw/include/
	${PROJECT_SOURCE_DIR}/vendor/spdlog/include/
	${PROJECT_SOURCE_DIR}/vendor/span-lite/include/
	${PROJECT_SOURCE_DIR}/vendor/imgui/
	${PROJECT_SOURCE_DIR}/vendor/imgui/examples/
    ${PROJECT_SOURCE_DIR}/vendor/toml11/
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
	-DGLFW_INCLUDE_NONE
    -DIMGUI_IMPL_OPENGL_LOADER_GLAD
	-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
)

target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

if(MSVC)
	set_source_files_properties(${PROJECT_SOURCES} PROPERTIES COMPILE_FLAGS "/experimental:external /external:W0 /external:anglebrackets /W4 /WX")
	set_source_files_properties(${VENDORS_SOURCES} PROPERTIES COMPILE_FLAGS "/w")
	target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELWITHDEBINFO>:/INCREMENTAL:NO>" "$<$<CONFIG:RELWITHDEBINFO>:/PROFILE>")
else()
    target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>" "$<$<CONFIG:DEBUG>:-g>")
    set_source_files_properties(${VENDORS_SOURCES} PROPERTIES COMPILE_FLAGS "-w")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})