cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
project(PartA)

add_executable(testFCM testFCM.cpp FCM.cpp)
target_include_directories(testFCM PRIVATE classes)
target_link_directories(testFCM PRIVATE classes)

add_executable(loadFile loadFile.cpp FCM.cpp)
target_include_directories(loadFile PRIVATE classes)
target_link_directories(loadFile PRIVATE classes)