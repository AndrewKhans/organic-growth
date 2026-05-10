# Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
# Licensed under the zlib/libpng license
# Based on CMakeLists.txt template from Ramon
# Modifications made by Andrew Khanschassoff

cmake_minimum_required(VERSION 3.5)
project(organic-growth CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Adding Raylib (locally)
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/raylib/")
# file(GLOB_RECURSE RAYLIB_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/raylib/src/*.c")
# set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/source/")
# add_library(raylib RAYLIB_SOURCES)

# Adding Raylib
# include(FetchContent)
# set(FETCHCONTENT_QUIET FALSE)
# set(BUILD_EXAMPLES OFF)
# FetchContent_Declare(
#     raylib
#     GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
#     GIT_TAG "master"
#     GIT_PROGRESS TRUE
# )
# FetchContent_MakeAvailable(raylib)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/source/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/source/")

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# add_compile_options(-O3)
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()