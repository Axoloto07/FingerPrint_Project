
add_executable(restoration clean_finger_patch.cpp)
add_executable(blurred_finger blurr_finger.cpp)
add_executable(dry_finger dry_finger.cpp)
add_executable(corrupted_clean corrupted_clean.cpp)
add_executable(moist_finger moist_finger.cpp)
add_executable(weak_finger weak_finger.cpp)

target_link_libraries(restoration
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)
target_link_libraries(weak_finger
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)
target_link_libraries(moist_finger
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)
target_link_libraries(dry_finger 
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)
target_link_libraries(blurred_finger
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)
target_link_libraries(corrupted_clean 
    PRIVATE
    FingerPrint
    ${OpenCV_LIBS} m
    alg
)
