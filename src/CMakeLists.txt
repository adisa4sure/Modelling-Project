# Create variable containing all the CXX sources
set(SOURCES
        draw.cpp
        transformations.cpp
        utils.cpp
)

set(LIBS
    PUBLIC
    ${OpenCV_LIBS}
)

# Add all the sources to the project
add_library(libFingerPrint ${SOURCES})

target_link_libraries(libFingerPrint ${LIS})

target_include_directories(libFingerPrint
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)
