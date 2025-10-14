cmake_minimum_required(VERSION 3.10)
project(ASCIIHorrorGame VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Library source files
set(LIBRARY_SOURCES
    src/TerminalUtils.cpp
    src/Panel.cpp
    src/PanelManager.cpp
    src/ASCIIImage.cpp
    src/ASCIIVideo.cpp
)

# Create static library
add_library(ascii_display STATIC ${LIBRARY_SOURCES})

# Examples
add_executable(example_panels examples/example_panels.cpp)
target_link_libraries(example_panels ascii_display)

add_executable(example_image examples/example_image.cpp)
target_link_libraries(example_image ascii_display)

add_executable(example_video examples/example_video.cpp)
target_link_libraries(example_video ascii_display)

add_executable(example_full examples/example_full.cpp)
target_link_libraries(example_full ascii_display)

add_executable(example_procedural examples/example_procedural.cpp)
target_link_libraries(example_procedural ascii_display)
