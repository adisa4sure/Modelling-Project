# Create new project
project (libFingerPrint)

# Create variable containing all the CXX sources
set(SOURCES
        base.cxx
)

# Add all the sources to the project
add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ${OpenCV_LIBS}
)
target_include_directories(${PROJECT_NAME} 
        PUBLIC
        ${OpenCV_INCLUDE_DIRS} 
)
