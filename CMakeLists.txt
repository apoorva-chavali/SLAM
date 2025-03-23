cmake_minimum_required(VERSION 3.10)
project(ObjectParser)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for all configurations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

# Add executable
add_executable(object_parser
    main.cpp
    Object.cpp
    ObjectParser.cpp
    Grid.cpp
)

# Include directories
target_include_directories(object_parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Enable warnings
if(MSVC)
    target_compile_options(object_parser PRIVATE /W4)
else()
    target_compile_options(object_parser PRIVATE -Wall -Wextra)
endif()

# Copy the objects.txt file to the build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/objects.txt
               ${CMAKE_CURRENT_BINARY_DIR}/objects.txt COPYONLY)

# Print success message
message(STATUS "Configuration complete, build with: cmake --build .")