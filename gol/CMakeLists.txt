
cmake_minimum_required(VERSION 3.10)

project(gol)

file(GLOB SOURCES src/gol.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src)


