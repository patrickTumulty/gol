
cmake_minimum_required(VERSION 3.10)

project(golcli)

file(GLOB SOURCES src/main.cpp)

find_package(Curses REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CURSES_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC gol ${CURSES_LIBRARIES})

