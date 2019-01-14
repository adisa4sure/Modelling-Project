# Create variable containing all the CXX sources
set(HEADERS
        draw.hpp
)

# Add all the sources to the project
add_library(libFingerPrinth ${HEADERS})
target_link_libraries(libFingerPrinth libFingerPrintsrc)
