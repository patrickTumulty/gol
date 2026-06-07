
cmake_minimum_required(VERSION 3.10)

project(gol)

file(GLOB SOURCES 
   src/gol.cpp
   src/gol_utils.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src)

add_executable(${PROJECT_NAME}_tests tests/gol_tests.cpp)

target_link_libraries(${PROJECT_NAME}_tests PUBLIC gol doctest::doctest)


