cmake_minimum_required(VERSION 3.8.11)
project(FingerPrint)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(OpenCV REQUIRED)
# Create variable containing all the CXX sources
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(alglib/)

add_subdirectory(alglib)
add_subdirectory(src)
# add_subdirectory(docs)
add_subdirectory(demo)
add_subdirectory(verif)
add_subdirectory(verif_results)
add_subdirectory(demo_results)

# # Download googletest while doing the configuration
# configure_file(CMakeLists.txt.in
#                googletest-download/CMakeLists.txt)
# execute_process(COMMAND ${CMAKE_COMMAND}
#   -G "${CMAKE_GENERATOR}" .
#   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
# execute_process(COMMAND ${CMAKE_COMMAND} --build .
#   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# # Add googletest when compiling
# add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
#                  ${CMAKE_BINARY_DIR}/googletest-build)

# include_directories(${gtest_SOURCE_DIR}/include)

# add_subdirectory(test)

enable_testing ()
