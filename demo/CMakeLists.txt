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
