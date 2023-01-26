# Add this line to the CMakeLists.txt containing tests
add_executable(test_patch test_patch.cpp)
add_executable(test_an_isotrop test_an_isotrop.cpp)
add_executable(test_convolution test_convolution.cpp)
add_executable(test_deconvolution test_deconvolution.cpp)
add_executable(test_morphological test_morphological.cpp)
add_executable(test_squares test_squares.cpp)
add_executable(test_symmetries test_symmetries.cpp)
#target_link_libraries(test_finger gtest libFingerPrint)


#add_test (NAME finger_test
#    COMMAND test_finger
#    )
    
target_link_libraries(test_patch
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)
target_link_libraries(test_an_isotrop
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)
target_link_libraries(test_convolution
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)
target_link_libraries(test_deconvolution
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)
target_link_libraries(test_morphological
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)
target_link_libraries(test_squares
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)
target_link_libraries(test_symmetries
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)
