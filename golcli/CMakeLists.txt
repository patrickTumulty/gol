
cmake_minimum_required(VERSION 3.10)

project(golcli)

file(GLOB SOURCES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC gol)

