project(GomuEngine)
cmake_minimum_required(VERSION 2.8)

# Find required libraries
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

aux_source_directory(. SRC_LIST)
add_definitions(-std=c++11 -pedantic -Wall -Wextra)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# Link libraries
TARGET_LINK_LIBRARIES(GomuEngine
${SDL_LIBRARY}
${SDLIMAGE_LIBRARY}
${SDLTTF_LIBRARY}
${GLEW_LIBRARY}
${OPENGL_LIBRARY}
)
