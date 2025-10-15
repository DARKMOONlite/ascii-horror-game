cmake_minimum_required(VERSION 3.15)
project(AsciiImageConverter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create the main executable
add_executable(ascii_converter
    src/main.cpp
    src/image_processor.cpp
    src/ascii_converter.cpp
)

target_include_directories(ascii_converter PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Enable warnings
if(MSVC)
    target_compile_options(ascii_converter PRIVATE /W4)
else()
    target_compile_options(ascii_converter PRIVATE -Wall -Wextra -Wpedantic)
endif()
