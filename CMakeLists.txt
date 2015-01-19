cmake_minimum_required(VERSION 2.8)
project(estimation)

set (estimation_VERSION_MAJOR 0)
set (estimation_VERSION_MINOR 0)
set (estimation_VERSION_PATCH 1)

#find_package(PkgConfig REQUIRED)
#pkg_search_module(GLFW REQUIRED glfw3)
#include_directories(${GLFW_INCLUDE_DIRS})
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules")
add_subdirectory(./glfw-3.0.4/)
include_directories(./glfw-3.0.4/include/)
find_library(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
message(STATUS "include_dirs = ${GLUT_INCLUDE_DIRS}, library = ${GLUT_LIBRARY}")
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
add_library (HelpersL helpers.c)

add_executable(Estimation estimation.c)
target_link_libraries(Estimation HelpersL glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

set(CMAKE_BUILD_TYPE Debug)
#TODO: FIGURE OUT ABOUT WARNING FOR UNINITIALIZED VARIABLE ACCESS
