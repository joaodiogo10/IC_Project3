cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
project(PartA_1)

add_executable(lang ../PartA/FCM.cpp lang.cpp)
target_include_directories(lang PRIVATE ../PartA)
target_link_directories(lang PRIVATE ../PartA)