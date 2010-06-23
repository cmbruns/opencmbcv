project(OpenCmbCv)
cmake_minimum_required(VERSION 2.8)

set(CMBCV_DO_TESTING ON CACHE BOOL "Whether to build test programs")
if(CMBCV_DO_TESTING)
    enable_testing()
endif()

add_subdirectory(cppsrc)
