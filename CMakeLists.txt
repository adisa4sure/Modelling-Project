cmake_minimum_required(VERSION 2.8.11)
project(FingerPrint)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(src)
add_subdirectory(docs)
add_subdirectory(demo)
