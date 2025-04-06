cmake_minimum_required(VERSION 3.10)
project(ObjectParser) # You might want to rename this project if it's now SLAM

set(CMAKE_CXX_STANDARD 23) # Note: C++23 might be ambitious; C++17 or C++20 are more common. Check compiler support.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Removed ---
# No longer need to find the package or specify a module path
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/share/cmake/geographiclib")
# find_package(GeographicLib REQUIRED)
# --- Removed ---

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# --- Added ---
# Add the GeographicLib source directory. CMake will find its CMakeLists.txt
# and build it as part of this project.
# Ensure the path matches where you added the submodule.
add_subdirectory(external/geographiclib)
# --- Added ---

# Add executable
add_executable(object_parser # Consider renaming this executable if it's the main SLAM program
    main.cpp
    Object.cpp
    ObjectParser.cpp
    Grid.cpp
)

# Include directories
# Add GeographicLib's include directory. When built via add_subdirectory,
# its include directories are often automatically propagated via the target,
# but explicitly adding can sometimes be necessary or clearer depending on the library.
# The target_link_libraries line below *should* handle this, but keep this comment in mind if you have include errors.
# target_include_directories(object_parser PRIVATE external/geographiclib/include) # Usually not needed if linking works
target_include_directories(object_parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


# Link against the target defined by GeographicLib's CMakeLists.txt
# When built via add_subdirectory, the target is typically the library name itself.
# GeographicLib creates a target named 'GeographicLib'.
target_link_libraries(object_parser PRIVATE GeographicLib)
# Note: If you encounter linking issues, GeographicLib might export a namespaced
# target like GeographicLib::GeographicLib. Try that if 'GeographicLib' doesn't work.
# target_link_libraries(object_parser PRIVATE GeographicLib::GeographicLib)


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