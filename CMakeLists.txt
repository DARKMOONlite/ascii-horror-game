cmake_minimum_required(VERSION 3.16)
project(AsciiArtGenerator VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
# pkg_check_modules(OPENCV REQUIRED opencv4)

# Create executable
add_executable(ascii_art_generator
    src/main.cpp
    src/ascii_generator.cpp
    src/color_utils.cpp
)

# Include directories
target_include_directories(ascii_art_generator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OPENCV_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(ascii_art_generator PRIVATE
    ${OPENCV_LIBRARIES}
)

# Compiler flags
target_compile_options(ascii_art_generator PRIVATE
    ${OPENCV_CFLAGS_OTHER}
    -Wall -Wextra -O3
)

# Install target
install(TARGETS ascii_art_generator
    RUNTIME DESTINATION bin
)
