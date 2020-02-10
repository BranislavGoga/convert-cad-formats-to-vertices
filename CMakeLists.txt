cmake_minimum_required(VERSION 3.13)

project(ModelConverter)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(OCE REQUIRED)

add_executable(ModelConverter
    main.cpp
)

target_include_directories(ModelConverter PRIVATE
    ${OCE_INCLUDE_DIRS}
    )

target_link_libraries(ModelConverter PUBLIC
    ${OCE_LIBRARIES}
    )
