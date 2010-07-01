project(OpenCmbCv)
cmake_minimum_required(VERSION 2.8)

# Whether to make test programs
set(CMBCV_DO_TESTING ON CACHE BOOL "Whether to build test programs")
if(CMBCV_DO_TESTING)
    enable_testing()
endif()

# Custom cmake module for python testing
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

# C++ API
add_subdirectory(cppsrc)

# python API
add_subdirectory(pysrc)
