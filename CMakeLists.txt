
cmake_minimum_required(VERSION 3.10)

project(GeneticScheduling)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(matplotplusplus)

include_directories(include tests)

add_executable(main main.cpp src/Config.cpp src/GA.cpp)
add_executable(test test.cpp src/Config.cpp src/GA.cpp)

target_link_libraries(main PUBLIC matplot)