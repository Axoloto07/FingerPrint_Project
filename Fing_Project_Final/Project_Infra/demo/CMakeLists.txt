
add_executable(restoration test_patch.cpp)
target_link_libraries(restoration
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)