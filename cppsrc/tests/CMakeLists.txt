
set(TEST_NAME TestPoint2D)
add_executable(${TEST_NAME} TestPoint2D.cpp)

set_target_properties(${TEST_NAME} PROPERTIES
     PROJECT_LABEL "Regr - ${TEST_NAME}")
target_link_libraries(${TEST_NAME} OpenCmbCv)
add_test(${TEST_NAME} ${TEST_NAME})

