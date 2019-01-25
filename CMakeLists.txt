cmake_minimum_required(VERSION 3.5)
project(FingerPrint CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-ofast ${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

get_filename_component(LibFP_INCLUDE_DIRECTORY include DIRECTORY)

include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(docs)

set(LIBS
    PUBLIC
    ${OpenCV_LIBS}
    FingerPrint)

add_subdirectory(demo)

add_executable(main ./demo/main.cpp)
add_executable(main-2 ./demo/main-2.cxx)

target_link_libraries(main ${LIBS})

target_include_directories(main
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(main-2 ${LIBS})

target_include_directories(main-2
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)
