target_sources(
  ${PROJECT_NAME}
  PRIVATE main.cpp
          gui/device_picker.h
          gui/device_picker.cpp
          gui/sna_workspace.h
          gui/sna_workspace.cpp
          imgui/imgui_component.h
          imgui/imgui_component.cpp
          imgui/imgui_disable.h
          imgui/imgui_dockspace.h
          imgui/imgui_dockspace.cpp
          imgui/imgui_functor.h
          imgui/imgui_progress.h
          imgui/imgui_window.h
          imgui/imgui_window.cpp
          radio/sdr_sink.h
          radio/sdr_sink.cpp
          radio/sdr_source.h
          radio/sdr_source.cpp
          util/config.h
          util/config.cpp
          util/event_dispatcher.h
          util/stl_helper.h
          wrapper/soapysdr_wrapper.h
          wrapper/soapysdr_wrapper.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
  target_compile_options(
    ${PROJECT_NAME} PRIVATE "/experimental:external" "/external:W0"
                            "/external:anglebrackets" "/W4" "/WX")
  target_link_options(
    ${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELWITHDEBINFO>:/INCREMENTAL:NO>"
    "$<$<CONFIG:RELWITHDEBINFO>:/PROFILE>")
else()
  target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-Wextra" "-Werror")
endif()

set_target_properties(
  ${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                             ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
