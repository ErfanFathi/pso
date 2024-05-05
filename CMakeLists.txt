cmake_minimum_required(VERSION 3.15)
project(pso)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(pso Main.cpp PSO.h Environment.h)
target_link_libraries(pso ${OpenCV_LIBS})