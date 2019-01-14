# Create variable containing all the CXX sources
set(SOURCES
        draw.cpp
)

set(LIBS
    PUBLIC
    ${OpenCV_LIBS}
    libFingerPrinth
)

# Add all the sources to the project
add_library(libFingerPrintsrc ${SOURCES})

target_link_libraries(libFingerPrintsrc ${LIS})

target_include_directories(libFingerPrintsrc
        PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)
