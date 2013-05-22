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

# Include GomuEngine include directory
include_directories(include)

# Include the right directories where the headers are found
include_directories(
${SDL_INCLUDE_DIR}
${GLEW_INCLUDE_DIR}
${OPENGL_INCLUDE_DIR}
)

set(HEADERS
include/gomu/gomu.hpp
include/gomu/Text.hpp
include/gomu/Sprite.hpp
)

# Add library
add_library(GomuEngine
src/gomu.cpp
src/Text.cpp
src/Sprite.cpp
${HEADERS}
)

target_link_libraries(GomuEngine
${SDL_LIBRARY}
${SDLIMAGE_LIBRARY}
${SDLTTF_LIBRARY}
${GLEW_LIBRARY}
${OPENGL_LIBRARY}
)

# Add Tests
function(addTest name)
    add_executable(${name} tests/${name}.cpp)
    target_link_libraries(${name} GomuEngine)
endfunction()

addTest(Text)

# Installation
install(FILES ${HEADERS} DESTINATION include/gomu)
install(TARGETS GomuEngine
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib
)
