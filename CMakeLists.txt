cmake_minimum_required(VERSION 2.8.11)
project(FingerPrint)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(OpenCV REQUIRED)
find_package(Doxygen)

include_directories(include)

add_subdirectory(src)
add_subdirectory(docs)
add_subdirectory(demo)

set(LIBS
    PUBLIC
    ${OpenCV_LIBS}
    FingerPrint)

add_executable(main ./demo/main.cpp)
target_link_libraries(main ${LIBS})

target_include_directories(main
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)
add_executable(starter-2 ./demo/starter-2.cxx)

target_link_libraries(starter-2 ${LIBS})

target_include_directories(starter-2
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)

add_executable(starter-3 ./demo/starter-3.cxx)

target_link_libraries(starter-3 ${LIBS})

target_include_directories(starter-3
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)

add_executable(maincourse1 ./demo/maincourse1.cxx)

target_link_libraries(maincourse1 ${LIBS})

target_include_directories(maincourse1
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)

add_executable(maincourse1v2 ./demo/maincourse1_v2.cxx)

target_link_libraries(maincourse1v2 ${LIBS})

target_include_directories(maincourse1v2
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)

add_executable(starter4 ./demo/starter4.cxx)

target_link_libraries(starter4 ${LIBS})

target_include_directories(starter4
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)

add_executable(maincourse3 ./demo/maincourse3.cxx)

target_link_libraries(maincourse3 ${LIBS})

target_include_directories(maincourse3
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)
