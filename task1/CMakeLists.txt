cmake_minimum_required(VERSION 3.20)

project(Integrals LANGUAGES CXX)

find_package(OpenMP REQUIRED)
set(CMAKE_CXX_STANDARD 20)

add_executable(my_programm main.cpp integration.cpp integration.hpp)
target_link_libraries(my_programm PRIVATE OpenMP::OpenMP_CXX)

