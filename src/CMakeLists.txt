target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
        radio/sdr_sink.h
        radio/sdr_sink.cpp
        radio/sdr_source.h
        radio/sdr_source.cpp
        util/config.h
        util/config.cpp
        wrapper/soapysdr_wrapper.h
        wrapper/soapysdr_wrapper.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${PROJECT_NAME} PUBLIC
	-DGLFW_INCLUDE_NONE
	-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/experimental:external" "/external:W0" "/external:anglebrackets" "/W4" "/WX")
	target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELWITHDEBINFO>:/INCREMENTAL:NO>" "$<$<CONFIG:RELWITHDEBINFO>:/PROFILE>")
else()
    # glog emits some dumb warnings so we have to do this
    set_source_files_properties(${PROJECT_SOURCES} PROPERTIES COMPILE_FLAGS "-Wall" "-Wextra" "-Werror")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})