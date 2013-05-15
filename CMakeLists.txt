project(GomuEngine)
cmake_minimum_required(VERSION 2.8)

# Find required libraries
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# Add additional flags to GCC based compilers
if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions("-std=c++11 -pedantic -Wall -Wextra")
endif ()

# Include the right directories where the headers are found
include_directories(
${SDL_INCLUDE_DIR}
${GLEW_INCLUDE_DIR}
${OPENGL_INCLUDE_DIR}
)

# Add sources and executable

add_executable(${PROJECT_NAME}
DrawText.cpp
DrawText.hpp
main.cpp
Window.cpp
Window.hpp
)

# Link libraries
TARGET_LINK_LIBRARIES(GomuEngine
${SDL_LIBRARY}
${SDLIMAGE_LIBRARY}
${SDLTTF_LIBRARY}
${GLEW_LIBRARY}
${OPENGL_LIBRARY}
)
