# Create new project
# Create variable containing all the CXX sources
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SOURCES
    "*.cpp"
)

# Add all the sources to the project
add_library(FingerPrint ${SOURCES})
