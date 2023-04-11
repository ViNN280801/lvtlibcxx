cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(lvt
    DESCRIPTION "This library will help you on a initial steps"
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-fPIC -Wall -Wpedantic -Wextra")

add_library(${PROJECT_NAME} SHARED lvt.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)
