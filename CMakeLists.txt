cmake_minimum_required(VERSION 3.13)

project(ModelConverter)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
#include(conanbuildinfo.cmake)
#conan_basic_setup()

find_package(OpenCascade REQUIRED)

add_executable(ModelConverter
    main.cpp
)

target_include_directories(ModelConverter PRIVATE
    ${OpenCascade_INCLUDE_DIRS}
    )

target_link_libraries(ModelConverter PUBLIC
    ${OpenCascade_LIBRARIES}
    )

if(WIN32)
    set(OpenCascade_BINDIR "${OpenCascade_INCLUDE_DIRS}/../bin")

    add_custom_command(TARGET ModelConverter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${OpenCascade_BINDIR}
        $<TARGET_FILE_DIR:ModelConverter>
        )
endif(WIN32)