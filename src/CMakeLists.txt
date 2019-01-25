# Create variable containing all the CXX sources
set(SOURCES
        draw.cpp
        transformations.cpp
        utils.cpp
        estimations.cpp
        interpolation/lininterpolator.cxx
        interpolation/lancinterpolator.cxx
)

set(LIBS
    PUBLIC
    ${OpenCV_LIBS}
)

# Add all the sources to the project
add_library(FingerPrint SHARED ${SOURCES})

target_link_libraries(FingerPrint ${LIS})

target_include_directories(FingerPrint
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
        ../include
)
