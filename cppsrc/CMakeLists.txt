include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
if(CMBCV_DO_TESTING)
    add_subdirectory(tests)
endif()

