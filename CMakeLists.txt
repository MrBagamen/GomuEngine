project(GomuEngine)
cmake_minimum_required(VERSION 2.8)

# Find required libraries
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
"/usr/include/SDL2"
${GLEW_INCLUDE_DIR}
${OPENGL_INCLUDE_DIR}
)

set(HEADERS
include/gomu/Text.hpp
include/gomu/Sprite.hpp
include/gomu/State.hpp
include/gomu/Application.hpp
include/gomu/input.hpp
include/gomu/Font.hpp
include/gomu/Texture.hpp
include/gomu/Sound.hpp
)

# Add library
add_library(GomuEngine
src/Text.cpp
src/Sprite.cpp
src/Application.cpp
src/input.cpp
src/Font.cpp
src/Texture.cpp
src/Sound.cpp
${HEADERS}
)

target_link_libraries(GomuEngine
SDL2 SDL2_image SDL2_ttf SDL2_mixer
${GLEW_LIBRARY}
${OPENGL_LIBRARY}
)

# Add Tests
function(addTest name)
    add_executable(${name} tests/${name}.cpp)
    target_link_libraries(${name} GomuEngine)
endfunction()

addTest(Text)
addTest(Sticks)

# Installation
install(FILES ${HEADERS} DESTINATION include/gomu)
install(TARGETS GomuEngine
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib
)
