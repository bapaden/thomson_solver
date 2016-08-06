#Project name
project(sngrid)

#Compiler flags
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -std=c++0x -O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}  -std=c++0x")

#Executable that calls optimization library
add_executable(generalized_thomson_problem generalized_thomson_solver.cpp)

#Install the project
install(TARGETS generalized_thomson_problem RUNTIME DESTINATION bin)
