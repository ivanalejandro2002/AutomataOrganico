cmake_minimum_required(VERSION 3.20)

project(AUTOMATA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL_X11_XSCRNSAVER OFF CACHE BOOL "" FORCE)
set(SDL_X11_XTEST OFF CACHE BOOL "" FORCE)
set(SDL_X11_XFIXES OFF CACHE BOOL "" FORCE)
set(SDL_X11_XCURSOR OFF CACHE BOOL "" FORCE)
set(SDL_X11_XSHAPE OFF CACHE BOOL "" FORCE)

add_subdirectory(external/SDL)

find_package(OpenGL REQUIRED)

add_library(glad
    external/glad/src/gl.c
)

target_include_directories(glad PUBLIC
    external/glad/include
)

#ADD SUBDIRECTORY SRC/MODULO
add_subdirectory(src/CG)

add_executable(AUTOMATA
    src/main.cpp
)

target_link_libraries(AUTOMATA PRIVATE
    SDL3::SDL3
    glad
    CG
    OpenGL::GL
)

if(UNIX AND NOT APPLE)
    target_link_libraries(AUTOMATA PRIVATE pthread dl)
endif()