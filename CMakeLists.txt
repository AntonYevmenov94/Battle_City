cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME Battle_City)

project(Battle_City)

add_executable(Battle_City src/main.cpp src/Renderer/ShaderProgramm.h src/Renderer/ShaderProgramm.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries (Battle_City glfw)

add_subdirectory(external/glad)
target_link_libraries (Battle_City glad)