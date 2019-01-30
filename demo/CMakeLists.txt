cmake_minimum_required (VERSION 3.0)

add_executable(basic_opencv basic_opencv.cxx)

target_link_libraries(basic_opencv
        PUBLIC
        ${OpenCV_LIBS}
)
target_include_directories(basic_opencv
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)
add_executable(starter-1 starter-1.cxx)

target_link_libraries(starter-1
        PUBLIC
        ${OpenCV_LIBS}
        FingerPrint
)
target_include_directories(starter-1
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
        ../include
)
