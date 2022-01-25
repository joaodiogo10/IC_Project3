cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
project(PartB_2)

add_executable(findlang ../PartA/FCM.cpp findlang.cpp)
target_include_directories(findlang PRIVATE ../PartA)
target_link_directories(findlang PRIVATE ../PartA)