cmake_minimum_required(VERSION 3.10)
project(ObjectParser)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add directory where FindGeographicLib.cmake is located
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/share/cmake/geographiclib")

# Use the FindGeographicLib module
find_package(GeographicLib REQUIRED)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add executable
add_executable(object_parser
    main.cpp
    Object.cpp
    ObjectParser.cpp
    Grid.cpp
)

# Include directories
target_include_directories(object_parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ✅ Correct: Link against GeographicLib
target_link_libraries(object_parser PRIVATE GeographicLib)

# Warnings
if(MSVC)
    target_compile_options(object_parser PRIVATE /W4)
else()
    target_compile_options(object_parser PRIVATE -Wall -Wextra)
endif()

# Copy input file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/objects.txt
               ${CMAKE_CURRENT_BINARY_DIR}/objects.txt COPYONLY)

message(STATUS "Configuration complete, build with: cmake --build .")
