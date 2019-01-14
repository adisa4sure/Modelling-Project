cmake_minimum_required(VERSION 2.8.11)
project(FingerPrint)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(OpenCV REQUIRED)

add_subdirectory(src)
add_subdirectory(docs)
add_subdirectory(include)

add_executable(main ./demo/main.cpp)

set(LIBS
    PUBLIC
    ${OpenCV_LIBS}
  libFingerPrintsrc)

target_link_libraries(main ${LIBS})

target_include_directories(main
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)
