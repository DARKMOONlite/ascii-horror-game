cmake_minimum_required(VERSION 3.16)
project(AsciiArtGenerator VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
# find_package(OpenCV REQUIRED)

include(FetchContent)

find_package(OpenCV)
if(NOT OpenCV_FOUND)
    include(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FetchOpenCV.cmake
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/SetOpenCVConfigSupportVars.cmake
    )
    fetch_opencv(
    CONFIG
        BUILD_opencv_gapi OFF
        BUILD_PERF_TESTS OFF
        BUILD_TESTS OFF
        BUILD_opencv_apps OFF
        BUILD_opencv_world OFF
        WITH_OPENGL OFF
        # WITH_CUDA OFF
        WITH_OPENCL OFF
    )
endif()

FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

# Create executable
add_executable(ascii_art_generator
    "src/main.cpp"
    "src/ascii_image/ascii_generator.cpp"
    "src/ascii_image/color_utils.cpp"
    "src/ascii_image/ascii_image.cpp"
    "src/game_menu.cpp"
    "src/ftxui_ansi/ansi_text.cpp"
    
)

# Include directories
target_include_directories(ascii_art_generator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ascii_image
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ftxui_ansi
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(ascii_art_generator PRIVATE
    ${OpenCV_LIBRARIES}
    ftxui::component
    ftxui::dom
    ftxui::screen
)

# Compiler flags
target_compile_options(ascii_art_generator PRIVATE
    -Wall -Wextra -O3
)

# Install target
install(TARGETS ascii_art_generator
    RUNTIME DESTINATION bin
)

#-------------- MENU TEST ---------------------

add_executable(menu_test
    "src/menu_test.cpp"
    "src/ascii_image/ascii_generator.cpp"
    "src/ascii_image/color_utils.cpp"
    "src/ascii_image/ascii_image.cpp"
    "src/game_menu.cpp"
    "src/ftxui_ansi/ansi_text.cpp"
)
# Include directories
target_include_directories(menu_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ascii_image
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ftxui_ansi
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(menu_test PRIVATE
    ${OpenCV_LIBRARIES}
    ftxui::component
    ftxui::dom
    ftxui::screen
)

# Compiler flags
target_compile_options(menu_test PRIVATE
    -Wall -Wextra -O3
)

# Install target
install(TARGETS menu_test
    RUNTIME DESTINATION bin
)

#-------------- ANSI TEST ---------------------

add_executable(ansi_test
    "src/ftxui_ansi/ansi_test.cpp"
    "src/ascii_image/color_utils.cpp"
    "src/ascii_image/ascii_image.cpp"
    "src/ascii_image/ascii_generator.cpp"
    "src/ftxui_ansi/ansi_text.cpp"
)

target_include_directories(ansi_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ascii_image
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ftxui_ansi
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(ansi_test PRIVATE
    ${OpenCV_LIBRARIES}
    ftxui::component
    ftxui::dom
    ftxui::screen
)

target_compile_options(ansi_test PRIVATE
    -Wall -Wextra -O3
)

install(TARGETS ansi_test
    RUNTIME DESTINATION bin
)