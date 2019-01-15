cmake_minimum_required(VERSION 2.8.11)
project(FingerPrint)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

get_filename_component(LibFP_INCLUDE_DIRECTORY include DIRECTORY)

add_subdirectory(src)
add_subdirectory(docs)
include_directories(include)

add_executable(main ./demo/main.cpp)
add_executable(starter-2 ./demo/starter-2.cxx)

set(LIBS
    PUBLIC
    ${OpenCV_LIBS}
    libFingerPrint)

target_link_libraries(main ${LIBS})

target_include_directories(main
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(starter-2 ${LIBS})

target_include_directories(starter-2
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)
