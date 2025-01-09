cmake_minimum_required(VERSION 2.8)

project( VBROWSER )

######################################
# finds OpenGL, GLU and X11
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(GL_LIBRARY GL GLU X11)

# Force static linking for GLFW
set(GLFW_STATIC ON)  # Make sure GLFW is built statically

# Find GLFW package (if installed or available in the system)
# find_package(GLFW REQUIRED)

file(GLOB SOURCES "src/*.c" "src/ui/*.c")

include_directories(${CMAKE_SOURCE_DIR}/lib/include/glad ${CMAKE_SOURCE_DIR}/lib/include)

add_executable(vbrowser src/main.c ${SOURCES})

target_sources(vbrowser PRIVATE lib/src/glad.c)

target_link_libraries(vbrowser glfw ${GL_LIBRARY} m)

