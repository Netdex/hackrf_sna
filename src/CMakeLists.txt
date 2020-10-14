target_sources(
  ${PROJECT_NAME}
  PRIVATE main.cpp
          gui/device_picker.h
          gui/device_picker.cpp
          gui/imgui_component.h
          gui/imgui_component.cpp
          gui/imgui_disable.h
          gui/imgui_dockspace.h
          gui/imgui_dockspace.cpp
          gui/imgui_functor.h
          gui/imgui_progress.h
          gui/imgui_window.h
          gui/imgui_window.cpp
          gui/sna_workspace.h
          gui/sna_workspace.cpp
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
