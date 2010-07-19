file(GLOB TEST_SRCS "Test*.cpp")

foreach(TEST_SRC ${TEST_SRCS})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SRC}) 
    set_target_properties(${TEST_NAME} PROPERTIES
         PROJECT_LABEL "Regr - ${TEST_NAME}")
    target_link_libraries(${TEST_NAME} OpenCmbCv)
    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()

